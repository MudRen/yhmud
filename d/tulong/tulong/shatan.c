inherit ROOM;

void create()
{
        set("short", "ɳ̲");
        set("long", @LONG
һƬ���ɫ��ɳ̲���ޱ��޼ʵĴ󺣾�����ǰ�ˡ������ĵĺ�ˮ����ӿ����
��׵��˻�������Ʈ������ı���ãã�Ĵ���û��һ�㷫Ӱ����ĿԶ������
�콻�紦����һƬ���ֲ��������Ǻ����������졣�������������е���ζ������
΢΢���Ų��ˡ�
LONG );

        set("exits", ([
                "west" : "/d/tulong/tulong/haian",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/liuyun" : 1,
        ]));

        set("outdoors", "tulong");
        setup();
}

