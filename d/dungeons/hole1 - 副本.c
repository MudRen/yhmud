#include <room.h>
#include <ansi.h>
//inherit F_DBASE;
inherit ROOM;

void create()
{
	set("short", "�����㳡");
	set("no_sleep_room",1);
	set("outdoors", "dungeons");
	set("no_clean_up", 0);
	setup();
	//replace_program(ROOM);
	call_out("main", 10);
	
}

void main()
{
	object me, *obs;
	object ob;
	object room;
	int i, exp;
	int lvl, num;
	
	me = this_player();
	obs = all_inventory(environment(me));
	obs = filter_array(obs, (: ! playerp($1) && living($1) :));
	
	room = environment(me);
	exp = me->query("combat_exp");
	lvl = to_int(pow(to_float(exp * 10), 1.0 / 3));
	
	num = 1;
	if (random(3) == 0) num = 2;
	//me->set_temp("migong", 1);
	if (sizeof(obs) < 10 && me->query_temp("migong"))
	{
		call_other(__FILE__, "creat_npc", lvl, num);
		remove_call_out("main");
		call_out("main", 30);//30��ˢ��
	}
	else
	{
		tell_object(me, HIW "\n����ɱ�У��������죬�㻹���߰ɡ�\n" NOR);
		remove_call_out("main");
		me->move("/d/city/wumiao");
		me->delete("temp/migong");
		destruct(room);
	}	
}

void creat_npc(int lvl, int num)
{
	object room, me, ob;
	int i, exp;
		
	me = this_player();
	room = environment(me);
	exp = me->query("combat_exp");
	lvl = to_int(pow(to_float(exp * 10), 1.0 / 3));
		
	for (i = 0; i < num; i++)
	{
		ob = new(CLASS_D("dungeons") + "/killer.c");
		NPC_D->set_from_me(ob, me, 100);
		
		ob->set("title", HIY "СϺ��" NOR);
		ob->set("lvl", lvl);
		ob->add_temp("apply/dodge", lvl / 2);
		ob->add_temp("apply/parry", lvl / 2);
		ob->add_temp("apply/force", lvl / 2);
		ob->add_temp("apply/armor", lvl);
		ob->add_temp("apply/defence", lvl);
		ob->add_temp("apply/damage", lvl / 10);
		ob->add_temp("apply/unarmed_damage", lvl / 10);
		ob->move(room);
		ob->kill_ob(me);
	}
	tell_object(me, HIW "��о���ߺ�����˸���Ӱ��\n" NOR);
}


