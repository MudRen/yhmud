#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�ƶ�");
        set("long", HIW"
    �����Ǿ������⣬������ĵط�����ֻ��������Ʈ����
���Ŀ�������
\n");
        set("exits", ([
                "down"  : "/d/city/tree",
                "up"  : "/d/sky/tianmen",
        ]));
        //MOYE->come_here();
/*
        set("objects",([ 
                __DIR__"clone/beast/qilin" : 1,
        ]));
*/
        set("valid_startroom", 1);
        set("sleep_room", 1);
        setup();
        replace_program(ROOM);
}

