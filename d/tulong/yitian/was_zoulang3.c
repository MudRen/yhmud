inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ��ͨ�����º���ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶�����
�������µĴ���ˡ�
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_houdian",
                "south" : "/d/tulong/yitian/was_dadian",
        ]));

        setup();
}

