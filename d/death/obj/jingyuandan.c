#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED "��Ԫ��" NOR, ({ "jingyuan dan", "jingyuan", " dan"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "һ�����ص��񵤣�ɢ��������Ѫ�⡣\n" NOR);
                set("unit", "��");
                set("value", 20000);
        }
}
