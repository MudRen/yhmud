#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_wash(string arg);
int do_born(string arg);

mapping born = ([
        "��������" : "/d/city/kedian",
        "ŷ������" : ([ "born"      : "��������",
                        "surname"   : "ŷ��",
                        "startroom" : "/d/baituo/dating",
                     ]),
        "�������" : ([ "born"      : "��������",
                        "surname"   : "��",
                        "startroom" : "/d/guanwai/xiaowu",
                     ]),
        "��ԭ���" : ([ "born"      : "��ԭ����",
                        "surname"   : "��",
                        "startroom" : "/d/zhongzhou/miaojia_houting",
                     ]),
        "���ϻ���" : ([ "born"      : "��������",
                        "surname"   : "��",
                        "startroom" : "/d/dali/wangfugate",
                     ]),
        "Ľ������" : ([ "born"      : "��������",
                        "surname"   : "Ľ��",
                        "startroom" : "/d/yanziwu/cuixia",
                     ]),
       
]);

void create()
{
        int i, k;
        string desc;
        string *position;

        set("short", HIR "���޵�" NOR);
        set("long", HIR @LONG

                    ��         ��         ��

    ���޵�����ɭ�ֲ������˸о���һ����̹ǵĺ��⣬��������ţͷ
���棬ڤ�����䣬�����������¡�ʮ�����ޣ������ڴˣ��ز������ڴ�
��֮�ϣ���ŭ����������ȽŲ�������Щ���ˡ���������һ��ʯͷ��
�ɵĳ��ӣ�����̶ˮ�峺ȴ�����ף���֪���������ж��ˮ�ص��Ա�
��һ������(paizi)����Ҳ��Ӧ����ϸ������


LONG NOR );
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : "Ͷ̥���������£��мǲ��ɲ��ʣ�washtoѡ���츳֮�󣬾�����born <���ĵ���>��\n"
        ]));

        set("objects", ([
                __DIR__"npc/dizangwang" : 1,
                "/d/death/npc/niutou" : 1,
        ]));

        set("no_say", "���޵�����ɭ�ֲ������������˵����\n");

        desc = query("item_desc/paizi");
        position = keys(born);

        for (i = 0, k = 1; i < sizeof(position); i++)
        {
                if (! stringp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIG "%s" NOR "\n", k++, position[i]);
        }

        for (i = 0; i < sizeof(position); i++)
        {
                if (! mapp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIC "%s" NOR "\n", k++, position[i]);
        }
        set("item_desc/paizi", desc);

        setup();
}

void init()
{
        add_action("do_wash", "washto");
        //add_action("do_wash2", "washto");
        add_action("do_born", "born");
}



