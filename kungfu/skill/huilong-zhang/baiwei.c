#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg; 
        object weapon;
        int extra;
        int count, i;

        extra = me->query_skill("huilong-zhang",1) + me->query_skill("staff", 1);    
                  
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��������β��ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(me->query_temp("weapon") || (string)weapon->query("skill_type") != "staff"))
                return notify_fail("ʹ�á�������β��ʱ˫��Ӧ�ó��ȣ�\n");

        if( (int)me->query_skill("huilong-zhang", 1) < 80 )
                return notify_fail("��Ļ����Ȳ�����죬����ʹ�á�������β����\n");

        if( (int)me->query_skill("shaolin-xinfa", 1) < 80 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�������β����\n");
     
        if( (int)me->query("neili") < 600 )
                return notify_fail("����������̫��������ʹ�á�������β����\n");

        msg = HIY "$N��Хһ�����������������и��ȣ�ͻȻһ��ת�����и��ȵ���$n��\n" NOR;

        message_vision(msg, me, target); 

        count = 4;
           
        for (i=0;i < count;i++)
        {
           COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
        }

        me->add("neili", -100 );

        me->start_busy(1+random(2));

            return 1;
}

