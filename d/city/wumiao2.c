#include <ansi.h>
#include <room.h>
#include <festival.h>
inherit ROOM;

void create()
{
	set("short", "�����¥");
	set("long", @LONG
������������Ķ�¥�����﹩�������ɵĳ������ƺ�����
���ܣ�����������������Ӣ����������˵���׻�����Ĵ�ͳ
�ڼ�����������(pray)��õ�ף����
LONG);
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_beg", 1);
	set("no_sleep_room", 1);

	set("exits", ([
                  "down" : __DIR__"wumiao",
	              ]));

	set("objects", ([
	                    "/adm/daemons/task/npc/zixu" : 1,
	                ]));
	setup();
}

void init()
{
	add_action("do_pray", "pray");
}

int do_pray(string arg)
{
	object me = this_player();
	int exp, pot, day, month, *date, exp0, exp1;
	date = localtime(time());
	month = date[4] + 1;
	day = date[3];
	exp = me->query("combat_exp");
	exp0 = me->query("experience");
	exp1 = me->query("learned_experience");

	if (me->is_busy())
	{
		return notify_fail("��������æ���أ�û��������������\n");
	}

	message_vision(HIG "\n$N" HIG "��������ǰ�����������Ŀ���������ͷ��Ȼ��ĬĬ�����š�\n" NOR, me);
	/*
	        if (me->query("festival/15.5.1"))
	        {
	             me->delete("festival");
	             log_file("static/log", sprintf("%s(%s) ɾ��festival��¼�� %s.\n",
	                      me->name(1), me->query("id"), ctime(time())));
	        }
	*/
	if (month == FETEMONTH && day >= BEGIN_DAY && day <= END_DAY)
	{
		if (me->query(FESTIVAL) == day)
		{
			if (day == END_DAY)
				tell_object(me, HIR "���Ѿ���ף�����ˣ����´νڼ��������ɡ�\n" NOR);
			else
				tell_object(me, HIR "������Ѿ���ף�����ˣ������������ɡ�\n" NOR);
			return 1;
		}
		if (me->query("potential") > me->query_potential_limit())
		{
			tell_object(me, HIB "��о��Լ��������ã��ɲ�֪��Ϊʲôû��Ч����\n" NOR);
			return 1;
		}

		if (exp >= 800000)
			pot = 3000 + random(9)*100;
		else if (exp >= 350000)
			pot = 2000 + random(6)*100;
		else if (exp >= 100000)
			pot = 1500 + random(3)*100;
		else
			pot = exp / 100 + 100;
		//pot /= 2;
		me->add("potential", pot);
		if (! me->query("skybook/guard/death"))
			me->set("skybook/guard/death", 1);
		me->set(FESTIVAL, day);
		message_vision(HIW "ڤڤ֮�к�����һ������������" HIR "ף$N" HIR + FETEDAY "��Ϸ����" HIW "��\n" NOR, me);
		tell_object(me, HIY "ֻ��һ��������֣���õ�����ף���������" + chinese_number(pot) + "��Ǳ�ܡ�\n" NOR);
		me->start_busy(5);
		return 1;
	}

	if (! me->query("skybook/guard/death") &&
	        (exp < 100000 || random(exp / 100) < me->query("kar")))
	{
		me->set("skybook/guard/death", 1);
		me->start_busy(10);
		message_vision(HIW "\n$N" HIW "���Ϸ���һ�㵭���İ׹⣬�Ե�����Ī�⡣\n" NOR, me);
		tell_object(me, HIY "������õ���Ӧ���ܵ�����Ļ��ӡ�\n" NOR);
		return 1;
	}

	if ( exp0 < exp1 )
	{
		me->set("learned_experience", exp0);
		me->start_busy(10);
		message_vision(HIC "\n$N" HIW "���Ϸ���һ�㵭���Ĺ�â���Ե�����Ī�⡣\n" NOR, me);
		tell_object(me, HIY "������õ���Ӧ���о������ա�\n" NOR);
		return 1;
	}

	tell_object(me, HIB "��о��Լ�����û���κ�Ч����\n" NOR);
	me->start_busy(1 + random(10));
	return 1;
}

