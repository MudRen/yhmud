#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", HIB "������˾��" NOR);
        set("long", HIB @LONG

                    ��         ��         ˾

    ����˾�ں���ɭɭ����ʯ����ĵ������ǻҳ��������಼Χᣣ�Χ�
���ý���˿������Щ��ֵ�ͼ����������һ����ʯ���� (table)��������
�����������������Ӻܾ�û��ɨ���ˡ�

LONG NOR );

        set("item_desc", ([
                "table" : WHT "һ����ʯ�Ƴɵ������������м���"
                          "�ѷ죬�������Ѹ�������ܾ��ˡ�\n" NOR,
        ]));

        set("exits", ([
                "east"  : __DIR__"lunhuisi_road1",
                "west"  : __DIR__"yanluodian",
                "north" : __DIR__"heisenlin/entry",
        ]));

        setup();
}

