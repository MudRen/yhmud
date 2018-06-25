// yongdao2.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
����Ȼת�䣬����������Զ��ǰ���Ȼ����������һ����Ѩ��
��������ʯ�ҡ���ϧ���ڱ���ʯͷ(stone)��ס��ǰ����
LONG );
        set("exits", ([ /* sizeof() == 2 */
            //"north" : __DIR__"shandong",
            "west"  : __DIR__"yongdao1",
        ]));
        set("item_desc", ([
            "stone" : "һ���ʯ��Ҫ��ǰ��ֻ����취�����ƿ���move����\n"
        ]) );
        set("no_clean_up", 0);
        setup();
		//replace_program(ROOM);
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me=this_player();

        if( !arg || arg != "stone" ) {
                return notify_fail("��Ҫ�ƶ�ʲô��\n");
        }
        if (me->query("neili") < 1500 ||
            me->query_str() < 35)
        {
                message_vision("$Nʹ�����̵ľ�Ҳû���ƶ���ʯ��\n", me);
                me->set("neili", 0);
                return 1;
        }
        message_vision(HIC "$N" HIC "վ��ʯǰ��˫�Ʒ����ƶ���ʯ��ֻ���þ�ʯ"
                       "֨֨����������\n�����ȥ���ֳ�һ��ɽ������\n" NOR, 
                       this_player());
        set("exits/north", __DIR__"shandong");
        remove_call_out("close");
        call_out("close", 5, this_object());
        me->add("neili",-1000);
        return 1;
}

void close(object room)
{
        message("vision", HIW "\nֻ����ʯ��֨֨�ػص�ԭ�ء�\n" NOR, room);
        room->delete("exits/north");
}