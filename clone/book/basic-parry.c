// basic_parry.c

inherit BOOK;

void create()
{
	set_name("�м�����", ({ "parry book", "book" }));
	set_weight(600);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"������д�����м����š�\n");
		set("value", 200);
		set("material", "paper");
		set("skill", ([
			"name": 	"parry",
			"exp_required":	1000,
			"jing_cost":	20,
			"difficulty":	20,
			"max_skill":	19,
		]));
	}
}
