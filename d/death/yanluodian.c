// regiser: yanluodian.c
// by Doing

#include <ansi.h>

inherit ROOM;


void create()
{
        set("short", HIR "���޵�" NOR);
        set("long", HIB @LONG
��������ֲ������˸о���һ����ĺ��⣬��������ţͷ���棬ڤ
�����䣬�����������¡�ʮ�����ޣ������ڴˣ��ز��������ڴ���֮�ϣ�
��ŭ����������ȽŲ�������Щ���ˡ�
    ��������һ��ʯͷ���ɵĳ��ӣ�����ˮ�峺ȴ�����ף���֪����
�����ж��
LONG NOR
);
        set("no_fight", 1);
        // set("no_magic", 1);
        
        set("exits", ([
                "east"  : __DIR__"jimiesi",        
                "south" : __DIR__"youmingdian",
                "west"  : __DIR__"yinyangta1",
                "north" : __DIR__"xuechi1",
        ]));
        
        set("objects", ([
                __DIR__"npc/dizangwang"    : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
       // int i;
      //  object ob;
        me = this_player();
        if (dir != "south")
        {
                if (objectp(present("dizang", environment(me))) 
                &&  ! me->query("hell_quest/������")
                &&  ! me->query("DiZangPass"))
                        return notify_fail(CYN "�ز���������һ�ۣ��ȵ����㻹����"
                                           "��ȥ�������������ʲô���֣�\n" NOR);
        }
        return ::valid_leave(me, dir);
}
       
