#include <ansi.h>
#include <combat.h>

#define TUN "��" HIR "ȼľ����" NOR "��"

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail(TUN "������õ���ʩչ��\n");

        if (me->query_temp("zhen_yan"))
                return notify_fail(TUN "�޷�����ʩչ��\n");

        if ((int)me->query_skill("ranmu-daofa", 1) < 180)
                return notify_fail("���ȼľ������Ϊ����������ʩչ" TUN "��\n");

        if (me->query("max_neili") < 2500)
                return notify_fail("���������Ϊ���㣬����ʩչ" TUN "��\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong"))
                return notify_fail("������û�м��������ڹ�Ϊ�ڹ�������ʩչ" TUN "��\n");
        if (me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("��û�м���ȼľ����Ϊ����������ʩչ" TUN "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ��������㣬����ʩչ" TUN "��\n");


        msg = HIY "$N" HIY "˫�ֳֵ���������������ʩ����ȼľ������ѧ��"
              HIR "ȼľ����" HIY "������ʱ��Х������������һ�������ޱȵ��"

              "��$N" HIY "����ӿ�����ƹ���$N" HIY "��ȥ��\n" NOR;
        message_sort(msg, me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("ranmu-daofa",1);
        me->set_temp("zhen_yan", 1);       
        me->add_temp("apply/attack", skill * 2 / 5);
        me->add_temp("apply/defense", skill * 2 / 5);
        me->add_temp("apply/damage", skill / 4);
        me->add("neili", -400);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if (me->query_temp("zhen_yan"))
        {
                me->add_temp("apply/attack", -(skill * 2 / 5));
                me->add_temp("apply/defense", -(skill * 2 / 5));
                me->add_temp("apply/damage", -(skill / 4));
                me->delete_temp("zhen_yan");

                tell_object(me, "�㾭��������Ϣ���ֿ��Լ���ʩչ��" HIR "ȼľ����" NOR "���ˡ�\n");
        }
}

