#include <ansi.h>
#include <combat.h>

#define ZHUAN "��" HIR "תǬ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
//      object weapon;
        int ap, dp, damage, count;
        string msg;
		
		float improve;
		int lvls, m, n;
		string martial;
		string *ks;
		martial = "finger";

        if (userp(me) && ! me->query("can_perform/tanzhi-shentong/zhuan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(ZHUAN "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 220)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʩչ" ZHUAN "��\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 200)
                return notify_fail("�������������Ϊ����������ʩչ" ZHUAN "��\n");
 
        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" ZHUAN "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" ZHUAN "��\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ���㣬����ʩչ" ZHUAN "��\n");

        if (me->query("neili") < 800)
                return notify_fail("�����ڵ���������������ʩչ" ZHUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��ȫ��������һָ��ָ�����ն�ʮ���޷�λ�ƹ��������"
              "���һ�����" HIR "תǬ��" HIC "��������\n" NOR;
			  
		lvls = to_int(pow(to_float(me->query("combat_exp") * 10), 1.0 / 3));
		lvls = lvls * 4 / 5;
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
		
		improve = improve * 5 / 100 / lvls;

        ap = me->query_skill("finger") +
             me->query_skill("qimen-wuxing", 1) +
             me->query_skill("tanzhi-shentong", 1);

        dp = target->query_skill("force") +
             target->query_skill("parry", 1) +
             target->query_skill("qimen-wuxing", 1);
		count = me->query_skill("mathematics", 1); 
		ap += ap * improve;

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                	me->start_busy(2);
                        msg += HIR "���Ǽ�$n" HIR "ֻ����âһ����$N" HIR "ʳָ"
                               "������$p" HIR "ӡ�ð�ߣ�ָ����ʱ���Զ��롣\n"
                               HIW "���������ۡ���һ�������Ͼ�Ȼ���������Խ���"
                               "\n" NOR "( $n" RED "���˹��أ��Ѿ�������в���"
                               "����ʱ�����ܶ�����" NOR ")\n";
                        damage = -1;
                } else
		{
                	me->start_busy(3);
                	damage = ap + random(ap);
                	me->add("neili", -(200 + random(count)));
                	msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, (100 + random(count/10)),
                        	                   HIR "���Ǽ�$n" HIR "ֻ����âһ����$N"
                                                   HIR "ʳָ������$p" HIR "���ð�ߣ�ָ��"
                                                   "��ʱ������롣\n���������͡���һ����"
                                                   "���Ͼ�Ȼ����������Ѫ��\n" NOR);
		}
        } else
        {
                me->start_busy(2);
                me->add("neili", -200);
                msg += CYN "$p" CYN "��$P" CYN "��ʽ���أ����д�"
                       "�⣬��ʱ���Ծ���ɣ�����������\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}