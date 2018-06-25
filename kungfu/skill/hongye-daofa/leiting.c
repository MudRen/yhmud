#include <ansi.h> 
#include <combat.h> 
 
#define LEITING "��" HIR "��������" NOR "��"  
 
inherit F_SSERVER; 
 
int perform(object me, object target) 
{ 
        string msg; 
        int extra; 
        object weapon; 
        int damage; 
 

        if(me->is_busy()) 
                return notify_fail("������û�գ���\n"); 
        if( (int)me->query_skill("hongye-daofa",1) < 80) 
                return notify_fail("��Ŀǰ������ʹ����" LEITING "��\n"); 
         
        if (!objectp(weapon = me->query_temp("weapon")) 
                || (string)weapon->query("skill_type") != "blade") 
                        return notify_fail("��ʹ�õ��������ԡ�\n"); 
        if( (int)me->query("neili") < 500 ) 
                 return notify_fail("�������������\n"); 
 
        if( !target ) target = offensive_target(me); 
 
        if( !target 
                ||      !target->is_character() 
                ||      !me->is_fighting(target) ) 
                return notify_fail(LEITING "ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 
         
        weapon = me->query_temp("weapon"); 
        damage = me->query_skill("hongye-daofa", 1) + random((int)me->query_skill("dodge")) / 2; 
        extra = me->query_skill("hongye-daofa",1) / 10; 
 
        me->add_temp("apply/attack", extra);     
        me->add_temp("apply/damage", extra); 
 
        msg = HIR  "\n$N���е�"+ weapon->name() +HIR"�ó����쵶�ƣ�" +  
                   weapon->name() +  
              HIR  "���Ƶ��ƣ�����������Ļ���$n��\n" NOR; 
        message_vision(msg, me, target); 
 
        if (random(10) > 4) 
        { 
                me->add("neili", -50); 
                msg = COMBAT_D->do_damage(me,target, WEAPON_ATTACK, damage, 30,     
                       HIC  "\n$N�������Ʊ���ǰ����һ�㣬�����Ŵ̶��ļ�����ֱ��$n��ȥ��\n" NOR); 
                message_combatd(msg, me, target); 
        } else 
        { 
                message_combatd(HIC  "\n$n���˷�������$N�ӵ�֮ǰ�Ƶ�����ʹ��$N���ò��ջ����߳ɵ�������\n" NOR, me, target); 
                COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR, msg); 
        } 
 
        me->add_temp("apply/attack", -extra); 
        me->add_temp("apply/damage", -extra); 
 
        me->start_busy(1); 
                return 1; 
} 

