//TASK��Ʒ
//Ϲ��������


#include <ansi.h>

#define  SET_TASK   "/adm/daemons/task/set_task"

inherit ITEM;


void create()
{
        set_name(HIM "��֬ˮ��" NOR, ({ "yanzhi"}));
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "��");
                set("owner_id", "aqing sao");
                set("owner", "����ɩ");

                set("value",10);
                set("no_sell",1);
                set("no_put",1);
        }
        setup();
}

void init()
{
	add_action("do_give","give");
}


int do_give(string arg)

{

	object me,ob;

	ob = this_object();
	me = this_player();

    return call_other(SET_TASK, "do_return", ob, me, arg);

}

string long()
{
        return "����" + query("owner") + "��" + query("name") +
               "(" + query("id") + ")��\n";

}

