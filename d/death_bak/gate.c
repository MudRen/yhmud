#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "���Ź�" NOR);
        set("long", HIR @LONG

                    ��         ��         ��

    �������������������ڡ����Źء���������ǰ������һ���ߴ��
��ɫ��¥������������޿�������ж�ǰ������Ϊһ�����Źؾ��޷���
�������ˡ�


LONG NOR );
        set("exits", ([
                "north" : __DIR__"gateway",
        ]) );
        set("objects", ([
                __DIR__"npc/bai":1,
                __DIR__"npc/ghost":1,
        ]) );

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
        replace_program(ROOM);
}
