#include <ansi.h>
inherit BUILD_ROOM;

void create()
{
        set("short", NOR MAG "����̨" NOR);
        set("long", @LONG
����̨�����������ڣ����ɲ������գ������±��ϳ���һ������
������(teng)�����ǹ��졣��Ϊ������ǣ�ÿ�������죬ɽ��֮�о�
�������������֡���Ŀ�������羰�续��������������طǳ���⡣
LONG);
        set("outdoors", "huashan");
        set("exits",([ /* sizeof() == 1 */
            "eastdown": __DIR__"chaopath2",
        ]));
        set("max_room", 3);
        set("item_desc", ([
              "teng"  : MAG "һ�����٣��������ܽ�ʵ�����ӣ����������������climb�������¡�\n" NOR,
        ]));   
        setup();
        //replace_program(ROOM);
}
void init()
{
        add_action("do_climb", "climb");
}
int do_climb(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg == "")
        	return 0;

        if (arg == "teng")
        {
                if (me->is_busy())
                {
                        return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
                        return 1; 
                }

                message_vision(MAG "$N�������٣�������������ȥ��\n"
                               NOR, me);

                me->move("/d/jinshe/shanbi");
                message("vision", HIC + me->name() + HIC "˳�����ٴ����������̨����������\n"
                                  NOR, environment(me), ({me}));
                me->start_busy(2);
                return 1;
        }
}
