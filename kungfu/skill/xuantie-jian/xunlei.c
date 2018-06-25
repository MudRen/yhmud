
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int j, z;
        object weapon;
        
        /*
        if (userp(me) && ! me->query("can_perform/xuantie-jian/xunlei"))
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչ��Ѹ�׻�����\n");
        */
                        
        j = me->query_skill("xuantie-jian", 1);
        z = me->query_skill("surge-force", 1);
 
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��Ѹ�׻���ֻ����ս���жԶ���ʹ�á�\n");

       if (!weapon || weapon->query("skill_type") != "sword")
                return notify_fail("�������ʹ�ý�ʱ����ʹ����Ѹ�׻�����\n");
                
        //if (me->query_skill_mapped("parry") != "xuantie-jian")
        //        return notify_fail("��Ļ����мܱ�������������ʱ����ʹ����Ѹ�׻�����\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("����뼤��������������ʹ����Ѹ�׻�����\n");
                
        if(me->query_skill("xuantie-jian", 1) < 160 )
                return notify_fail("�������������������죬ʹ������Ѹ�׻�����\n");

        if(me->query_skill("surge-force", 1) < 160 )
                return notify_fail("���ŭ��������Ϊ������ʹ������Ѹ�׻�����\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("����ڹ��ȼ�������ʹ������Ѹ�׻�����\n");

        if( (int)me->query_str() < 45)
                return notify_fail("���������������ʹ������Ѹ�׻�����\n");

        if( (int)me->query_dex() < 30)
                return notify_fail("�������������ʹ������Ѹ�׻�����\n");                                                                               

        if( (int)me->query("max_neili") < 2000 )
                return notify_fail("����������̫����ʹ������Ѹ�׻�����\n");      

        if( (int)me->query("neili") < 900 )
                return notify_fail("����������̫����ʹ������Ѹ�׻�����\n"); 

        me->add_temp("apply/str", z / 10);
        me->add_temp("apply/attack", j / 3); 
 
        msg = BLU "\n$N�����е�"+weapon->name()+"������$nһѹ����Ȼ����һ���� һ����Ϊ���������籼�׳��繥��$n��\n\n"NOR;
        message_combatd(msg, me, target);
        
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
 

        me->add("neili", -500);
        
        me->add_temp("apply/str", -z / 10);
        me->add_temp("apply/attack", -j / 3);

        me->start_busy(3);
        if( !target->is_busy() )
                target->start_busy(1);
        return 1;
}

