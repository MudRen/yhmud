// boots.c ����ѥ
 
#include <armor.h>
#include <ansi.h>
 
inherit BOOTS;
 
void create()
{
        set_name(HIR "����ѥ" NOR, ({ "qilin xue", "xue", "boots" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "leather");
		set("unit", "˫");
		set("long", HIR "����һ˫��������Ƥ����Ƥѥ����˵���Ը����������Ա����㲿��\n" NOR);
		set("value", 100000);
		set("armor_prop/dodge", 80);
	}
	setup();
}
