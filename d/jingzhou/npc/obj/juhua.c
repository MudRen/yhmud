#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(MAG "Ұ�ջ�" NOR, ({ "ye juhua", "juhua" }));
        set("weight", 10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","һ��ƽƽ������Ұ�ջ�����ζ�����ġ�\n");
                set("unit", "��");
                set("material", "wood");
        }
        setup();
}       


