#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i; 

        i = me->query_skill("ruying-suixingtui", 1) / 4;

        if ( userp(me) && !me->query("can_perform/ruying-suixingtui/ruying"))
                return notify_fail("����ʹ�õ��⹦��û�������Ĺ��ܡ�\n");
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����Ӱ���Ρ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("ʹ�á���Ӱ���Ρ�ʱ˫�ֱ�����ţ�\n");

        if( (int)me->query_skill("ruying-suixingtui", 1) < 160 )
                return notify_fail("�����Ӱ�����Ȳ�����죬����ʹ�á���Ӱ���Ρ���\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���Ӱ���Ρ���\n");

        if( (int)me->query_dex() < 30 )
                return notify_fail("���������ǿ������ʹ�á���Ӱ���Ρ���\n");

        if (me->query_skill_prepared("unarmed") != "ruying-suixingtui"
        || me->query_skill_mapped("unarmed") != "ruying-suixingtui")
                return notify_fail("�������޷�ʹ�á���Ӱ���Ρ����й�����\n");
 
        if( (int)me->query("max_neili") < 2000 ) 
                return notify_fail("���������Ϊ̫��������ʹ�á���Ӱ���Ρ���\n");

        if( (int)me->query("neili") < 700 )
                return notify_fail("����������̫�٣�����ʹ�á���Ӱ���Ρ���\n"); 

        me->add("neili", -500);
      
        msg = YEL "\n������һ�����������ھ���˲ʱ������\n" NOR;
        message_vision(msg, me, target); 
       
        me->add_temp("apply/strength", i);
        me->add_temp("apply/dexerity", i);
        me->add_temp("apply/attack", i);
        me->add_temp("apply/damage", i);

        if (random((int)me->query("combat_exp")) > (int)target->query("combat_exp") / 2 
        &&  random((int)me->query_skill("force")) > (int)target->query_skill("force") / 2)
       { 
             msg = HIY "$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ�أ�"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);
        
             msg = HIY "������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n��"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1,msg);
 
             msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ������"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

             msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ�£�"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);

             msg = HIR"��ʱ$N˫��չ��������һ��ǿ�ҵ����磬˫����ʱ�벢������Ӱ���Ρ�һ�����ں���$n����֮�ϣ�"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);
        } else 
       {
             msg = HIY"$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ�أ�"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK,msg);
        
             msg = HIY"������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n��"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1,msg);
 
             msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ������"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"),TYPE_QUICK,msg);

             msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ�£�"NOR;
             COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1,msg);
        }
 
             msg = YEL "\n����������ʹ�꣬ȫ��һת���������ڵ��ϡ�\n" NOR;
               
             //me->add("neili", -400);
             me->add_temp("apply/dexerity", -i);
             me->add_temp("apply/damage", -i); 
             me->add_temp("apply/strength", -i);
             me->add_temp("apply/attack", -i);   
             me->start_busy(2+random(2));

        return 1;
}


