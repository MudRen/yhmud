#include <ansi.h>
#include <combat.h>

#define ZHENWU "��" HIY "�����а" NOR "��"

inherit F_SSERVER;

string final(object me, object target, int damage);

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
		martial = "sword";

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHENWU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHENWU "��\n");

        if ((int)me->query_skill("taiji-jian", 1) < 180)
                return notify_fail("���̫������������죬����ʩչ" ZHENWU "��\n");

        if (me->query("neili") < 200)
                return notify_fail("��������������������ʩչ" ZHENWU "��\n");

        if (me->query_skill_mapped("sword") != "taiji-jian") 
                return notify_fail("��û�м���̫������������ʩչ" ZHENWU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��ǰһ����ƽƽ�ӳ�һ������ɨ$n" HIY "��ȥ����"
              "�ް�㻨�ɿ��ԡ�\n" NOR;
			  
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
		
		improve = improve * 5 / 100 / lvl;

        me->add("neili", -50);
        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
		ap += ap * improve;
        if (target->is_bad()) ap += ap / 8;

        me->start_busy(2);
        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIC "����$n" HIC "��͸$P" HIC "�к����ɱ�ţ���"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 4, me);
        target->receive_wound("jing", damage / 8, me);
        return  HIY "���$n" HIY "ȴ˿��δ�����з����������Ӧ��һ�У�ȴ��$N"
                HIY "����\n��Ȼһ�䣬������ǧ���������������߷緶��\n" NOR +
                HIR "$n" HIR "��ʱ����ʧ�룬��$P" HIR "��һ������Ҫ������Ѫ����"
                "���Ҳ��̶ã�\n" NOR;
}

