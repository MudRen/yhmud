// Room: /d/fuzhou/wuyishan5.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "����Ϫ");
	set("long", @LONG
ӯӯһˮ����Ϊ����������������䣬���ͻأ�����ǡ�Ϫ
������к��Һ��ɽ�⵹������������
LONG );
	set("exits", ([
		"east"      : __DIR__"wuyishan2",
		"northup"   : __DIR__"wuyishan3",
		"northwest" : __DIR__"wuyishan4",
	]));
	set("resource/water", 1);
	set("outdoors", "fuzhou");
	setup();
	replace_program(ROOM);
}

