// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�뷿");
	set("long", @LONG
������С��Ĺ뷿��һ���������������һ����齷���ǽ�ǣ�����ϸ
ɴ����С��������һ��ջ��ڳ�˼������������԰��
LONG );

	set("exits", ([
		"west" : __DIR__"houyuan",
		"north" : __DIR__"huayuan",
	]));

	set("objects", ([
		__DIR__"npc/shuanghua" : 1,
	]));
	
	setup();
	replace_program(ROOM);
}

