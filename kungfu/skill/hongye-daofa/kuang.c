          
#include <ansi.h>  
#include <combat.h>  
  
#define KUANG "��" HIR "�����Ҷ" NOR "��"   
  
inherit F_SSERVER;  
  
int perform(object me, object target)  
{  
        int extra;  
        object weapon;  
        string msg;  
  
        extra=me->query_skill("hongye-daofa",1);  
   
  
        if( !target ) target = offensive_target(me);  
  
        if( !target||!target->is_character()||!me->is_fighting(target) )  
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��" KUANG "��\n");  
          
        if( (int)me->query_skill("hongye-daofa",1) < 150)  
                return notify_fail("��Ŀǰ������ʹ����" KUANG "��\n");  
  
        if (!objectp(weapon = me->query_temp("weapon"))  
                || (string)weapon->query("skill_type") != "blade")  
                        return notify_fail("��ʹ�õ��������ԡ�\n");  
          
        if( (int)me->query("neili") < 800 )  
                        return notify_fail("�������������\n");  
          
        me->add("neili", -300);  
        msg = HIC "$N��ȻһЦ�����Ϳ�ݾ��׵ĵ�����Ȼ��ø���������\n"  
              HIC "������һ˲֮�䣬$N�ѿ��������������������ŷ磬���ﺬ�ŵ�Ӱ��\n"  
              HIC "$nֻ����������ֹͣ�ˣ�" NOR;  
  
        message_vision(msg, me, target);                  
                  
        message_combatd(HIY  "$N����������������\n" NOR, me, target);   
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
  
        message_combatd(HIY  "$N����$n����������������\n" NOR, me, target);   
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
  
        message_combatd(HIY  "$N��Ȼ�ִ���������������\n" NOR, me, target);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"), TYPE_REGULAR, msg);  
  
        me->start_busy(2 + random(2));  
        return 1;  
}  

