#include <ansi.h>
#include <combat.h>

#define PO "��" HIR "�����" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
//		object weapon;
		int damage;
		string msg;
		int ap, dp;
		//me = this_player();
	
		float improve;
		int lvl, m, n;
		string martial;
		string *ks;
		martial = "strike";
		me = this_player();

        if (userp(me) && ! me->query("can_perform/liuyang-zhang/po"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
		if (! target || ! me->is_fighting(target))
                return notify_fail(PO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(PO "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 220)
                return notify_fail("��˻�����Ψ�Ҷ��𹦻�򲻹�������ʩչ" PO "��\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 220)
                return notify_fail("�����ɽ�����Ʋ�����죬����ʩչ" PO "��\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ���㣬����ʩչ" PO "��\n");

        if (me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("��û�м�����ɽ�����ƣ�����ʩչ" PO "��\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang")
                return notify_fail("��û��׼����ɽ�����ƣ�����ʩչ" PO "��\n");

        if (me->query_skill_mapped("force") != "bahuang-gong")
                return notify_fail("��û�м����˻�����Ψ�Ҷ��𹦣�����ʩչ" PO "��\n");

        if (me->query("neili") < 800)
                return notify_fail("�������������㣬����ʩչ" PO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

		msg = HIR "$N" HIR "���˻�����Ψ�Ҷ������������ޣ�ȫ�������ŷ�������һ��"
              "��$n" HIR "ͷ����Ȼ���䡣\n" NOR;
			  
		lvl = to_int(pow(to_float(me->query("combat_exp") * 10), 1.0 / 3));
		lvl = lvl * 4 / 5;
		ks = keys(me->query_skills(martial));
		improve = 0;
		n = 0;
		//������5�����ܵļӳ�
		for (m = 0; m < sizeof(ks); m++)
		{
			if (SKILL_D(ks[m])->valid_enable(martial))
			{
				n += 1;
				improve += (int)me->query_skill(ks[m], 1);
				if (n > 4 )
					break;
			}
		}
		
		improve = improve * 4 / 100 / lvl;

		me->add("neili", -380);
        ap = me->query_skill("force") + me->query_skill("strike");
        dp = target->query_skill("force") + target->query_skill("parry");
		ap += ap * improve;
		if (me->query("family/family_name") == "���չ�")
			ap += ap / 10;
        if (target->is_good()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
		{
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        msg += HIR "��ʱֻ�����ۡ���һ����$N" HIR "һ�ƽ�$n"
                               HIR "ͷ���ĵ÷��飬�Խ��Ľ�������̱����ȥ��\n"
                               NOR "( $n" RED "���˹��أ��Ѿ�������в���"
                               "��ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                } else
			{
			//damage = ap * 2 / 3;
			        damage = ap + random(ap / 2);

	                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
        	                                   HIR "$n" HIR "��æ�ֵ�������Ȼ������$N"
                                                   HIR "�ƾ����ˮ��ӿ�����ڣ������������"
                                                   "�߹ǡ�\n:����@?");
			}
			me->start_busy(1 + random(3));
		} else
		{
			msg += CYN "$p" CYN "��$P" CYN "�ƾ����ȣ����Ƶֵ���"
                       "ס����������������������������\n" NOR;
			me->start_busy(1 + random(4));
		}
		message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

	return 1;
}