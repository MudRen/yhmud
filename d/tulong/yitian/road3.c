#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������һ�����ѵ�С·�ϣ�������������ˣ��䱸�������ϡ�
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_damen",
                "south" : "/d/tulong/yitian/road2",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/bing1" : 10,
        ]));

        set("outdoors", "beijing");
        setup();
}
