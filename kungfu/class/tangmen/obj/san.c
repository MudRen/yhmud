// san.c
#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG"ɢ����Ů" NOR, ({"sanhua tianyu"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "����һö�Ĵ��������Ƶİ���ɢ����Ů�������ޱȡ�\n");
                set("unit", "ö");
                set("value", 21);         
        }
        setup();
}

