// ��������

#include <ansi.h>

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("��������ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("longxing-jian", 1) < 150)
                return notify_fail("������ν���������죬����ʹ���������֡�\n");
        
        if ((int)me->query_skill("buddhism", 1) < 150)
                return notify_fail("��ķ���Ϊ������죬����ʹ���������֡�\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("���Ѿ���ƣ���ߣ����������ˡ�\n");

        if ((int)me->query_temp("xian") >= 50)
                return notify_fail("���Ѿ�������̫���ˣ������Ѿ�����ˡ�\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->start_busy(1);
        message_combatd(HIR "ֻ��$N" HIR "���������дʣ��������������"
                        "����$N���У�\n" NOR, me);

        me->add_temp("apply/attack", 2);
        me->add_temp("apply/dodge", 1);
        me->add_temp("apply/parry", 1);
        me->add_temp("xian", 1);

        return 1;
}

