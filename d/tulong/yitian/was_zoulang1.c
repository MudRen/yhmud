inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ��ͨ�����º�����ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶�����
������������������
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_zoulang2",
                "south" : "/d/tulong/yitian/was_dayuan",
                "east" : "/d/tulong/yitian/was_tinge",
                "west" : "/d/tulong/yitian/was_tingw",
        ]));

        setup();
}

