#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
���������µĺ��ǳ��Ŀ�����������ǰ����һ�����������ϵ���¯
�в��ż����㣬���ϰ���һЩ���š����״�һ��ľ�ƽ��ݣ�����ͨ�����µ���
¥��
LONG );
        set("exits", ([
            "south"  : "/d/tulong/yitian/was_zoulang3",
            "up"    : "/d/tulong/yitian/was_lou2",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-5dao" :5,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("dao seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������\n" NOR);

        if (dir == "south" && objectp(present("dao seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������\n" NOR);

        return ::valid_leave(me, dir);
}

