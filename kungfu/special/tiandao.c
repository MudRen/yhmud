

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "�������" NOR; }

int perform(object me, string skill)
{
        if ((me->query("int") < 26 || me->query("special_skill/qinzong")) && me->query_skill("zuoyou-hubo", 1) < 360 )
                me->set_skill("zuoyou-hubo", 360);

        return notify_fail("��û�й��˵Ĳ��ǣ�������һ���㶼�ڿҷܶ�����\n"
                           "����춯�أ�����ش���˵��񼼡����ؼ�ʹ�ú�\n"                          
                           "�ɵõ����һ���������ʮ����ע�⣺���ؼ�������\n"
                           "�����Դ���25�����50����޷�����ʹ�ã�\n");
}
