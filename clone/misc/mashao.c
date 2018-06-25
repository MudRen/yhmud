/* mashao.c ���� */

#include <ansi.h>

inherit ITEM;

void init()
{
    if ( interactive( this_player() ) &&
         environment() == this_player() )
    {
        add_action( "do_whistle", "whistle" );
    }
}

void create()
{
    set_name( HIG "����" NOR, ({ "ma shao", "shao" }) );
    if ( clonep() )
        set_default_object( __FILE__ );
    else {
        set( "unit", "��" );
        set( "long", "����һ�������Ƴɵ����ڣ���������Զ�ھֵı�־��\n" );
        set( "whistle", 3 );
    }

    setup();
}

int do_whistle()
{
    object  horse;
    string  err, file;
    object  me  = this_player();
    object  ob  = this_object();

    if ( me->is_busy() || me->query( "doing" ) )
        return(notify_fail( "��������æ�أ������п�����˵�ɡ�\n" ) );

    if ( me->is_in_prison() )
        return(notify_fail( "�����������أ����ʲô����\n" ) );

    if ( me->is_ghost() )
        return(notify_fail( "���㻹�������ٻ��ɡ�\n" ) );

    if ( me->query( "family/family_name" ) != "������" )
        return(notify_fail( "���ֲ�����Զ�ھֵ��ˣ�û����ƥ�ɺ�����\n" ) );

    if ( environment( me )->query( "no_ride" ) ||
         environment( me )->query( "maze" ) )
        return(notify_fail( "�㷢�������е�Ź֣����ڵ�����������ȥ��\n" ) );

    if ( !environment( me )->query( "outdoors" ) )
        return(notify_fail( "�㻹�ǵ������ٺ�����ƥ�ɣ�\n" ) );

    if ( environment( me )->query( "outdoors" ) == "wuguan" )
        return(notify_fail( "���������˹���������ô������Ҳû�ã�\n" ) );

    switch ( random( 3 ) )
    {
    case 0:
        file = "/clone/horse/huangbiaoma";
        break;
    case 1:
        file = "/clone/horse/zaohongma";
        break;
    default:
        file = "/clone/horse/ziliuma";
    }
    call_other( file, "???" );
    err = catch( horse = new( file ) );
    if ( err || !ob->query( "whistle" ) || me->query_temp( "is_riding" ) )
    {
        message_vision( HIM "$N" HIM "����һ�����ڣ�"
                "Ȼ��ʲôҲû�з��� :)\n" NOR, me );
        return(1);
    }
    horse->move( environment( me ) );
    horse->reset_action();
    horse->set_leader( me );
    message_vision( HIC "$N" HIC "�ó����ڴ���һ����"
            "һƥ$n" HIC "��Զ�����˹�����\n" NOR, me, horse );
    ob->add( "whistle", -1 );
    if ( me->is_fighting() )
        me->start_busy( 1 + random( 3 ) );

    return(1);
}
