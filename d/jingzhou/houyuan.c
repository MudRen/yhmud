
inherit ROOM;

void create()
{
	set("short", "���ź�Ժ");
	set("long", @LONG
���������ŵĺ�Ժ����ɨ�÷ǳ��ɾ��������ǹ��˵�Χǽ��Ժ������
�˲��ٵĸ����滨��ݣ����Ը�ɫ�ջ�Ϊ�ࡣԺ����Ѿ�ߵķ��䣬������
һ����(men)��
LONG );

        set("item_desc", ([
                "men" : "�����ź������С��Ĺ뷿��\n",
        ]));
        
	set("exits", ([ /* sizeof() == 2 */
                "west"  : __DIR__"xixiang",  
                "north" : __DIR__"ymzhengting",
                "east"  : __DIR__"dongxiang",
        ]));
	
        set("objects", ([
		__DIR__"npc/guanjia" : 1,
	]));
	
	set("no_clean_up", 0);
	setup();
	// replace_program(ROOM);
}

void init()
{
	add_action("do_unlock", "unlock");
	if (present("guan jia", environment(this_player())))
		delete("exits/east");
}

int do_unlock(string arg)
{
	object ob;
	if (query("exits/east"))
		return notify_fail("�������Ѿ��Ǵ򿪵ġ�\n");
	if (!arg || (arg != "men" && arg != "east"))
		return notify_fail("��Ҫ��ʲô��\n");
	if (!(ob = present("guifang key", this_player())))
		return notify_fail("�㲻��������\n");
	set("exits/east", __DIR__"dongxiang");
	message_vision("$N��һ��Կ�״򿪷��ţ�����Կ��ȴ���ˡ�\n", this_player());
	destruct(ob);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (!wizardp(me) && objectp(present("guan jia", environment(me))) && 
		(dir == "west" || dir =="east"))
		return notify_fail("�ܼҵ�ס���㣺��������լ��\n");
	return ::valid_leave(me, dir);
}
