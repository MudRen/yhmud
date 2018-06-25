#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if ((int)me->query_temp("dujiang"))
                return notify_fail("���Ѿ�����һέ�ɽ����ˡ�\n");

        if ((int)me->query_skill("yiwei-dujiang", 1)< 150)
                return notify_fail("���һέ�ɽ��ȼ�����������ʩչ���������\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong")) 
                return notify_fail("������û�м��������ڹ�Ϊ�ڹ�������ʩչ"  "��\n"); 
        if ((int)me->query_dex() < 30)
                return notify_fail("���������ʹ�á�һέ�ɽ���������\n");

        if ((int)me->query_skill("force", 1)< 150)
                return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

        if ((int)me->query_skill("dodge", 1)< 150)
                return notify_fail("����Ṧ��Ϊ����������ʹ�ô��������\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("���������Ϊ����ʹ�á�һέ�ɽ�����\n");

        if ((int)me->query("neili") < 250)
                return notify_fail("���ʱ���������㣡\n");

        msg = HIB "$N" HIB "�������ָ����ڹ���ʩչ��һέ�ɽ�������,"
                  "����һչ�������˶�ʱ���Ʈ��������Խ��Խ�ᡣ\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("yiwei-dujiang", 1);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->set_temp("dujiang", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        me->add("neili", -200);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("dujiang"))
        {
                me->add_temp("dex", -amount);
                me->delete_temp("dujiang");
                tell_object(me, "��ġ�һέ�ɽ����˹���ϣ��������ջص��\n");
        }
}

