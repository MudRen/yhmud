#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ����ʥ�����������Լ���ս������\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("shenghuo-shengong", 1);
        me->add("neili", -150);
        message_combatd(HIM "$NĬ��ʥ���񹦣���ɫ���ɻƷ��ϣ����������Ϸ��������������죬����ֻ�"
                        "��Ϊ��ɫ����Ϊ���졣\n" NOR,me);
        me->add_temp("apply/attack", skill * 1 / 3);
        me->add_temp("apply/dodge", skill * 1 / 3);
        me->add_temp("apply/parry", skill * 1 / 3);
        me->set_temp("powerup", 1);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 1 / 3 :), skill);
        if (me->is_fighting()) me->start_busy(1 + random(3));
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount);
                me->add_temp("apply/dodge", -amount);
                me->add_temp("apply/parry", -amount);
                me->delete_temp("powerup");
                tell_object(me, "���ʥ����������ϣ����������˿������������ջص��\n");
        }
}

