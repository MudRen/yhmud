// gangbiao.c
#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("��ĸ�ػ���", ({"hhbiao", "biao" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "����һ���������Ƶĸ��ڣ��������\n");
                set("unit", "Щ");
                set("base_value", 1);
                set("material", "steel");
                set("base_unit", "ö");
                set("base_weight", 10);
        }
        set_amount(1);
        init_throwing(100);
        setup();
}
