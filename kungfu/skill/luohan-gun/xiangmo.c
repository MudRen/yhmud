// xiangmo.c �޺���ħ����ʮ���޺���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
                object weapon;
        
        if (! target) target = offensive_target(me);
        
        //if ( userp(me) && !me->query("can_perform/luohan-gun/xiangmo"))
        //        return notify_fail("��ʹ�õ��⹦��û��������ܣ�\n");
        
        if (! objectp(weapon = me->query_temp("weapon")) ||  
                        (string)weapon->query("skill_type") != "club")  
                 return notify_fail("��ʹ�õ��������ԡ�\n");
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("���޺���ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill("luohan-gun", 1) < 80) 
        return notify_fail("����޺�����������죬���ڻ��޷�ʹ�á��޺���ħ����\n");
                                
        if ((int)me->query("neili") < 150)
        return notify_fail("�����������������޷����á��޺���ħ����\n");
                
        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�˵�һ����һ��ƽƽ��$n"
              HIY "ɨ������ʽ��Ȼ�򵥣�����ȴҲ���������ء�\n" NOR;

        ap = me->query_skill("club");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                damage = 100 + ap / 5 + random(ap / 5);
                me->add("neili", -50);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "ֻ��$n" HIR "һ���м�ʧ�󣬵�ʱ"
                                           "��������˸����ţ��ƺ�һ��������һ����\n" NOR);
                me->start_busy(2);
        } else 
        {
                msg += CYN "����$p" CYN "����һ�񣬼�ס��$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                me->add("neili", -50);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}


