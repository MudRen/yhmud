#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������һ�����ѵ�С·�ϣ�������������ˡ�
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/road3",
                "west" : "/d/tulong/yitian/road1",
        ]));

        set("outdoors", "beijing");
        setup();
}
