#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name("С�ɵ�", ({ "xiao feidao", "feidao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "Щ");
                set("value", 500);
                set("base_unit", "��");
                set("base_value", 100);
                set("base_weight", 1000);
                set("material", "steel");
                set("long", "һ��ѩ���ķɵ���\n");
                
        }
       set_amount(5);
       init_throwing(15);
       setup();
}