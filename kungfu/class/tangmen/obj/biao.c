#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "���Ӹ���" NOR, ({"qizi gangbiao"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "����һö�Ĵ��������Ƶĸ��ڣ������ޱȡ�\n");
                set("value", 21);
                set("unit", "ö");
        }
        setup();
}
