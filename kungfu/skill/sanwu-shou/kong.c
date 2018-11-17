#include <ansi.h>
#include <combat.h>

#define KONG "��" HIY "�޿ײ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, count;
        string msg;
        int ap, dp;
        object weapon;

        if (userp(me) && ! me->query("can_perform/sanwu-shou/kong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "whip")
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" KONG "��\n");

        if ((int)me->query_skill("sanwu-shou", 1) < 140)
                return notify_fail("�����������ֹ���죬����ʩչ" KONG "��\n");

        if (me->query_skill_mapped("whip") != "sanwu-shou")
                return notify_fail("��û�м������������֣�����ʩչ" KONG "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ���Ϊ����������ʩչ" KONG "��\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����ڵ���������������ʩչ" KONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("whip");
        dp = target->query_skill("parry");
		count = 0;
		
		if (target->query("shen") > 0)
		{
			count += 20;
			ap += ap * 10 / 100;
		}		
	
		if (target->query("gender") != "Ů��")
		{
			count += 30;
			ap += ap * 15 / 100;
		}
				
	
        msg = HIY "\n$N" HIY "һ����Х���ھ����ǣ�ʩ�����С�" HIW "�޿�"
              "����" HIY "������" + weapon->name() + HIY "�������죬��"
              "��������$N" HIY "��Ȼ�ڿն��𣬻��������е�" + weapon->name() + 
              HIY "�����ֱ�£�ӿ��$n" HIY "��\n" NOR;
        message_sort(msg, me, target); 

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap);
				damage += damage * count / 100;
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60 + count,
                                           HIR "����$N" HIR "������飬���ư��磬"
                                           "$n" HIR "������΢һ�����ҽ�һ������"
                                           "ʱ��Ѫ���ܡ�\n" NOR);

                me->start_busy(1 + random(3));
                me->add("neili", -220);
        } else
        {
                msg = CYN "$n" CYN "��$N" CYN "����Ϯ��������"
                      "��ӯ��ֻ�����һ�ݣ��Ŷ����һ�ޡ�\n" NOR;

                me->start_busy(4);
                me->add("neili", -100);
        }
        message_vision(msg, me, target);
        return 1;
}
