// tanghua.c
#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "�ƻ�" NOR, ({"tang hua", "hua" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR"����һ��������������꼻����������磬����һ��֮�£��Ͷ������ǡ�\n"NOR);
                set("unit", "ö");
                set("value", 21);
        }
        setup();
}
