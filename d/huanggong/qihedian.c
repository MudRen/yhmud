inherit ROOM;

void create()
{
	set("short", "��͵�");
	set("long", @LONG
��������͵������һ�����������ȣ�ͨ����Ժ���������м����Է���
�����ǹ���̫���ס����
LONG );
        set("outdoors", "huanggong");
	set("exits", ([
		"south" : __DIR__"tinglang3",
		"west" : __DIR__"zoulang1",
		"north" : __DIR__"houhuayuan",
	]));
	set("objects", ([
		__DIR__"npc/shiwei" :1,
		__DIR__"npc/taijian" :1,
	]));
//	set("no_clean_up", 0);
	setup();
}

int valid_leave(object me, string dir)
{
me->delete("huanggong/canenter");
return ::valid_leave(me, dir);
}
