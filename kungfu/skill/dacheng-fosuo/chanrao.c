#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon = me->query_temp("weapon");

        //if (!wizardp(me) && ! me->query("can_perform/dacheng-fosuo/chanrao")) 
        //        return notify_fail("����ʹ�õ��⹦��û��������ܣ�\n");
        
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("���ƾ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill("dacheng-fosuo",1) < 80)
                return notify_fail("��Ĵ�˷�����������죬����ʹ�ò��ƾ���\n");

        if( !weapon 
        ||      weapon->query("skill_type") != "whip"
        ||      me->query_skill_mapped("whip") != "dacheng-fosuo" ) 
                return notify_fail("�������޷�ʹ�ò��ƾ���\n");

        if( me->query("neili") < 500 )
                return notify_fail("�������������\n");

        if( target->is_busy() )
        return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

          me->start_perform( 5, "���ƾ�");
    msg = HIG "$Nʹ�����ƾ�������һ����$n��˫�Ⱦ�ȥ��\n";

        me->start_busy(random(2));
        if((random(me->query("combat_exp")) > target->query("combat_exp")/2) 
                ||      (random(me->query_dex()) > target->query_dex()/2))
        {
        msg += HIY "���$p��$Pһ�������ȱ����ʵʵ�����������ڵ����޷�����\n" NOR;
                target->start_busy((int)me->query_skill("dacheng-fosuo",1)/20+2);

        } 
        else {
                msg += HIW "����$p������$P�Ĳ��ƾ�������һԾ��㿪�ˡ�\n" NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);
        
        me->add("neili", -200);
        return 1;
}

