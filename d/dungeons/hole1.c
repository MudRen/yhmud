#include <room.h>
#include <ansi.h>

inherit ROOM;
int do_findway(string arg);

void create()
{
	set("short", "ħ���");
	
	set("long", @LONG
�����Ǵ�˵�е�ħ������������ɭɭ�ģ�ǽ�����ߵĴ��Ѳ�
֪����˭��ȼ�ˣ���������Χ�Ļ��������Ϻܸɲڵģ���һ����һ���
ɢ����һ��һ���Ĳ�֪��ʲô�����������ð�ɭɭ�Ĺ�ͷ�����Ż�ѻ�
�������������񾭱��������ƶ�����Ӱ���������ý����ģ��о�����
�ڰ���Ǳ����Σ�ղ��ɵ������ս������е�������
    �������(findway)Ѱ����һ�����ڡ�
LONG );
	
	set("outdoors", "dungeons");
	setup();
}

void init()
{
        add_action("do_findway", "findway");
}


int do_findway(string arg)
{
	string *ob1_list = ({
                "/clone/fam/gift/perwan",
                "/clone/fam/gift/kardan",
				"/clone/money/cash",
				"/clone/money/gold",
				"/clone/money/silver",
				"/clone/misc/jinchuang",
    });
        
    string *ob2_list = ({
                "/clone/fam/max/xuanhuang",
				"/clone/fam/max/longjia",
				"/clone/fam/max/tianshu1",
				"/clone/fam/max/tianshu2",
				"/clone/fam/obj/guo",
    });
	
	string gift;
    object item;
	
	object me, ob, *obs;
	int i, n, m, exp, lvl;
	me = this_player();
	obs = all_inventory(environment(me));
	obs = filter_array(obs, (: ! playerp($1) && living($1) :));
	exp = me->query("combat_exp");
	lvl = to_int(pow(to_float(exp * 10), 1.0 / 3));
	n = sizeof(obs);
		
	if (n < 1 && me->query_temp("dungeons_killed") > 8)
	{
		me->set_temp("dungeons_killed", 0);
		tell_object(me, HIY "\n��������ɢ��,��Լ�м������ڡ�\n" NOR);
		me->move(__DIR__"holen");
		/*set("exits", ([
		"north" : __FILE__,
		"south" : __FILE__,
		"east"  : __FILE__,
		"west"  : __FILE__,
		]));*/
		return 1;
	}
	else
	{
		tell_object(me, RED "ɱ��ɱ��ɱ��ֻ��ɱ¾����Ψһ��·��\n" NOR);
	}	
        
    if (n < 1 && me->query_temp("dungeons_killed") < 9)
	{		
		if (random(8) > 0)
		{
			m = 1;
			if (random(3) == 0) m = 2;
			for (i = 0; i < m; i++)
			{
			ob = new(CLASS_D("dungeons") + "/killer.c");
			NPC_D->set_from_me(ob, me, 100);
		
			ob->set("title", HIY "ħ����" NOR );
			ob->set("lvl", lvl);
			ob->add_temp("apply/dodge", lvl / 2);
			ob->add_temp("apply/parry", lvl / 2);
			ob->add_temp("apply/force", lvl / 2);
			ob->add_temp("apply/armor", lvl);
			ob->add_temp("apply/defence", lvl);
			ob->add_temp("apply/damage", lvl / 10);
			ob->add_temp("apply/unarmed_damage", lvl / 10);
			ob->move("/d/dungeons/hole1");
			}
			tell_object(me, HIW "��о���ߺ�����˸���Ӱ��\n" NOR);
		}
		else
		{
			if (random(200) > 1)
			{
				gift = ob1_list[random(sizeof(ob1_list))];
				item = new(gift);
				item->move(me);
				tell_object(me, HIW "��ͻȻ������һ" + item->query("unit") + item->name() +
                                HIW "��\n" NOR);
			}
			else
			{
				gift = ob2_list[random(sizeof(ob2_list))];
				item = new(gift);
				item->move(me);
				tell_object(me, HIW "��ͻȻ������һ" + item->query("unit") + item->name() +
                                HIW "��\n" NOR);
			}
		}
	}
	return 1;
}

/*
int valid_leave(object me)
{
	
	string dest;
	int total_steps = 5;
	
		
	dest = sprintf("/d/dungeons/hole%d", random(3) + 1);
	me->add_temp("dungeon/steps", random(2));
	me->move(dest);
	if (me->query_temp("dungeon/steps") == total_steps)
		{
			me->move(__DIR__"holen");
			me->delete_temp("dungeon/steps");
			write(HIY "�㾭����;���棬�����߳��˵����Թ���\n" NOR);
		}
	return -1;
}*/
