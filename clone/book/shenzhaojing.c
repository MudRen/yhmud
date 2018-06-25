// shenzhao-jing.c

#include <ansi.h>

inherit BOOK;

void create()
{
        set_name(MAG "���վ�" NOR, ({ "shenzhao jing", "jing", "book"})); 
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ź���ͨ��ֽ�����泭¼��һЩ�ھ����ƺ���һ"
                            "�ֽ������վ�\n�ľ����书���ϡ�\n");
                set("material", "paper");
                set("skill", ([
                        "name"        :  "shenzhaojing",
                        "exp_required":  100000,
                        "jing_cost"   :  30,
                        "difficulty"  :  25,
                        "max_skill"   :  200,
                ]));
        }
}
