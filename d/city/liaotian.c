#include <ansi.h>
inherit ROOM;

int is_chat_room()
{
	return 1;
}

void create()
{
        set("short", "�͵�跿");
        set("long", @LONG
���������ݿ�ջ�Ĳ�԰��������������µ��˶���������
���С�������ڿ����м䣬æ����ͣ���������С��Ҳϲ��
���������Ҷ��ۻ��
LONG);
        set("no_fight", 1);
        set("can_trade", 1);
        set("no_sleep_room", 1);
        set("objects",([ 
                "/clone/food/peanut":5, 
                "/clone/game/fruit":1, 
                "/clone/game/mint":1,
                	"/adm/npc/horseboss":1,
                //__DIR__"npc/yanruyu":1,
               //"/adm/npc/beastseller":1,
        ])); 
        set("exits", ([
                "north" : __DIR__"kedian",
                "east" : __DIR__"qiyuan/qiyuan1",
        ]));

        setup();
        replace_program(ROOM);
}


