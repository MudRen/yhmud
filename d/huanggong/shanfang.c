//shanfang.c ���ŷ�

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "���ŷ�");
        set("long", @LONG
�ʹ������ʳ��ƽ��������Ȼ��ͬ,������Ǹ���������ŵ���
�ŷ�.�㲻������������ζ����һ��,�ɱ���������ǻʹ���.
LONG
        );
        set("exits", ([
			"north" : __DIR__"tinglang2",
        ]));
        set("objects", ([
			__DIR__"obj/yuchi" : 2,
			__DIR__"obj/nverhong" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
