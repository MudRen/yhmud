// sanda.c ���師
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
		object weapon;	
		string msg;
		int ap, dp;
		int damage, count;
		int zhuan;
		
		zhuan = me->query("reborn/count");
		
		if (! target) target = offensive_target(me);
		
		if (! me->is_fighting())
			return notify_fail("�����師��ֻ����ս����ʹ�á�\n");
			
		if (! objectp(weapon = me->query_temp("weapon")) ||
				(string)weapon->query("skill_type") != "hammer")
			return notify_fail("��ʹ�õ��������ԡ�\n");
			
		if (me->query_skill_mapped("hammer") != "leiting-fu")
            return notify_fail("��û�м�����������������ʹ�á����師����\n");

		if ((int)me->query_str() < 40)
			return notify_fail("�����ڵı���������Ŀǰ����ʹ�á����師����\n");

		if ((int)me->query_skill("force") < 200)
			return notify_fail("����ڹ���򲻹�������ʩչ�����師����\n");

		if ((int)me->query_skill("hammer", 1) < 180)
			return notify_fail("��Ĺ�����Ϊ����������ʹ�á����師����\n");

		if ((int)me->query("neili") < 500)
			return notify_fail("����������㣡\n");
		
		if (! living(target))
			return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

		// ��һ�����Դ�
		ap = me->query_skill("hammer") + me->query("str") * 2;
		dp = target->query_skill("force");
		damage = me->query_skill("leiting-fu", 1);
		damage += (me->query_str() - zhuan * 20) * 2;
		count = me->query_str() - zhuan * 20;
		
        msg = "\n" HIW "$N" HIW "�ȵ������Դ���\n" NOR;
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                           "һ�����ѻ����Լ���ǰ����������������"
                                           "�л������С�\n" NOR);
				me->add("neili", -80);
        } else
        {
                msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
                       "����������ֵ�����©���������\n" NOR;
				me->add("neili", -40);
        }

        // �ڶ���������
        ap += me->query("dex") * 3;
		dp = target->query_skill("parry");
		damage += (me->query_dex() - zhuan * 20) * 3;
		count += me->query("dex") - zhuan * 20;
        msg += "\n" YEL "$N" YEL "�ȵ�����������\n" NOR;
        if (ap / 2 + random(ap * 4 / 5) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                           "һ�����ѻ����Լ���ǰ����������������"
                                           "�л������С�\n" NOR);
				me->add("neili", -110);
        } else
        {
                msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
                       "����������ֵ�����©���������\n" NOR;
				me->add("neili", -55);
        }

        // �������Ͷ���
        ap += me->query("con") * 5;
        dp = target->query_skill("dodge");
		damage += (me->query_con() - zhuan * 20) * 5;
		count += me->query("con") - zhuan * 20;
        msg += "\n" HIM "$N" HIM "�ȵ����Ͷ��䣡\n" NOR;
        if (ap / 3 + random(ap * 3 / 5) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                           "һ�����ѻ����Լ���ǰ����������������"
                                           "�л������С�\n" NOR);
				me->add("neili", -140);
        } else
        {
                msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
                       "����������ֵ�����©���������\n" NOR;
				me->add("neili", -70);
        }

        me->start_busy(3 + random(3));
        message_combatd(msg, me, target);
        return 1;
}
