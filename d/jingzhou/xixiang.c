inherit ROOM;

void create()
{
        set("short", "Ѿ���Է�");
        set("long", @LONG
����Ѿ�ߵķ��䡣���г���򵥣�ûʲô������
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/juyou" : 1,
        ]));
	setup();
        replace_program(ROOM);
}

