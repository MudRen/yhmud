//��ȥ������ wuxing.c 
         
#include <ansi.h> 
#include <skill.h> 
#include <weapon.h> 
#include <combat.h> 
         
//inherit F_CLEAN_UP; 
 
void remove_effect(object me, int a_amount, int d_amount); 
 
inherit F_SSERVER; 
int perform(object me, object target) 
{ 
        object weapon; 
        int skill; 
        int extra; 
        string msg; 
  
        if ( !target ) target = offensive_target(me); 
         
        if ( !target 
                ||      !target->is_character() 
                ||      !me->is_fighting(target) ) 
                        return notify_fail("����ȥ�����Ρ�ֻ����ս����ʹ�á�\n"); 
 
        if (!objectp(weapon = me->query_temp("weapon")) 
                || (string)weapon->query("skill_type") != "sword") 
                return notify_fail("����ȥ�����Ρ������ý�����ʩչ��\n"); 
         
        if( (int)me->query_skill("luohan-jian", 1) < 100 ) 
                return notify_fail("��ġ��޺�������������죬����ʹ�á���ȥ�����Ρ���\n"); 
 
        if( (int)me->query("neili") < 300  )  
                return notify_fail("�������������\n"); 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
 
        skill = me->query_skill("luohan-jian",1); 
         
        extra = me->query_skill("luohan-jian",1) / 10; 
        extra += me->query_skill("luohan-jian",1) / 10; 
        me->add_temp("apply/attack", extra);     
        me->add_temp("apply/damage", extra); 
         
        msg = HIG "$N����ͻ�䣬˲������ֳ�������Ӱ��������$n��ȥ��\n" NOR; 
               message_vision(msg, me, target);  
         
        me->add("neili", -200); 
         
        message_combatd(HIR "  ���־���\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),  
                                       TYPE_REGULAR);  
         
        message_combatd(HIY "    ȥ�־���\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),  
                                       TYPE_REGULAR);  
 
        message_combatd(HIG "      ���־���\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),  
                                       TYPE_REGULAR);  
         
        message_combatd(HIB "        ���־���\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),  
                                       TYPE_REGULAR);  
         
        message_combatd(HIW "          ���־���\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),  
                                       TYPE_REGULAR);  

        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, skill, 80,  


                    HIC "            ��ȥ������    �û����澳 \n" NOR); 
        message_combatd(msg, me, target);  


        me->start_busy(3); 
        me->add_temp("apply/attack", -extra); 
        me->add_temp("apply/damage", -extra); 
 
        return 1; 
} 

