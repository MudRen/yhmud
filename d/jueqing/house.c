inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
���Ǿ���ȵ׵�һ��Сé�ݣ������ƺ��ܾ�û�������ˡ�
LONG);
        set("exits", ([
               "out"  :  __DIR__"underya2",
        ]));

        if (random(5) == 1)
               set("objects", ([
                      "/d/gumu/obj/fengmi" : 2,
                      	//���ת�Ƶ���Ĺ�����ǲ�Ҫ������С��Ů���޷�����:) by н������
                      //"/kungfu/class/gumu/yang" : 1,
               ]));

        else 
               set("objects", ([
                      "/d/gumu/obj/fengmi" : 2,                      
               ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}