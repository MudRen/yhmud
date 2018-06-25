// basic_whip.c

inherit BOOK;

void create()
{
	set_name("�޷�����", ({ "whip book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����޷����š�\n");
		set("value", 200);
		set("material", "paper");
		set("skill", ([
			"name": 	"whip",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	19,
		]));
	}
}
