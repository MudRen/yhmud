#include <ansi.h>
#include <combat.h>

#define LIAN "��" HIW "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        //int i, count;

        if (userp(me) && ! me->query("can_perform/quanzhen-jian/lian"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("�������޽������ʩչ" LIAN "������\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 180)
                return notify_fail("��ȫ�潣��������죬����ʩչ" LIAN "��\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("��û�м���ȫ�潣��������ʩչ" LIAN "��\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang" &&
			me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("��û�м���ȫ����Ʒ�������ʩչ" LIAN "��\n");

        if ((int)me->query("neili") < 400)
                return notify_fail("�����ڵ��������㣬����ʩչ" LIAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->start_busy(3);
        me->add("neili", -60);

        msg = HIR "������У�$N��ƽ�̣�����������ͬʱ���Ⱥ�ɨ����������ȫ�����е�" LIAN HIR"���С�\n" NOR;
        message_combatd(msg, me, target);

        COMBAT_D->do_attack(me, target, weapon, 1);

        weapon->unequip();
        COMBAT_D->do_attack(me, target, 0, 1);

        ap = me->query_skill("sword") + me->query_skill("unarmed", 1);
        dp = target->query_skill("parry");

        message_combatd(HIY "$N" HIY "��һ�䣬৵�һ�ȣ�������$n��ɨ������ֻ���õ��ϳ������\n" NOR, me, target);

        if(random(ap) > dp / 2)
        {
                damage = ap / 2 + random(ap);

                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "ֻ��$n�����������Ѿ���$Nһ��ɨ�У��ҽ����У�����������\n" NOR);
                me->add("neili", -150);
				message_combatd(msg, me, target);
        } else
        {
				message_combatd(HIY "$n�������������ͣ����һԾ�����ɵض��˿�ȥ��\n" NOR, me, target);
				me->add("neili", -50);
		}

        weapon->wield();

        return 1;
}

