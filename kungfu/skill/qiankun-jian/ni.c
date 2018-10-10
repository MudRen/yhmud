#include <ansi.h>
#include <combat.h>

#define NI "��" HIW "��תǬ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
		
		float improve;
		int lvl, i, n;
		string martial;
		string *ks;
		martial = "sword";

        if (userp(me) && ! me->query("can_perform/qiankun-jian/ni"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(NI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" NI "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" NI "��\n");

        if (me->query_skill("qiankun-jian", 1) < 180)
                return notify_fail("���Ǭ������Ϊ����������ʩչ" NI "��\n");

        if (me->query("neili") < 400)
                return notify_fail("�����������������ʩչ" NI "��\n");

        if (me->query_skill_mapped("sword") != "qiankun-jian")
                return notify_fail("��û�м���Ǭ���񽣣�����ʩչ" NI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ����Х������" + weapon->name() +
              HIW "һ�񣬽�Ǭ����������ʩչ����ʱ��Ӱ���أ���"
              "���⻪ֱ׷$n" + HIW "��ȥ��\n" NOR;
			  
		lvl = to_int(pow(to_float(me->query("combat_exp") * 10), 1.0 / 3));
		lvl = lvl * 4 / 5;
		ks = keys(me->query_skills(martial));
		improve = 0;
		n = 0;
		//������5�����ܵļӳ�
		for (i = 0; i < sizeof(ks); i++)
		{
			if (SKILL_D(ks[i])->valid_enable(martial))
			{
				n += 1;
				improve += (int)me->query_skill(ks[i], 1);
				if (n > 4 )
					break;
			}
		}
		
		improve = improve * 3 / 100 / lvl;

        ap = me->query_skill("sword") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("parry");
		
		ap += ap * improve;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 3 + random(ap / 3);
                me->add("neili", -200);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
                                           HIR "$n" HIR "��ȫ�޷�����������ʵ��΢"
                                           "΢һ��䣬����" + weapon->name() + HIR
                                           "����û���Լ��ؿ����硣\n" NOR);
        } else
        {
                me->add("neili", -80);
                me->start_busy(4);
                msg += CYN "����$n" CYN "����" CYN "$N" CYN
                       "������������һԾ�������������Ī��"
                       "��һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
