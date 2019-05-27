/* person used in quest */

#include <ansi.h>

inherit CLASS_D( "generate" ) + "/chinese";


#define WAITING     1
#define ATTACKING   2
#define OVER        3
#define GO_CMD      "/cmds/std/go"

void random_move();


int leave();


int  is_stay_in_room()
{
    return(1);
}


mapping fam_info;

int filter_listener( object ob )
{
    if ( ob->query( "env/no_story" ) )
        return(0);
    return(1);
}


void create()
{
    ::create();
    set( "gender", "����" );
    set( "age", 30 + random( 30 ) );
    set( "long", "" );
    set( "attitude", "friendly" );
    set( "chat_chance", 30 );
    set( "chat_msg", ({ (: random_move:) }) );
    set( "chat_chance_combat", 120 );
    set( "scale", 150 );
    set( "no_get", 1 );

    set_temp( "apply/armor", 100 );
    set_temp( "apply/damage", 100 );
    set_temp( "born_time", time() );
    set_temp( "dest_time", 1800 + time() );

    add_money( "gold", 5 + random( 25 ) );

    fam_info = query( "fam_info" );

    if ( clonep() )
        keep_heart_beat();
}


void set_from_me( object me )
{
    int exp;
    mapping my;

    NPC_D->init_npc_skill( this_object(), NPC_D->get_exp( me ) );
    my = query_entire_dbase();

    if ( my["max_qi"] > 10000 )
        my["max_qi"] = 10000;

    if ( my["max_jing"] < my["max_qi"] / 2 )
        my["max_jing"] = my["max_qi"] / 2;

    if ( my["max_jing"] > 6000 )
        my["max_jing"] = 6000;

    my["eff_jing"]  = my["max_jing"];
    my["jing"]  = my["max_jing"];
    my["eff_qi"]    = my["max_qi"];
    my["qi"]    = my["max_qi"];

    exp = me->query( "combat_exp" ) * 11 / 10;
    if ( exp > query( "combat_exp" ) )
        set( "combat_exp", exp );

    my["jiali"] = query_skill( "force" ) / 2;
}


int accept_fight( object ob )
{
    command( "say �ҿ�û��Ȥ�����棬����ҹ�����" );
    return(0);
}


int accept_hit( object ob )
{
    command( "say ���Ұ�������������ʰ�㣡" );
    return(0);
}


int accept_kill( object ob )
{
    object  *t;
    object  *our;
    object  killer;

    if ( !living( this_object() ) )
        return(1);

    fam_info = query( "fam_info" );

    /* ����Ƿ������ڹ���״̬ */
    if ( "/adm/daemons/story/familywar"->query_status() != ATTACKING )
    {
        if ( ob->query( "family/family_name" ) == fam_info["family"] )
        {
            command( "say �ߣ���Ŀǰ���ڵȴ�ָ���������ȡ��������" );
            return(notify_fail( "���������˲�м���㽻�֡�\n" ) );
        }else  {
            command( "heng" );
            return(notify_fail( "���������˲�м���㽻�֡�\n" ) );
        }
    }else  { /* ֻ������ӵ���� */
        if ( !pointerp( t = ob->query_team() ) || !sizeof(t) || sizeof(t) < 2 )
        {
            command( "say �ҴӲ��͵�ǹƥ����˽��֡�" );
            return(notify_fail( "���������˲�м���㽻�֡�\n" ) );
        }

        message_vision( HIW "$N" HIW "�����е������ֵ��ǣ����һ���ϰ���ɱ��$n" HIW "��" +
                RANK_D->query_rude( this_object() ) + "����\n" NOR, ob, this_object() );

        foreach( killer in t )
        {
            if ( objectp( killer ) &&
                 living( killer ) && !killer->is_fighting( this_object() ) )
                killer->kill_ob( this_object() );
        }

        our = filter_array( all_inventory( environment() ), (: objectp( $1 ) &&
                                     !wizardp( $1 ) &&
                                     environment( $1 ) &&
                                     $1->query( "team_num" ) &&
                                     living( $1 ) &&
                                     !playerp( $1 ) :) );
        killer = 0;
        foreach( killer in our )
        {
            if ( objectp( killer ) &&
                 living( killer ) && !killer->is_fighting( ob ) )
                killer->kill_ob( ob );
        }
    }

    return(1);
}


int accept_ansuan( object ob )
{
    return(notify_fail( "���˾����Ժøߣ����������֡�\n" ) );
}


int accept_touxi( object ob )
{
    return(notify_fail( "���˾����Ժøߣ����������֡�\n" ) );
}


