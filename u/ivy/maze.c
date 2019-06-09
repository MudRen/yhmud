#include <ansi.h>

inherit ROOM;

varargs void create(int x, int y, int z)
{
    set("short", "��ħ�þ�");
    set("long", "�����������ħ�þ����ޱ��޼ʣ����ܻ����ɵģ��������֪�������Ķ��ߡ�\n");
    set("exits", ([
        "north":__DIR__ "maze/" + x + "," + (y + 1) + "," + z,
        "south":__DIR__ "maze/" + x + "," + (y - 1) + "," + z,
        "west":__DIR__ "maze/" + (x - 1) + "," + y + "," + z,
        "east":__DIR__ "maze/" + (x + 1) + "," + y + "," + z,
    ]));
    set("maze", "maze");
    setArea(x, y, z, "maze");

    if (random(3))
    {
        removeRandomExit();
        // ����رյڶ�������
        if (random(2))
        {
            removeRandomExit();
        }
    }

    if (!random(100))
    {
        set("long", "Ҳ��֪���ڻþ������˶�Զ�����Ѿ���Ҫ��ʧ�˷���������һ����������Ĵ����ţ�door����\n");
        set("item_desc", ([
            "door":"�뿪(out)��ħ�þ��Ĵ����ţ�\n",
        ]));
        set("exits/out", "/d/city/wumiao2");
    }

    if (!random(15))
    {
        set("objects", ([
            "/clone/beast/qingshe" : 1,
        ]));
    }

    if (!random(20))
    {
        set("objects", ([
            "/clone/beast/dushe" : 1,
        ]));
    }

    if (!random(30))
    {
        set("objects", ([
            "/clone/beast/jinshe" : 1,
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
    if (interactive(me) && (!objectp(ob) || !living(ob)) && !random(10))
    {
        setDemon(me);
    }
}
