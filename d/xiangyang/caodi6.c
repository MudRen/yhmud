inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "�ݵ�");
        set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ��
���ˣ���Ȼ�ɹű�û�������ţ�����ɱ��Χ˿��������
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"southgate2",
                "south"  : "/d/wudang/wdroad5",
                "west"  : "/d/tiezhang/hunanroad1",
        ]));
        setup();
        replace_program(ROOM);
}
