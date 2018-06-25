#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "�߲����");
        set("long",
"������Ǵ�˵��������������ظ߲��Թ��Ĵ��ıڹ�
�Ķ�������ľ��ķ���(fo).���֮����һ���������Σ�����
֮��͸��һ�����ϣ���һ����ң����飺

        " WHT "��������������������������������������
        ��                                  ��
        ��     " NOR + HIR "��     ��      ��     ��" NOR + WHT "     ��
        ��                                  ��
        ��������������������������������������" NOR "

�������涼�ǵ��á�\n");
        set("maze", 1);
        set("exits", ([
                "west" : __DIR__"wroom1",
                "east" : __DIR__"eroom1", 
        ]));
        set("item_desc", ([ 
            "fo" : "��Щ���񶼰�����ֵ����ƣ���о����Բ���(think)����ȭ�ŵ����⡣\n",
        ]));
        setup();
}

void init()
{
    add_action( "do_think", "think" );
}

int do_think()
{
    object  ob;
    int c_skill, add;

    ob = this_player();

    c_skill = (int) ob->query_skill( "unarmed", 1 );
    if ( ob->query_skill( "unarmed", 1 ) < 50 )
    {
        write( "��Ի���ȭ�ŵ��˽���Ȼ̫�ͣ��޷��ӷ�����������Ҫ�塣\n", ob );
        return(1);
    }

    if ( !ob->can_improve_skill( "unarmed" ) )
    {
        write( "���ʵս���鲻�㣬�޷��ӷ���������ߵ���ѧ��\n" );
        return(1);
    }

    if ( ob->query( "jing" ) < 100 )
    {
        write( "�㾫�����ܼ��У������޷�����������⡣\n" );
        return(1);
    }

    if ( c_skill > 180 )
    {
        write( "��о��Լ��ӷ����������ѧ����ʲô�����ˡ�\n" );
        return(1);
    }

    message_vision( "$Nģ���ŷ�������ƣ����ã��ԡ�����ȭ�š�"
            "��������\n", ob );
    if ( ob->query( "special_skill/clever" ) )
        add = ob->query("int") * 5 / 2;
    else
        add = ob->query("int") * 3 / 2;
    ob->improve_skill( "unarmed", add );
    ob->receive_damage( "jing", 50 + random( 40 ) );
    ob->start_busy( 2 );
    return(1);
}
