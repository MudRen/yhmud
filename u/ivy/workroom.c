#include <ansi.h>
inherit ROOM;

varargs void create(int x, int y, int z)
{
    set("short", "�ƶ�");
    set("long", HIW"
    �����Ǿ������⣬������ĵط�����ֻ��������Ʈ����
���Ŀ�������\n");
    setArea(x, y, z, "�ƶ�");
    set("exits", ([
        "north":__DIR__ "workroom/" + x + "," + (y + 1) + "," + z,
        "south":__DIR__ "workroom/" + x + "," + (y - 1) + "," + z,
        "west":__DIR__ "workroom/" + (x - 1) + "," + y + "," + z,
        "east":__DIR__ "workroom/" + (x + 1) + "," + y + "," + z,
    ]));

    if (x == 0 && y == 0)
    {
        addExit("down", __DIR__ "mogong");
        addExit("up", "/d/sky/tianmen");
    }

    /*
    set("objects",([
        __DIR__"clone/beast/qilin" : 1,
    ]));
    */

    //MOYE->come_here();

    set("valid_startroom", 1);
    set("sleep_room", 1);
    setup();
}
