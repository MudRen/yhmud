// fuyun.c ����

#include <ansi.h>
#include <command.h>
#include <config.h>
#include <getconfig.h>

inherit NPC;

int do_answer();
int do_list();
int do_duihuan(string);

mapping convert_list = ([
	1:			({"/clone/fam/gift/str3", 1000, 0}),
	2:			({"/clone/fam/gift/int3", 1000, 0}),
	3:			({"/clone/fam/gift/con3", 1000, 0}),
	4:			({"/clone/fam/gift/dex3", 1000, 0}),
	5:			({"/clone/fam/item/yanluo", 1000, 0}),
	6:			({"/clone/fam/item/lihuo", 1000, 0}),
	7:			({"/clone/fam/item/qiankun_stone", 1000, 0}),
	8:			({"/clone/fam/max/tianshu2", 3000, 0}),
	9:			({"/clone/fam/max/tianshu1", 5000, 0}),
	10:			({"/clone/fam/obj/guo", 6666, 0}),
	11:			({"/clone/fam/max/longjia", 8888, 0}),
	12:			({"/clone/fam/max/xuanhuang", 8888, 0}),
	13:			({"/clone/fam/item/bless_water", 9999, 0}),
	14:			({"/d/item/obj/tiancs", 99999, 0}),
	15:			({"/d/death/obj/qise", 99999, 0}),
	16:			({"/d/death/obj/tianjing", 999999, 0}),
]);

void create()
{
	set_name("����", ({ "fu yun","fu", "yun" }));
	set("title", HIC"�Ź�����"NOR);
  set("nickname", HIY "�������" NOR);
	set("gender", "����");
	set("age", 60);
	set("str", 100);
	set("long", "һ�ж��Ǹ��ơ�\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("higgling", 500);
	set_temp("apply/damage", 15);

	set("combat_exp", 800000);
	set("attitude", "friendly");

        set("inquiry", ([
                "�Ź�" : (: do_answer :),
                "����" : (: do_answer :),
                "���ɹ���" : (: do_answer :),
        ]));

	setup();
	set_max_encumbrance(100000000);
}

void init()
{
        add_action("do_duihuan", "duihuan");
		add_action("do_list", "list");
}

int do_answer()
{
        write(name() + "�����������˵�������ɽ�����Ʒ�����ﶼ�У����루list���鿴��\n");
        return 1;
}

int do_list()
{
	    int i,gx;
		object ob;

        write("����Ŀǰ���Զһ���duihuan��������Ʒ��\n");
        write("==========================================\n");
        write("���  �Ź�    ��Ʒ\n");
        write("------------------------------------------\n");
        for(i = 1; i <= sizeof(convert_list); i++){
			    ob = new(convert_list[i][0]);
			    write(i + "  ");
				if(i < 1000) write(" ");
				if(i < 100) write(" ");
				if(i < 10) write(" ");
				gx = convert_list[i][1];
				write(gx + "  ");
				if(gx < 10000) write(" ");
				if(gx < 1000) write(" ");
				if(gx < 100) write(" ");
				write(" ");
			    write(ob->name());
				write("\n");
	    }
        write("==========================================\n");

        return 1;
}

int do_duihuan(string arg)
{
	    int n, count, i, gx;
		object ob, me;
		string  name;

		if (!arg || sscanf(arg, "%d %d", n, count) != 2)
                return notify_fail(CYN "����΢Ц������Ҫ�һ�ʲô������"
                                   "ָ�duihuan <���> <����>\n" NOR);

		if (n > sizeof(convert_list))
                return notify_fail(CYN "����΢Ц�������루list��"
		                           "�����������ɡ�\n" NOR);

		me = this_player();
		gx = convert_list[n][1] * count;

		if(me->query("gongxian") < gx)
			    return notify_fail(CYN "���ƶ�����Цһ����û���㡣\n" NOR);

		for(i=0; i<count; i++){
		        ob = new(convert_list[n][0]);
				name = ob->name();
		        ob->move(me, 1);
		}

		me->add("gongxian", -gx);

        write(CYN "�����ó�һЩ" + name + CYN "���㣬"
		                            "Ц���е�˵����ӭ�´ι��١�\n" NOR);
        return 1;
}

void unconcious()
{
        message_vision("\n$N�ߺ�������������ʲô���������\n",
                       this_object());
}

void die()
{
        message_vision("\n$N���һ����˵�����һ�������ġ�����\n",
                       this_object());
}
