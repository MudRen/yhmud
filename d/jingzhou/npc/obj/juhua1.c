#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�̾ջ�" NOR, ({ "lv juhua", "juhua" }));
        set("weight", 100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","һ�赭�̵ľջ�����������ˮ�̲�����\n");
                set("unit", "��");
                set("material", "wood");
        }
        setup();
}       

