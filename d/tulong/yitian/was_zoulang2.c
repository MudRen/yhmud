inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����һ��ͨ�����´���ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶���ǰ
��������µĴ���ˡ������ϵƻ�ͨ�����ǳ��Ŀ�������
LONG );
        set("exits", ([
                "north" : "/d/tulong/yitian/was_dadian",
                "south" : "/d/tulong/yitian/was_zoulang1",
        ]));

        setup();
}

