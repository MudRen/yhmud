//changjian.c 

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("����", ({"sword", "changjian", "jian", "sword"}));
        set_weight(5000);
	if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", "����һ�������ľ��ֽ������ڷ����ޱȡ�\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
        	set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }

	init_sword(25);
	setup();
}