inherit ROOM;
void create()
{
        object item, con;

        set("short", "������¥����");
        set("long", @LONG
������������¥�Ĵ������൱�Ŀ���һ��������Ů�������ã���Ůǰ��
��һ��޴�ĺ�ľ�������ܣ�����վ�����ױ����ų��������ɡ�
LONG );
        set("exits", ([ 
                "down" : "/d/tulong/yitian/was_lou3",
        ]));
        set("objects", ([
                "/d/tulong/yitian/npc/ada" : 1,
                "/d/tulong/yitian/npc/aer" : 1,
                "/d/tulong/yitian/npc/asan" : 1,
                "/d/tulong/yitian/npc/he" : 1,
                "/d/tulong/yitian/npc/zhao" : 1,
                "/d/tulong/yitian/obj/shelf" : 1,
                "/clone/npc/walker" : 1,
        ]) );

        setup();

	con = present( "shelf", this_object());
	item = new("/d/tulong/obj/yitianjian");

	item->move(con);
}

