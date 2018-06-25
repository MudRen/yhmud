#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;
        
        if (userp(me) && ! me->query("can_perform/jinzhong-zhao/zhao"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");      

        if ((int)me->query("neili") < 400)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("jinzhong-zhao", 1) < 150)
                return notify_fail("���[������]��Ϊ������\n");

        if ((int)me->query_temp("jinzhongzhao"))
                return notify_fail("���Ѿ�����[������]��Ϊ�������ˡ�\n");

	      if ((int)me->query_temp("jingangbuhuai"))
                return notify_fail("���Ѿ������ղ����������ˡ�\n");
                
        if ((int)me->query_temp("special/jinshen"))
                return notify_fail("���Ѿ�������ħ����֮���ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", -300);
        me->receive_damage("qi", 0);

        message_combatd(HIW "ֻ��$N" HIW "���챩��һ����ȫ����Ȼһ����һ����������Ѹ���ξ���"
                            "����סȫ��\n�漴���������ܣ�ɲʱ�����ܷ�ɳ��ʯ���̳�����!��\n" NOR, me);

        //me->add_temp("apply/armor", skill / 3);
        me->add_temp("apply/armor", skill / 2);
        me->add_temp("apply/force", skill / 4);
        me->set_temp("jinzhongzhao", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("jinzhongzhao"))
        {
                me->add_temp("apply/armor", -(amount / 2));
                me->add_temp("apply/force", -(amount / 4));
                me->delete_temp("jinzhongzhao");
                tell_object(me, "���[������]������������ϣ��������ջص��\n");
        }
}

