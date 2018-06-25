#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "���µڶ���");
        set("long", @LONG
���������µĵڶ��㣬��¥��վ�ż������Ż�����ĵĺ��С�һ������¥��
��������������
LONG );
        set("exits", ([
            "down"  : "/d/tulong/yitian/was_houdian",
            "up"    : "/d/tulong/yitian/was_lou3",
        ]));

        set("objects", ([
            "/d/tulong/yitian/npc/18jingang-4zhang" :4,
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" && objectp(present("zhang seng", environment(me))))
           return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������\n" NOR);

        if (dir == "down" && objectp(present("zhang seng", environment(me))))
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

