//duan.c  
// gladiator 
 
#include <ansi.h> 
 
inherit F_SSERVER; 
 
int perform(object me, object target) 
{ 
        int str, dex, skill, power; 
        string weapon; 
 
        if( !target ) target = offensive_target(me); 
         
        if( !target 
                ||      !target->is_character() 
                ||      !me->is_fighting(target) ) 
                return notify_fail("[���ƾ�]ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 
                 
        if( me->query_skill("force",1) < 100 ) 
                return notify_fail("��Ļ����ڹ����δ�����޷�ʩչ���ƾ���\n");        
         
        if( me->query_skill("whip",1) < 100 ) 
                return notify_fail("���ƾ���Ҫ��տ�����Ʊ޷�������Чʩչ��\n");        
         
                // for a 800K player, frce/2 = 150, shen/3K = 300, power = 300 
                // for players > 1.2M, power will hit max 
         
        str = me->query_str(); 
         
        power = random( me->query_skill("qingyun-bian",1) / 3) + me->query_skill("force",1) / 2; 
                 
        if(power<150)power=150; 
        if(power>480)power=480; 
         
        if( me->query("neili") <= 200 ) 
                return notify_fail("�����������ʹ�ö��ƾ���\n"); 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
         
        message_vision(HIW "$N�����������͵�һ��"NOR + "$n" +  
                       HIW "�����ޱ߷����������գ�һ��"NOR +  
                       HIM "�" NOR + HIW "���������Ӱ����ǵص������Ϯ����\n"  
                         NOR, me, me->query_temp("weapon")); 
         
        me->add_temp("apply/attack", power / 5); 
        me->add_temp("apply/damage", power / 5); 
        target->add_temp("apply/armor",-power / 5); 
        target->add_temp("apply/dodge",-power / 5); 
 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
         
        if (random(10)>0) COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        if (random(10)>2) COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        if (random(10)>4) COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        if (random(10)>6) COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 
        if (random(10)>8) COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
 
                 
        me->start_perform(1 + random(2),"[���ƾ�]"); 
                 
        me->add_temp("apply/attack", -power / 5); 
        me->add_temp("apply/damage",-power / 5); 
        target->add_temp("apply/armor",power / 5); 
        target->add_temp("apply/dodge",power / 5); 
 
        me->add("neili", -power); 
        me->start_busy( 2 + random(2)); 
 
        return 1; 
} 

