#include <ansi.h> 
#include <combat.h> 
 
inherit F_SSERVER; 
 
int perform(object me, object target) 
{ 
      int i, jiali, count; 
        string msg; 
       object weapon; 
 
       if( !target ) target = offensive_target(me); 
       if( !target 
                || !target->is_character() 
                || !me->is_fighting(target)  
                || !living(target)) 
                return notify_fail("�������桹����ֻ�ܶ�ս���еĶ���ʹ�á�\n");        
       if (! objectp(weapon = me->query_temp("weapon")) || 
          (string)weapon->query("skill_type") != "blade")  
                return notify_fail("�����Ұѵ���˵�ɣ�\n"); 
         
        if (me->query_skill_mapped("blade") != "jiechen-dao") 
                return notify_fail("�����ʹ�ý䳾����ʩչ�������桹��\n"); 
 
        if(me->query_skill("jiechen-dao", 1) < 180 ) 
                return notify_fail("��Ľ䳾������Ӳ������⡸�����桹��������Ҳ�ա�\n"); 
 
        if(me->query_skill("blade", 1) < 180 ) 
                return notify_fail("��Ļ���������������죬ʹ�����������桹������\n");        
 
        if( (int)me->query_skill("hunyuan-yiqi", 1) < 140 ) 
                return notify_fail("�����������Ԫ���ȼ�������ʹ�����������桹������\n"); 
 
        if( (int)me->query_con() < 34) 
                return notify_fail("������廹����ǿ׳��ǿʹ�������桹�����������Է٣�\n"); 
 
        if ( me->query_skill_mapped("force") != "hunyuan-yiqi") 
           return notify_fail("���������ڹ�ƽƽ���棬���ʹ�ó��������桹����������\n");  
 
        if (me->query("max_neili") < 3000) 
           return notify_fail("���������Ϊ�������⡸�����桹��������Ҳ�ա�\n"); 
 
        if (me->query("neili") < 1000) 
           return notify_fail("����Ŀǰ�������������⡸�����桹��������Ҳ�ա�\n"); 
 
        me->add("neili", -300); 
  
        message_vision(HIR "\nͻȻ$N���������������ֽ������֣��˳�ʮ������������ɫ��ʱͨ�죬\n"    
                           "�������޽����������������Ĵ߶������̹��ƴ�ʤ��\n" 
                           "����$nֱ�����£�\n" NOR, me, target);       
 
        i = me->query_skill("force") / 2 * (3+random(4));         
        jiali = me->query("jiali"); 
 
        me->set("jiali", i); 
        me->add_temp("apply/attack", jiali/2); 
         
        count = 4; 
        count += random(4); 
        while (count --) 
        { 
 
              COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0); 
        } 
         
        me->add_temp("apply/attack", -jiali/2); 
        me->set("jiali", jiali); 
        if(!me->query_temp("xiuluo")) me->add("neili", -300); 
        else me->delete_temp("xiuluo"); 
 
        me->start_busy(1+random(3)); 
        return 1; 
} 

