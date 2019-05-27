// from NT MudLIB
// ziqi.c ��������

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
//      string msg;
//      mapping buff,data;
        int /*d_count,count,*/ qi, maxqi, skill;
		object weapon = me->query_temp("weapon");
		skill = me->query_skill("zixia-shengong", 1);

        if((int)me->query_temp("ziqi"))
				return notify_fail(HIG"���Ѿ����������������ˡ�\n");

        if((int)me->query("neili") < 200 )
                return notify_fail("���������������\n");

        if(skill < 150)
                return notify_fail("�����ϼ�񹦵���Ϊ����������ʹ����������! \n");

        // �����б������ӱ�������
		if ( ! weapon || weapon->query("skill_type") != "sword" )
				return notify_fail("��û�н�.��ô����������ѽ? \n");

        qi = me->query("qi");
        maxqi = me->query("max_qi");
		
		message_combatd(MAG "$N" MAG "����һ����������������ʢ�����еı�������͸��һ���Ϲ⡣����\n" NOR, me);
		
        if( qi > (maxqi * 0.4) )
        {
                me->add_temp("apply/damage", skill / 10);
				me->add_temp("apply/sword", skill / 10);
				me->set_temp("ziqi", 1);
				me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 10 :), skill);
				me->add("neili", -200);
        }
        else
        {
                message_combatd(HIR "$N" HIR "ƴ�����������������������������Լ�����̫�أ�û�ܳɹ�!\n" NOR, me);
        }
        
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("ziqi"))
        {
                me->add_temp("apply/damage", -amount);
                me->add_temp("apply/sword", -amount);
                me->delete_temp("ziqi");
                tell_object(me, "�����������������ϣ�����������ȥ��\n");
        }
}