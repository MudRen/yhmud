#include <ansi.h>
#include <combat.h>

#define ZHUAN "��" HIY "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count;
        int i, attack_time;

        if (userp(me) && ! me->query("can_perform/longxing-jian/kong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" ZHUAN "��\n");

        if ((int)me->query_skill("longxing-jian", 1) < 160)
                return notify_fail("������ν���������죬����ʩչ" ZHUAN "��\n");

        if (me->query("neili") < 250)
                return notify_fail("�����������������ʩչ" ZHUAN "��\n");

        if (me->query_skill_mapped("sword") != "longxing-jian")
                return notify_fail("��û�м������ν���������ʩչ" ZHUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "һ����Х������" + weapon->name() +
              HIY "����������������գ�ɲ�Ǽ䣬һ����⼲�䣬"
              HIY "����һ��������Խ�ڰ�գ��͵�����$n" HIY "��\n" NOR;

        ap = me->query_skill("sword");
        dp = target->query_skill("parry");
        attack_time = 7;
        if (ap / 2 + random(ap * 2) > dp)
        {
                msg += HIR "���$p" HIR "��$P" HIR
                       "���˸����ֲ������������˲�Ͼ��\n" NOR;
                count = ap / 6;
                me->add_temp("apply/attack", count);
                attack_time += random(ap / 45);
        } else
        {
                msg += HIC "$n" HIC "��$N" HIC "�⼸����������"
                       "�����Ҵ��⣬С��Ӧ����\n" NOR;
                count = 0;
        }
                
        message_combatd(msg, me, target);

        if (attack_time > 10)
                attack_time = 10;

        me->add("neili", -attack_time * 20);

        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(attack_time));

        return 1;
}

