#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY "����ͥ��" NOR);
        set("long", HIY @LONG
                    ��           ͥ

    ����һ��ͥ���ڣ���ͥ��������������۸ߴ���ʤ������ŭ������
����ȽŲ�������Щ���ˡ�

LONG NOR );

        set("no_sleep_room", 1);
        set("objects", ([
                __DIR__"npc/lonely": 1,
        ]));

        setup();
}


