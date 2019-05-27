#include <ansi.h> 
#include <combat.h>  
 
inherit F_SSERVER; 
#include "/kungfu/skill/eff_msg.h"; 
 
int perform(object me, object target) 
{ 
        string msg/*, dodge_skill*/; 
        int extra, skill, at, df, i, lmt, damage, p; 
        object weapon; 
        extra = me->query_skill("leiming-bian",1); 
 
        //if (userp(me) && !me->query("can_perform/leiming-bian/cibei")) 
       //       return notify_fail("��ʹ�õ��⹦��û��������ܡ�\n"); 
        if( !target ) target = offensive_target(me); 
 
        if( !target 
                 || !target->is_character() 
                 || !me->is_fighting(target) ) 
              return notify_fail("�۴ȱ��־���ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 
 
        if( extra < 160) 
              return notify_fail("��������޷���Ϊ̫��,������ʹ�ôȱ��־���\n"); 
         
        skill = me->query_skill("buddhism", 1); 
         
        if( skill < 150) 
              return notify_fail("��������ķ��ȼ�����������֧�ִȱ��־��� \n"); 
         
        if( me->query("shen") < 200000) 
              return notify_fail("�ȱ��־������ޱ�����Ϊ��,��ʦ���Ƕ������°�! \n"); 
         
        if( me->query("neili") < 1500 ) 
              return notify_fail("���������Ϊ���������ȱ��־���\n"); 
         
        weapon = me->query_temp("weapon"); 
 
        if( !weapon 
         || weapon->query("skill_type") != "whip") 
              return notify_fail("������û�б������ʹ�ôȱ��־���\n"); 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
         
        msg = RED "ֻ��$N����������ȱ�Ϊ�������е�" + weapon->name() + RED "�·����������㵹����$n��\n" NOR;   
                 
        at = me->query("combat_exp") * me->query_skill("leiming-bian", 1) / 1000;  
        df = target->query("combat_exp") * target->query_skill("dodge", 1) / 1000;  
                 
        if( (random(at) + at / 2)  > df ) 
        { 
            damage = me->query("shen", 1) / 2000; 
             
            //if(damage > 1500) damage = 1500 + (damage-1500)/100; 
            if(damage > 1500) damage = 1500; //�趨���� 2017-02-03
             
            msg += CYN "$n������$N���ޱ߷𷨴򶯣��͵ĺ��ˣ�����û��һ˿Ѫɫ...\n" NOR;        
            target->receive_damage("qi", damage, me); 
            target->receive_wound("qi", damage / 3, me); 
             
            p = (int)target->query("qi") * 100 / (int)target->query("max_qi"); 
            msg += "( $n" + eff_status_msg(p) + " )\n";  
            message_vision(msg, me, target); 
            target->start_busy(3); 
             
            weapon = me->query_temp("weapon"); 
            msg = HIG "\n������$N���е�" + weapon->name() + HIG "�����ζ�����Ȼ��֪���ж��ٻ���\n" NOR; 
            message_vision(msg,me,target); 
                     
            lmt = random(me->query_skill("leiming-bian", 1) / 50) + 1; 
            if ( lmt < 3 ) lmt = 3; 
            if ( lmt > 6 ) lmt = 6; 
 
            for(i=1;i <= lmt;i++) 
            { 
                 extra = me->query_skill("leiming-bian", 1); 
                 me->add_temp("apply/attack", extra / 5); 
                 me->add_temp("apply/damage", extra / 5); 
                 COMBAT_D->do_attack(me,target, me->query_temp("weapon"), 1); 
                 me->add_temp("apply/attack",-extra / 5); 
                 me->add_temp("apply/damage",-extra / 5); 
            } 
            me->add("neili",-300); 
            me->start_busy(random(2) + 2); 
        } else  
       {       
              msg = HIG "\n$n���������ǿ$N�Ĺ�����ȫ�������Σ�\n" NOR; 
              message_vision(msg,me,target); 
              me->add("neili",-200); 
              me->start_busy(random(2)); 
       } 
        return 1; 
} 
