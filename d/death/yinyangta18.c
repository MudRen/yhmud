#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "������" NOR);
        set("long", HIB @LONG
���ǵ�������ߵ�һ��������Լ������ߣ�����ʮ�˼����������
�����������и�����̨(stone)����˵��������ȸ·����
LONG NOR
        );

        set("exits", ([
                "down" : __DIR__"yinyangta17",
        ]));

        set("item_desc", ([
                "stone" : HIW "\n���������Է�(put)��Ʒ��\n" NOR,
        ]));
                
        set("objects",([
                // __DIR__"npc/zhuque" : 1,
        ]));
        set("zhuque", 1);
        
        setup();
}

void init()
{
        object me;
        me = this_player();

        add_action("do_fang", "put");
        add_action("do_fang", "fang");
}

int do_fang(string arg)
{
        object me = this_player();
        object ob;
        object ob1;


        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");
                
        if (objectp(present("zhu que", environment(me))))
                return notify_fail("��ȸ�Ѿ������ˣ���Ѱʲôѽ���Ͽ�ս���ɣ�\n");

        if (query("zhuque") < 1)
                return notify_fail("��ȸ�Ѿ������ˣ�������ôѰҲ��Ѱ�����ģ�\n");

        if (arg != "qise yingluo")
                return notify_fail("��������������ɫ��󣬲�������������ȸ��\n");
                                
        if (! objectp(ob = present("qise yingluo", me)))
                return notify_fail("������û��������ɫ���\n");               
        
        destruct(ob);
        message_vision(HIC "\n$N" HIC "��С������Ľ�������ɫ���ŵ�����̨����ʼĿ��ת����Ѱ����ȸ��\n" NOR, me); 
        
        ob1 = new("/d/death/npc/zhuque");
        ob1->move(environment(me));
        message_vision(HIC "\n������ȸ�ܵ�������ɫ����������ͻȻ�����ڹ���̨�����ʱ��ϲ��\n" NOR, me);         
        
        return 1;
}
 