int do_wash(string arg)
{
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail("ָ���ʽ��washto <����> <����> <����> <��>\n");
        if( tmpstr>30) return notify_fail("����ѡ��������������ܴ���30��\n");
        if( tmpstr<10) return notify_fail("����ѡ���������������С��13��\n");
        if( tmpint>30) return notify_fail("����ѡ������Բ������ܴ���30��\n");
        if( tmpint<10) return notify_fail("����ѡ������Բ�������С��13��\n");
        if( tmpcon>30) return notify_fail("����ѡ��ĸ��ǲ������ܴ���30��\n");
        if( tmpcon<10) return notify_fail("����ѡ��ĸ��ǲ�������С��13��\n");
        if( tmpdex>30) return notify_fail("����ѡ������������ܴ���30��\n");
        if( tmpdex<10) return notify_fail("����ѡ�������������С��13��\n");
        if((tmpstr+tmpint+tmpcon+tmpdex)!=80) return notify_fail("����ѡ��������ܺͱ���Ϊ80��\n");

        write(HIC "���������ǳأ���ʱ��һ�ɼ������˽�ȥ��\n" NOR, me);

        my = me->query_entire_dbase();

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 5 + random(26);
        my["per"] = 5 + random(26);

        write(HIC "ֻ����ž����һ�����㱻ʪ���������˳�����\n" NOR, me);
        write(sprintf(HIY "\n����λ�õ����������츳�ֱ��ǣ�\n"
                          "�������� " HIG "%d" HIY " �� "
                          "���ԣ��� " HIG "%d" HIY " �� "
                          "���ǣ��� " HIG "%d" HIY " �� "
                          "������ " HIG "%d" HIY " ��\n"
			  "��������⣬��ȥͶ̥(born)�ɣ�������"HIR"<born ��������>\n\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        me->set_temp("washed", 1);

        return 1;
}

int do_born(string arg)
{
        object me;
        object obj;
        object item;
        mixed dest;
        string new_name;
        string msg;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if (! me->query_temp("washed"))
                return notify_fail("���������ǳ���ϴһ��(washto)��ѡ����츳����Ͷ̥Ҳ���ٰ���\n");

        if (arg && arg[0] < 160)
                return notify_fail("������������ĵ���������born �������ϣ�������born ŷ�������Ա���Ͷ��̥��\n");

        new_name = 0;
        if (arg) sscanf(arg, "%s %s", arg, new_name);

        if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
        {
                message_vision(CYN "ţͷ��ݺݵĶ�$N" CYN
                               "˵����Ҫ��ʲô��Ͷ̥ȥ���\n" NOR, me);
                return 1;
        }

        if (mapp(dest) && stringp(dest["notice"]))
                return notify_fail(dest["notice"]);

        if (stringp(dest))
        {
                if (! objectp(obj = find_object(dest)))
                        obj = load_object(dest);
                me->set("startroom", dest);
                me->set("born", arg);
                me->set("born_family", "û��");
        } else
        {
                if (! objectp(obj = find_object(dest["startroom"])))
                        obj = load_object(dest["startroom"]);
                me->set("startroom", dest["startroom"]);
                me->set("born", dest["born"]);
                me->set("born_family", arg);

                if (new_name)
                {
                        if (! sscanf(new_name, dest["surname"] + "%*s"))
                                new_name = dest["surname"] + new_name;

                        if (strlen(new_name) > 8)
                                return notify_fail("�������̫���ˡ�\n");

                        if (strlen(new_name) < 4)
                                return notify_fail("�������̫���ˡ�\n");

                        if (! is_chinese(new_name))
                                return notify_fail("���������������֡�\n");
                }

                if (me->query("surname") != dest["surname"])
                {
                        // ������Ҫ�仯
                        if (! new_name) new_name = dest["surname"] + me->query("purename");
                        if (stringp(msg = NAME_D->invalid_new_name(new_name)))
                        {
                                write(msg);
                                write("����Կ�����Ͷ�����ҵ�ʱ������ѡ�����֣�born <����> <����>\n");
                                return 1;
                        }
                        me->set("surname", dest["surname"]);
                        me->set("purename", new_name[strlen(dest["surname"])..<1]);
                }

                if (mapp(dest["family"]))
                {
                        me->set("family", dest["family"]);
                        me->assign_apprentice(dest["family"]["title"], 0);
                }
                me->set_name();
        }
        if (! objectp(obj))
        {
                message_vision(CYN "ţͷһ����ɦɦͷ˵������ô��������"
                               "�⡭��\n" NOR, me);
                return 1;
        }

        message_vision(HIC "ţͷ����һ�ţ���$N" HIC "���˳�ȥ��\n" NOR, me);
	
		foreach (item in all_inventory(me))
			if (! item->query("armor_type") && ! (item->query("id")=="heros book"))
			{
				if (item->is_character() || item->query("value"))
					item->move(environment(me));
				else
					destruct(item);
			}

        // ѡ�����⼼��
        UPDATE_D->born_player(me);

        me->move(obj);
        me->set("mud_age", 0);
        me->set("age", 14);
        me->save();
        HELP_CMD->main(me, "rules");
        message_vision("$N�����۾�����㯵��������İ�������硣\n", me);

        return 1;
}
