// bohu.c ������

#include <ansi.h>
#include <combat.h>

#define BOHU "��" HIY "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
		
		float improve;
		int lvl, m, n;
		string martial;
		string *ks;
		martial = "whip";
 
        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/ruanhong-zhusuo/bohu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(BOHU "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" BOHU "��\n");

        if ((int)me->query_skill("ruanhong-zhusuo", 1) < 150)
                return notify_fail("����������������죬�޷�ʩչ" BOHU "��\n");

        if (me->query("neili") < 300)
                return notify_fail("��������������޷�ʩչ" BOHU "��\n");

        if (me->query_skill_mapped("whip") != "ruanhong-zhusuo")
                return notify_fail("��û�м�������������޷�ʩչ" BOHU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ�����ȣ�ʹ������������������" + weapon->name() +
              HIY "���裬�����Ӱ��������СȦ������ǵ�����$n" + HIY "��\n" NOR;
			  
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

        ap = me->query_skill("whip") + me->query_skill("force");
        dp = target->query_skill("force") + target->query_skill("parry");
		
		ap += ap * improve;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 4 + random(ap / 3);
                me->add("neili", -300);
                me->start_busy(1);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "ֻ��$n" HIR "һ���ҽУ�" + weapon->name() + HIR
                                           "����$p" + HIR "���ϻ���������ɼ��ǵ��˿ڣ�Ƥ��"
                                           "���룬��Ѫ�ɽ����಻���ԣ�\n" NOR);
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
