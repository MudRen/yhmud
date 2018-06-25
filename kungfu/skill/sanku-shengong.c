/*
 * sanku-shengong.c
 */

inherit FORCE;

int valid_force( string force )
{
	return(force == "biyun-xinfa");
}

int query_neili_improve( object me )
{
	int lvl;
	lvl = (int) me->query_skill( "sanku-shengong", 1 );
	return(lvl * lvl * 21 * 15 / 100 / 200);
}

int valid_enable( string usage )
{
	return(usage == "force");
}

int valid_learn( object me )
{
	if ( me->query_skill( "force", 1 ) < 40 )
		return(notify_fail( "��Ļ����ڹ�̫���ˡ�\n" ) );
	if ( me->query( "gender" ) == "����" && me->query_skill( "sanku-shengong", 1 ) > 49 )
		return(notify_fail( "���Ų�Ҫ�������޸����Ե��ˣ����޷�������������񹦡�\n" ) );

	return(::valid_learn( me ) );
}

int practice_skill( object me )
{
	return(notify_fail( "������ֻ����ѧ(learn)�������������ȡ�\n" ) );
}

string exert_function_file( string func )
{
	return(__DIR__ "sanku-shengong/" + func);
}
