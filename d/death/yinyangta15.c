#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "������" NOR);
        set("long", HIB @LONG
���ǵ�������ߵ�һ��������Լ������ߣ�����ʮ�˼����ഫ����
ס��������ȸ���������Ҳ��֪�����Ǽ١�
LONG NOR
        );

        set("exits", ([
              "up"   : __DIR__"yinyangta16",
              "down" : __DIR__"yinyangta14",
        ]));
        
        set("objects",([
        ]));
        
        setup();
        replace_program(ROOM);
}
