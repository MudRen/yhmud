// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "freezingbc"; }

string chinese_name() { return "���Ϻ���"; }

string update_msg_others()
{
        switch (random(3))
        {
        case 0:
                return HIW "$N" HIW "������ͻȻһ�Σ���ɫ��ò԰ף����ݲ�ס�Ĵ����\n" NOR;

        case 1:
                return HIW "$N" HIW "΢΢����һ��������ʹ���쳣��\n" NOR;

        default:
                return HIW "$N" HIW "������һ�£�������������һ���˪��\n" NOR;
        }
}

string update_msg_self()
{
        return HIG "��Ȼ����һ���䣬������������\n" NOR;
}

string die_reason()
{
        return "������������������";
}
