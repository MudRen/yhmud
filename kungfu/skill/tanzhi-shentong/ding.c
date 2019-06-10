#include <ansi.h>
#include <combat.h>

#define DING "��" HIC "������" NOR "��"

string final(object me, object target);

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
		int damage;

        if (userp(me) && ! me->query("can_perform/tanzhi-shentong/ding"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(DING "ֻ�ܿ���ʩչ��\n");

        //if (target->is_busy())
        //        return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
		if (target->query_temp("no_perform"))
                return notify_fail("�Է������Ѿ��޷������������ŵ������ɡ�\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 120)
                return notify_fail("��ĵ�ָ��ͨ������죬����ʩչ" DING "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 120)
                return notify_fail("��Ծ���ѧ���˽ⲻ��������ʩչ" DING "��\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("��û�м�����ָ��ͨ������ʩչ" DING "��\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("��û��׼����ָ��ͨ������ʩչ" DING "��\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("���������Ϊ���㣬����ʩչ" DING "��\n");

        if (me->query("neili") < 300)
                return notify_fail("�����ڵ���������������ʩչ" DING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��ָ�ᵯ����ʱֻ����쬡���һ����һ���������޵�"
              "����ѳ�$n" HIC "�����ȥ��\n" NOR;

        ap = me->query_skill("finger");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
/*                msg +=  HIR "$n" HIR "ֻ��в��һ�飬�ѱ�$P"
                        HIR "ָ�����У�ȫ����������������������\n" NOR;
                target->start_busy(ap / 30 + 2);
*/
				damage = ap / 4 + random(ap / 2);
				msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 0, (: final, me, target, 0 :));
                me->start_busy(2);
                me->add("neili", -200);

        } else
        {
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������һԾ�����˿�ȥ��\n" NOR;
                me->start_busy(1);
				me->add("neili", -150);
        }
        message_combatd(msg, me, target);
		return 1;
}

string final(object me, object target)
{
        target->set_temp("no_perform", 1);
        call_out("ding_end", 1 + random(5), me, target);
        return HIR "$n" HIR "ֻ����ǰ��âһ���������漴ȫ��һ��"
               "��ʹ������Ѫ�������������\n$p��Ȼ��һ��������"
               "�����������������ƻ�ɢһ�㣬ȫȻ�޷����ơ�\n" NOR;
}

void ding_end(object me, object target)
{
        if (target && target->query_temp("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
                target->delete_temp("no_perform");
	}
	return;
}
