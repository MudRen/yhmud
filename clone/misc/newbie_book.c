// newbie.c

#include <ansi.h>
#include <command.h>

inherit ITEM;

void create()
{
        set_name(HIY "�����⴫" NOR, ({ "heros book", "book" }) );
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIY "һ����֪��ɶ�����Ƴɵ��飬���顾�����⴫���ĸ����֡�\n" NOR
                            HIC "�Ȿ������������ָ�ϣ���������ϸ�Ķ���read book����\n" NOR);
                set("unit", "��");
				//set("value", 5000);
				set("material", "paper");
        }
}

void init()
{
        add_action("do_du", "read");
}

int do_du(string arg)
{
		if (arg == "book")
			return HELP_CMD->main(this_player(), "feature");
		return 0;
}

