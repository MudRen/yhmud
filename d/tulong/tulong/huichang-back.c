inherit ROOM;
void create()
{
        set("short", "�ﵶ�����᳡");
        set("long", @LONG
�������ﵶ�����᳡��һƬ��ݵ��ϰ����߰��ŷ��������˶��׵�һϯ�⣬
ÿ�����Զ��������ˣ��к�ɳ�ɡ��޾����ȭ�ŵȵȸ��ɵ��ӡ�
LONG );

        set("exits", ([
                "west" : "/d/tulong/tulong/gukou",
                ]));

        set("objects", ([
                "/d/tulong/tulong/npc/mai" : 1,
                "/d/tulong/tulong/npc/guo" : 1,
                "/d/tulong/tulong/npc/yin" : 1,
                "/d/tulong/tulong/npc/yuan" : 1,
                "/d/tulong/tulong/obj/ding" : 1,
                "/d/tulong/tulong/npc/zhang" : 1,
                "/d/tulong/tulong/npc/chang" : 1,
                ]));
setup();
}

