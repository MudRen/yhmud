#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN "���׻�Ѩ��" NOR);
        set("long", GRN @LONG

                    ��         ��         Ѩ

    �����Ǽ���˾�����ɭ�������һ����Ѩ�������ϲ��տ�������
�����Ŀ����������ڿ��Ի����ˡ���˵������֮һ�İ׻�����Ϣ�ڴ˵ء�
�����İ��ޱȣ����������������Χ�����

LONG NOR );

        set("objects", ([
                __DIR__"npc/baihu" : 1,
        ]));
        
        set("exits", ([
                "south" : __DIR__"heisenlin/exit",
        ]));

        set("baihu", 1);
        setup();
}
