#include <ansi.h>

inherit ROOM;

void setDemon(object me);
void setInventory(int x, int y, int z);

varargs void create(int x, int y, int z)
{
    set("short", "��ħ�þ�");
    set("long", "�����������ħ�þ����ޱ��޼ʣ����ܻ����ɵģ�Ҳ��֪���������ʲôΣ�ա�\n");
    set("maze", "maze");
    setArea(x, y, z, "maze");
    set("exits", ([
        "north":__DIR__ "maze/" + x + "," + (y + 1) + "," + z,
        "south":__DIR__ "maze/" + x + "," + (y - 1) + "," + z,
        "west":__DIR__ "maze/" + (x - 1) + "," + y + "," + z,
        "east":__DIR__ "maze/" + (x + 1) + "," + y + "," + z,
    ]));
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
        set("long", "�������ޱ��޼ʵĻþ������ⵥ���Ļþ�����һ����������Ĵ����ţ�door�����Եø�����Ŀ��\n");
        set("item_desc", ([
            "door":"�뿪(out)��ħ�þ��Ĵ����ţ�\n",
        ]));
        set("exits/out", "/d/city/wumiao2");
    }

    setInventory(x, y, z);
}

void setInventory(int x, int y, int z)
{
    mapping inv = ([]);

    if (!random(15))
    {
        inv["/clone/beast/qingshe"] = 1;
    }

    if (!random(20))
    {
        inv["/clone/beast/dushe"] = 1;
    }

    if (!random(30))
    {
        inv["/clone/beast/jinshe"] = 1;
    }

    set("objects", inv);
    setup();
}

void setDemon(object me)
{
    int exp, level;
    object ob;
    string *ob_list = ({
        "/d/beijing/npc/dan/danA_5.c",
        "/d/beijing/npc/dan/danB_6.c",
        "/d/beijing/npc/dan/danC_5.c",
        "/d/beijing/npc/dan/danD_6.c",
        "/d/beijing/npc/dan/danM_9.c",
        "/d/beijing/npc/dan/danS_1.c",
        "/d/beijing/npc/dan/danS_2.c",
        "/d/beijing/npc/dan/danS_4.c",
        "/d/beijing/npc/dan/danS_4.c",
        "/d/beijing/npc/dan/danS_5.c",

        "/clone/fam/pill/full1",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
    });
    exp = me->query("combat_exp") * 10;
    level = to_int(pow(to_float(exp), 1.0 / 3)) / 10 + 1;

    ob = new (CLASS_D("generate") + "/demon.c");
    NPC_D->set_from_me(ob, me, 120);
    ob->set_temp("level", level);
    ob->add_temp("apply/attack", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/dodge", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/parry", ob->query_skill("force", 1) * (level - 1) / 15);
    ob->add_temp("apply/damage", 5 + level * 7);
    ob->add_temp("apply/unarmed_damage", 5 + level * 7);
    ob->add_temp("apply/armor", 10 + level * 15);

    if (!random(100))
    {
        ob->carry_object(element_of(ob_list));
    }
    if (!random(1000))
    {
        ob->carry_object("/clone/fam/item/lihuo");
    }

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
