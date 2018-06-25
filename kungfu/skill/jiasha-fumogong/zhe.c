#include <ansi.h>
#include <combat.h>

#define JIU "��" HIR "��������" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/jiasha-fumogong/zhe"))
               return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(JIU "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("max_neili") < 2000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" JIU "��\n");

        if (me->query_skill("jiasha-fumogong", 1) < 140)
                return notify_fail("������ķ�ħ����������죬����ʩչ" JIU "��\n");

        if (me->query_skill_mapped("unarmed") != "jiasha-fumogong")
                return notify_fail("������û�м������ķ�ħ��Ϊȭ�ţ�����ʩչ" JIU "��\n");

        if (me->query_skill_prepared("unarmed") != "jiasha-fumogong")
                return notify_fail("������û��׼��ʹ�����ķ�ħ��������ʩչ" JIU "��\n");

        if ((int)me->query("neili") < 400)
                return notify_fail("��������������޷�����" JIU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "���һ����ʩ�����С�" HIR "��������" HIG "������ʱ�����ŷ��������Ķ���˫��"
              "��Ȼ������������$n" HIG "��\n" NOR;

        ap = me->query_skill("unarmed") + me->query("con") * 20;
        dp = target->query_skill("parry") + target->query("con") * 20;

        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 4;
                if ( me->query("max_neili") > target->query("max_neili") * 2
                     && me->query("neili") > 500 )
                {
                msg += HIR "$n" HIR "ȫ��һ�������㲻�ȣ���$N"
                       HIR "���л��÷������صĵ����ڵ��ϡ�\n" NOR;

                me->add("neili", -500);
                me->start_busy(3);

              //  message_combatd(msg, me, target);

                target->set("eff_qi", 0);
                target->set("eff_jing", 0);
                //target->unconcious(me);
                }
        } else
        {
                count = ap / 9;

        }

        message_sort(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -300);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
              //  if (random(5) < 2 && ! target->is_busy())
               //         target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));

        me->add_temp("apply/attack", -count);

        return 1;
}

