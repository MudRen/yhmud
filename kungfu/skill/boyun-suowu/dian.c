#include <ansi.h>

inherit F_SSERVER;

string name()
{
	return("������");
}

int perform( object me, object target )
{
	int	ap, dp/*, damage*/;
	string	msg;

	if ( !target )
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if ( me->query_temp( "weapon" ) )
		return(notify_fail( "��ֻ�ܿ���ʹ�á������㡹��\n" ) );

	if ( !me->is_fighting( target ) )
		return(notify_fail( "ֻ�ܶ�ս���еĶ���ʹ�á�\n" ) );

	if ( (int) me->query_skill( "boyun-suowu", 1 ) < 100 )
		return(notify_fail( "��ġ���������������죬����ʹ�á������㡹��\n" ) );

	if ( (int) me->query_skill( "biyun-xinfa", 1 ) < 100 )
		return(notify_fail( "��ı����ķ�����������\n" ) );

	if ( me->query( "neili" ) < 800 )
		return(notify_fail( "�������������\n" ) );

	ap	= me->query_skill( "hand" ) + me->query_dex() * 10;
	dp	= target->query_skill( "dodge" ) + target->query_dex() * 10;

	msg = HIG "$N����һ��������һ���黨�����������£����͡���һ�����ƿն�ȥ!\n"NOR;

	message_combatd( msg, me, target );

	me->add( "neili", -500 );

	if ( ap / 2 + random( ap ) > dp )
	{
		if ( !target->is_busy() )
			target->start_busy( ap / 100 + 2 );
		msg = HIC "$nȫ��پ�һ�飬�ƺ����ܶ�����\n"NOR;
	}else
		msg = HIM "ֻ��$n����һ�ã�һ��������ƿն�����\n"NOR;
	message_combatd( msg, me, target );

	return(1);
}