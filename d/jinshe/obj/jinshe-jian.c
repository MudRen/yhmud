// jinshe-jian.c α���߽�

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
	set_name(HIY"���߽�"NOR,  ({ "jinshe jian", "sword", "jian" }));
	set_weight(10000);
	if (clonep())
		//set_default_object(__FILE__);
		destruct(this_object());
	else {
		set("unit", "��");
		set("long", 
"�⽣�����ã������������ǳ��أ��������ǻƽ�����������
��������������һ��Ѫ�ۣ����������͵İ��⣬���ǹ��졣����
��״�������أ�������������һ�����������ɣ���β���ɽ�����
��ͷ���ǽ��⣬��������ֲ棬���Խ��⾹�����档\n");
		set("value", 200000);
		set("material", "gold");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������У���ʱȫ�����쬵�ֻ�к������ˡ�\n");
		set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
	}
	init_sword(70);
	setup();
}
