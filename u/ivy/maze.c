#include <ansi.h>

inherit ROOM;

varargs void create(int x, int y, int z)
{
    set("short", "心魔幻境");
    set("long", "这里是你的心魔幻境，无边无际，四周灰蒙蒙的，你根本不知道该向哪儿走。\n");
    set("exits", ([
        "north":__DIR__ "maze/" + x + "," + (y + 1) + "," + z,
        "south":__DIR__ "maze/" + x + "," + (y - 1) + "," + z,
        "west":__DIR__ "maze/" + (x - 1) + "," + y + "," + z,
        "east":__DIR__ "maze/" + (x + 1) + "," + y + "," + z,
    ]));
    set("maze", "maze");
    setArea(x, y, z, "maze");

    if (!random(100))
    {
        set("long", "也不知道在幻境中走了多远，你已经快要迷失了方向，这里有一个闪闪发光的传送门（door）。\n");
        set("item_desc", ([
            "door":"离开(out)心魔幻境的传送门，但不是斩杀心魔离开的话" HIY "起不到修心的作用" NOR "！\n",
        ]));
        set("exits/out", "/d/city/guangchang");
    }

    if (!random(10))
    {
        set("objects", ([
            "/clone/beast/qingshe" : 1,
        ]));
    }

    if (!random(20))
    {
        set("objects", ([
            "/clone/beast/wubushe" : 1,
        ]));
    }

    if (!random(30))
    {
        set("objects", ([
            "/clone/beast/yanjingshe" : 1,
        ]));
    }
    setup();
}

void setDemon(object me)
{
    int level = 1 + random(100);
    object ob;

    ob = new (CLASS_D("generate") + "/demon.c");
    NPC_D->set_from_me(ob, me, 100);
    ob->add_temp("apply/attack", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/dodge", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/parry", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/damage", 5 + level * 7);
    ob->add_temp("apply/unarmed_damage", 5 + level * 7);
    ob->add_temp("apply/armor", 10 + level * 15);
    ob->move(environment(me));
}

void init()
{
    object me = this_player();
    object ob = next_inventory(me);
    if (interactive(me) && (!objectp(ob) || !living(ob)) && !random(5))
    {
        setDemon(me);
    }
}
