#include <ansi.h>

inherit ROOM;


void create()
{
        set("short", "���");
        set("long", @LONG
���������µĴ��ǳ��Ŀ����������ﱾ��������ɮ�����֮����
����ǰ����һ�����������ϵ���¯�в��ż����㡣���ϰ���һЩ���š���������
��ϥ�������档��������������ƫ�
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_zoulang3",
                "south" : "/d/tulong/yitian/was_zoulang2",
                "east" : "/d/tulong/yitian/was_piandiane",
                "west" : "/d/tulong/yitian/was_piandianw",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-4bo" :4,
        ]));

        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "north" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������\n" NOR);

        if (dir == "south" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������\n" NOR);

        if (dir == "west" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������\n" NOR);

        if (dir == "east" && objectp(present("bo seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������\n" NOR);

        return ::valid_leave(me, dir);
}

void reset()
{
        object ob;

        ::reset();

        foreach (ob in all_inventory(this_object()))
        {
                if (ob->is_character() ||
                    ob->is_head() ||
                    ob->is_corpse() ||
                    ob->query("no_get"))
                        continue;
                destruct(ob);
        }
        
        return;
}

