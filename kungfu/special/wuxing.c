
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "����ת��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("����ת��ʱ����������Ͷ̥ת������\n"
                           "ȡ�����Ǹ���ת����ӵ�г���û�е�\n"
                           "��ѧ����������ת����ӵ�иü��ܿ�\n"
                           "���������ѧ�о��ٶȰٷ�֮��ʮ��\n"
                           "������ѧ��ϰ�ٶ���߰ٷ�֮��ʮ��\n"
                           "��ѧ������ȡ�ٶ���߰ٷ�֮��ʮ��\n");
}
