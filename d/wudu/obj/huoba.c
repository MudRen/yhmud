// huoba.c

#include <weapon.h>
 

inherit SWORD;

void create()
{
        set_name("���",({ "huo ba" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "֧");
                set("value", 10000);
                set("material", "wood");
                set("long", "����֧��ѡ�\n");
                set("wield_msg", "$N�ó�һ��$n���������С�\n");
                set("unequip_msg", "$N�������е�$n��\n");
        }
           init_sword(5);
        setup();
}