void die( object killer )
{
    object  dob;            /* �������NPC���� */
    int n;                  /* ���Խ������˵���Ŀ */
    int exp;                /* ��Ҫ�Ϸֵľ��� */
    int pot;                /* ��Ҫ�Ϸֵ�Ǳ�� */
    int weiwang;            /* ��Ҫ�Ϸֵ����� */
    int score;              /* ��Ҫ�Ϸֵ����� */
    int gongxian;           /*  */
    object  *t;             /* ɱ���ҵ��˵Ķ����б� */
    object  tob;
//  int i;

    /* �ҵ�ɱ����(NPC)���Ǵ����ҵ��� */
    if ( !objectp( dob = killer ) )
        dob = query_defeated_by();

    if ( !pointerp( t = dob->query_team() ) )
    {
        ::die();
        return;
    }

    if ( !sizeof(t) )
    {
        ::die();
        return;
    }

    if ( objectp( dob ) )
    {
        exp = 5000 + random( 5000 );
        pot = 2000 + random( 2000 );
        weiwang = 3000 + random( 6000 );
        score   = 3000 + random( 6000 );
        n   = sizeof(t);
        if ( !n || n < 4 )
        {
            exp /= 5;
            pot /= 5;
            weiwang /= 3;
            score   /= 3;
        }

        foreach( tob in t )
        {
            if ( objectp( tob ) && living( tob ) )
            {
                if ( tob->query( "family/family_name" ) == fam_info["family"] )
                    gongxian = 100 + random( 300 );

                else
                    gongxian = 0;

                GIFT_D->delay_bonus( tob,
                             (["exp"      : exp + ( (tob == dob) ? 2000 : 0),
                               "pot"      : pot + ( (tob == dob) ? 500 : 0),
                               "weiwang"  : weiwang + ( (tob == dob) ? 1000 : 0),
                               "score"    : score + ( (tob == dob) ? 1000 : 0),
                               "gongxian" : (n < 4 ? gongxian / 3 : gongxian),
                               "prompt"  : (pointerp( t ) ? "��Ķ������" + name() + "֮��" :
                                    "����" + name() + "֮��")]) );
            }
        }
        CHANNEL_D->do_channel( this_object(), "rumor",
                       sprintf( "��˵%s����%sʱ��%s�Ķ�������ˣ�",
                        name(), fam_info["family"], dob->query( "name" ) ) );
    }
    /* �������� */
    ::die();

    return;
}


void random_move()
{
    string  dir;
    string  * route;
//  object  master;
    object  *listeners;

    if ( time() > query_temp( "dest_time" ) ||
         "/adm/daemons/story/familywar"->query_status() == OVER )
    {
        message_vision( "$N����ææ�����ˡ�\n", this_object() );
        CHANNEL_D->do_channel( this_object(), "rumor",
                       sprintf( "��˵%s��Ȼ�ɹ��Ĺ���%s����Ҳ�������ˣ����ò����������չ����ơ�",
                        name(), fam_info["family"] ) );
        log_file( "static/killed_die", sprintf( "%s %s(%s) vanished because timeout(%d:%d).\n",
                            log_time(), name(), query( "id" ),
                            time() - query_temp( "born_time" ),
                            query_temp( "dest_time" ) - query_temp( "born_time" ) ) );
        destruct( this_object() );
        return;
    }

    if ( "/adm/daemons/story/familywar"->query_status() == WAITING )
    {
        listeners = filter_array( users(), (: filter_listener:) );

        if ( query( "is_leader" ) && random( 3 ) == 0 )
            message_vision( HIW "$N" HIW "˵�����������ǣ���Ҫ�ż����������ǹ���" +
                    fam_info["family"] + "����ɱ��~����\n" NOR, this_object() );
        else if ( random( 10 ) == 0 )
            message_vision( HIC "$N" HIC "���µ�������ô���컹�������" +
                    fam_info["family"] + "�Ҷ��ȵò��ͷ��ˣ���\n" NOR, this_object() );

        return;
    }
    fam_info    = query( "fam_info" );
    route       = fam_info["route_list"];

    /* �Ѿ��ߵ��յ� */
    if ( query( "move" ) >= sizeof(route) )
    {
        if ( base_name( environment() ) == fam_info["tar_room_fi"] )
        {
            if ( !this_object()->is_fighting() )
            {
                CHANNEL_D->do_channel( this_object(), "rumor",
                               "��˵������֯����" + fam_info["family"] + "��" + fam_info["tar_room_nm"] +
                               "��" + fam_info["family"] + "�Դ�Ԫ�����ˡ�\n" );
                FAMILY_D->add_family_fame( fam_info["family"], -1000 );
                "/adm/daemons/story/familywar"->change_status( OVER );
            }
        }

        return;
    }

    /* ����·���б��ƶ� */
    if ( stringp( dir = route[query( "move" )] ) )
    {
        command( "say �ֵ��ǳ尡��ɱ�������仨��ˮ��Ƭ�ײ�����" );
        if ( GO_CMD->main( this_object(), dir ) )
            add( "move", 1 );

        else if ( stringp( fam_info["spe_cmds"] ) )
            command( fam_info["spe_cmds"] );

        else return;
    }
}


void init()
{
    object me = this_player();

    fam_info = query( "fam_info" );

    if ( !living( me ) ||
         playerp( me ) ||
         me->query( "team_num" ) ||
         me->query( "family/family_name" ) != fam_info["family"] )
        return;

    if ( !"/cmds/std/kill"->main( this_object(), me->query( "id" ) ) )
        kill_ob( me );
}
