

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "ѭӰ����" NOR; }

int perform(object me, string skill)
{
        if (me->query_skill("count", 1) < 300)
                me->set_skill("count", 300);

        if (me->query_skill("mathematics", 1) < 300)
                me->set_skill("mathematics", 300);

        return notify_fail("����ת���������ݹ����󣬲����������������\n"
                           "���أ�������̬�����۵ף��˺����ܵ�����ж��\n"                          
                           "֮�����Ի�ʹ�ú�ɵõ��������Լ��������ټ���\n"
                           );
}
