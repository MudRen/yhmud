// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǽ�����ԼĪ���ɼ�����һ���ʯ�ң�ǽ�ںͶ��嶼�Ǵ�ʯ������
ǽ�������һֻ��Ͱ�������ŵ��ľ��ǳ�����ù����������ǽ�ϵ�С����
ȥ�����Լ������ָ���һ�ǡ�
LONG );

        set("exits", ([
                "west" : __DIR__"ymzhengting",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        create_door("west", "����", "east", DOOR_CLOSED);
	setup();
        replace_program(ROOM);
}


