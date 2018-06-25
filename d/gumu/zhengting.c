
#include <ansi.h>
inherit ROOM;

int do_sleep(string arg);

void create()
{
        set("short", "����");
        set("long", @LONG
�����ǹ�Ĺ������������Ӧͣ�����ѹ�ľ֮��Ķ�����ȴ
��֪�����˰ᵽ����ȥ�ˡ������ж�����һλ������Ů������
�ϰڷ���һ��ʯͷ���ɵĴ�(chuang)�����к�ϵ��һ�����ӣ�
��֪����ʲô�õģ�����֮�⣬���ް��衣
LONG
        );

        set("exits", ([
                "west" : __DIR__"liangong",
                "north" : __DIR__"xiaoting",
                "south" : __DIR__"houting",
        ]));
/*
        set("objects", ([
                CLASS_D("gumu") + "/longnv" : 1,             	
        ]));
*/
        set("valid_startroom",1);

        set("item_desc", ([
        	"chuang": HIC "����һ����" HIW "ǧ�꺮��" HIC "��ɵĺ��񴲡�\n" NOR,
        ]) );
        setup();
        "/clone/board/gumu_b"->foo();
}

void init()
{
        add_action("do_sleep", "sleep");
}

int do_sleep(string arg)
{
        object me=this_player();
        int lvl_force;

        lvl_force = (int)me->query_skill("force", 1);
        if (me->is_busy())
        {
                tell_object(me, RED "�����������Ϣδ���������������ܸе������嵴�����Ҽ�����Ϣ��\n" NOR);
                return 1;
        }
        if (lvl_force > 100)
        {
        	if ( me->query("max_neili") < 200 ) //������������
        		{
                write(HIR"�����ڵ�������Ϊ̫���޷��������񴲵ĺ�����ȥ���������ɡ�\n"NOR);
                return 1;
             }
             /*
        	if ( me->query("max_neili") > 2000 ) //������������
                {
                write(HIR"�������ڵ�������Ϊ���ɺ����Ѿ�ûʲô���ˡ�\n"NOR);
                return 1;
                }
                */
                
                if ( me->query("max_neili") > 2000 && me->query("family/family_name") != "��Ĺ��" ) //������������
                {
                write(HIR"�������ڵ�������Ϊ���ɺ����Ѿ�ûʲô���ˡ�\n"NOR);
                return 1;
                } else
                	
                if ( me->query("max_neili") > 3000) //��Ĺ���Ӹ��� 2017-02-20
                {
                write(HIR"�������ڵ�������Ϊ���ɺ����Ѿ�ûʲô���ˡ�\n"NOR);
                return 1;
                }
                
                message_vision(HIC "\n$N" HIC "�����˺��񴲣���ʼǱ���ڹ���ʹ��"
                               "Ϣ���д�С���졣\n", this_player());
                if (random(20) > 10 && (int)me->query("max_neili") < (int)me->query_neili_limit())
                {
                        message_vision(HIM "\n$N" HIM" ��Ϣ��ϣ�ֻ���þ�����"
                                       "����Ϣ���������ڶ�����\n" NOR, this_player());
                        me->add("max_neili", 1);
                        //me->start_busy(3 + random(5));
                        me->start_busy(2 + random(2));//����busy
                        me->receive_damage("qi", lvl_force / 3 + random(lvl_force / 3));
                }
                else
                {
                        message_vision(HIY "\n$N" HIY "��Ϣ��ϣ�վ������������������"
                                       "������ûʲô������\n" NOR, this_player());
                        //me->start_busy(1 + random(2));
                        me->start_busy(1); //����busy
                        me->receive_damage("qi", 10 + random(10));
                }
        } else
        {
                message_vision(HIW "\n$N" HIW "���Ϻ��񴲣�ֻ���ñ���̹ǣ�������"
                               "��һ���Ǳ�����������������\n", this_player());
        }
        return 1;
}

