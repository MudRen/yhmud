
#include <room.h>
#include <ansi.h>

inherit ROOM;
int do_summons(string arg);

void create()
{
	set("short", "ħ����һ����");
	
	set("long", @LONG
������ħ���ĵ�һ�㣬����������ɭɭ�ģ�ǽ�����ߵĴ��Ѳ�
֪����˭��ȼ�ˣ���������Χ�Ļ��������Ϻܸɲڵģ���һ����һ���
ɢ����һ��һ���Ĳ�֪��ʲô�����������ð�ɭɭ�Ĺ�ͷ�����Ż�ѻ�
�������������񾭱��������ƶ�����Ӱ���������ý����ģ��о�����
�ڰ���Ǳ����Σ�ղ��ɵ������ս������е�������
    ����������ٻ�(kboss)Сboss��
LONG );
	set("exits", ([
		//"enter"  : __FILE__,
	]));
	set("outdoors", "dungeons");
	setup();
}

void init()
{
        add_action("do_summon", "kboss");
}

int do_summon(string arg)
{

	
	object me, ob;
	int i, m, lvl, exp;
	me = this_player();
	

	exp = me->query("combat_exp");
	lvl = to_int(pow(to_float(exp * 10), 1.0 / 3));
	lvl += lvl * 0.2;
	
	if (me->query_temp("dungeons_killer1"))
		return notify_fail(RED "ɱ��ɱ��ɱ��ֻ��ɱ¾����Ψһ��·��\n" NOR);
	
    
	m = 1;
	if (random(4) == 0) m = 2;
	for (i = 0; i < m; i++)
	{
		ob = new(CLASS_D("dungeons") + "/killer1.c");
		NPC_D->set_from_me(ob, me, 100);
		
		ob->set("title", HIY "ħ���СͷĿ" NOR );
		ob->set("lvl", lvl);
		ob->add_temp("apply/dodge", lvl / 2);
		ob->add_temp("apply/parry", lvl / 2);
		ob->add_temp("apply/force", lvl / 2);
		ob->add_temp("apply/armor", lvl);
		ob->add_temp("apply/defence", lvl);
		ob->add_temp("apply/damage", lvl / 6);
		ob->add_temp("apply/unarmed_damage", lvl / 6);
		
		ob->move("/d/dungeons/holen");
		me->set_temp("dungeons_killer1", 1);
	}
		tell_object(me, HIW "��о���ߺ�����˸���Ӱ��\n" NOR);
		
	return 1;
}
	
	
	
