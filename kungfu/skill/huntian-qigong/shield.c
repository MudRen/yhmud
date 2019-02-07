// shield.c ������

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���û��������������Լ��ķ�������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�������������\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 200)
                return notify_fail("��Ļ���������Ϊ������\n");

        if ((int)me->query_temp("shield"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("huntian-qigong", 1) +
				me->query_skill("checking", 1) +
				me->query_skill("begging", 1);
        me->add("neili", -100);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "ʹ������������ѧ����Ԫ�����һ�ɰ���"
                        "�Զ������跢ɢ���£�ȫ�������ڰ�ɫ�����У�\n" NOR, me);
						

        me->add_temp("str", skill / 40);
		me->add_temp("dex", skill / 40);
        me->set_temp("shield", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 40 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
                me->add_temp("str", -amount);
				me->add_temp("dex", -amount);
                me->delete_temp("shield");
                tell_object(me, "��Ļ�������������ϣ���ɫ�ı�����ɢȥ��\n");
		}
}
