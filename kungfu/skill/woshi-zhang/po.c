#include <ansi.h> 
#include <combat.h>  

inherit F_SSERVER;  

int perform(object me, object target)  
{
        string msg;  
        int damage;  

        if (! target) target = offensive_target(me);  

        if (! target || ! me->is_fighting(target))  
                return notify_fail("����ʯ����ֻ����ս���жԶ���ʹ�á�\n");  

        //if (userp(me) && ! me->query("can_perform/woshi-zhang/po"))  
        //        return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");  

        if (me->query_temp("weapon") ||  
            me->query_temp("secondary_weapon"))  
                return notify_fail("�������ֲ���ʹ�á���ʯ���񡹣�\n");  

        if (me->query_skill("force") < 140)  
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");  

        if (me->query_skill("woshi-zhang", 1) < 120)  
                return notify_fail("�����ʯ����Ϊ������Ŀǰ����ʹ�á���ʯ���񡹣�\n");  

        if (me->query_skill_mapped("strike") != "woshi-zhang") 
                return notify_fail("��û�м�����ʯ�ƣ�����ʩչ����ʯ���񡹡�\n"); 

        if (me->query("neili") < 400) 
                return notify_fail("��������������������ʩչ����ʯ���񡹡�\n"); 

        if (! living(target)) 
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        msg = HIW "ֻ��$N" HIW "�������ƣ���Ȼ��ŭ��һ����һ���ƿն���������" 
              "��ʯ�Ƶ�һ�С�������ʯ�����ƿ�����$n" HIW "��ȥ��\n" NOR; 

        if (random(me->query_skill("strike")) > target->query_skill("parry") / 2) 
        { 
                me->start_busy(2); 

                damage = me->query_skill("woshi-zhang", 1); 
                //damage = damage * 2 + random(damage * 5); 
                damage = damage * 2 + random(damage * 2);
                //msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35, 
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���ֻ��$n" HIR "һ���Һ����ؿ�" 
                                           HIR "�ѱ�$N�ƾ����ʵʵ�ĺ��У����ۡ������һ��" 
                                           "����Ѫ��\n" NOR); 
                me->add("neili", -250); 
        } else 
        {
                me->start_busy(2); 
                me->add("neili", -120); 
                msg += CYN "����$p" CYN "������$N" CYN 
                       "����ͼ���㿪������ɱ�š�\n" NOR; 
        }
        message_combatd(msg, me, target); 

        return 1; 
}


