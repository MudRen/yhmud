inherit ROOM;
#include <room.h>


void create()
{
	set("short", "��������");
	set("long", @LONG
ֻ�����϶����������ס������һ������������������ϸ
������ǽ������һ�����ң����顰�����������ĸ����������
���֡�֪���������İ����������飬ʦү�����ں�
LONG);
	set("exits", ([
		"north" : __DIR__"jzyamen",
		"south" : __DIR__"houyuan",
		"east"  : __DIR__"jail",		
	]));
	set("objects", ([
		__DIR__"npc/jing" : 1,
		
	]));

        create_door("east", "����", "west", DOOR_CLOSED);
	setup();
	// replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
	if (! wizardp(me) && objectp(present("ling tuisi", environment(me))) && 
		dir == "east")
		return notify_fail("�躲�ֵ�ס���㣺�������η���\n");
	return ::valid_leave(me, dir);
}