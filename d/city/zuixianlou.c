#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "����¥");
	set("long", @LONG
��Բ���������������ݳ�����¥����˵�����˲�֪������
������������ѧʿ���ε��ˣ�������¥�Ļ�����޲����ڣ���
ȻΪ�����ң�����һ�δ��麣�ڵļѻ����Ӵ�����¥��������
¥�²��ü��ף��˿Ͷ��ǴҴҵ����ˣ������ӡ����ȡ��׾�
�͸�·ȥ�ˡ�¥����������
LONG );
	set("exits", ([
		"east" : __DIR__"majiu",
		"west" : __DIR__"beidajie2",
		"up" : __DIR__"zuixianlou2",
		"north" : __DIR__"wfoxd",
	]));
	set("objects", ([
		__DIR__"npc/xiaoer2" : 1,
	]));
 
    set("no_fight", 1);
	setup();
	//replace_program(ROOM);
}

int valid_leave(object me, string dir) 
{
        object ob = this_player();

        if (dir == "north" && ob->query("id") != "ivy") 
                return notify_fail(HIW "��о�ǰ����һ�������������ס�����ȥ·��\n" NOR);

        return ::valid_leave(me, dir);
}