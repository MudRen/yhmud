

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "��а����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("���ֻ�ʱ���Ե�ɺϣ����ɵõ��������ӣ�\n"
                           "�Ӷ��ٶ����֣���а�޷����д��ؼ��߲���\n"
                           "��ʹ֮�࣬�޶���֮�֣�������ֹ�������\n"
                           "Ҳ������׾١�\n");
}