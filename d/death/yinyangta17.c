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
                "up"   : __DIR__"yinyangta18",
                "down" : __DIR__"yinyangta16",
        ]));
        
        set("objects",([
                __DIR__"npc/mamian" : 1,
        ]));
        
        setup();
}

int valid_leave(object me, string dir)
{
//      int i;
//      object ob;
        me = this_player();
        if (dir == "up")
        {
                if (objectp(present("ma mian", environment(me))))
                        return notify_fail(CYN "���濴����һ�ۣ��ȵ����㻹����"
                                           "��ȥ�������������ʲô���֣�\n" NOR);
        }
        return ::valid_leave(me, dir);
}