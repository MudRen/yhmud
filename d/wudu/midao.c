inherit ROOM;

void create()
{
        set("short", "�ܵ�");
        set("long", @LONG
�������嶾�̻�԰�����һ����խ�İ�������ɭ���£���
�������˻ҳ���������������Ҳ��֪��ͨ���δ���
LONG);
        set("exits", ([
                "up"   : __DIR__"huating2",
                "west" : __DIR__"midao2",
        ]));
 //��������ǧ��������Ļ�� 2017-02-10       
         set("objects", ([
                  __DIR__"obj/huoba": 1,
        ]));
        setup();
        //replace_program(ROOM);
}
