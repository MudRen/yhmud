// Room: /d/huanggon/tinglang3.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ܵ���������.������ϲ�˵Ļ���,վ�����,��Լ���õ�����
������Ů����Ц������,�����������������,�Եþ�������,��������
�Ĺ��ͦ�ϵ�.
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
			  "north" : __DIR__"qihedian",
			  "east" : __DIR__"tinglang2",
		]));
        set("no_clean_up", 0);
        set("outdoors", "huangong");

        setup();
        replace_program(ROOM);
}
