/*
 * This program is a part of NT MudLIB
 * liu.c ������Ӱ
 */

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name()
{
	return(HIR "������Ӱ" NOR);
}

int perform( object me, object target )
{
	int	skill;
	object	weapon;

	if ( !target )
		target = offensive_target( me );

	if ( !target
	     || !target->is_character()
	     || !me->is_fighting( target ) )
		return(notify_fail( "��������Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n" ) );

	if ( !objectp( weapon = me->query_temp( "weapon" ) ) ||
	     (string) weapon->query( "skill_type" ) != "sword" )
		return(notify_fail( "�������ʹ�ý�ʱ����ʹ����������Ӱ����\n" ) );

	if ( me->query( "neili" ) < 400 )
		return(notify_fail( "��Ŀǰ���������㣬�޷�ʩչ��������Ӱ����\n" ) );

	if ( (skill = me->query_skill( "wuzhan-mei", 1 ) ) < 100 )
		return(notify_fail( "�����չ÷�����������죬�޷�ʹ�á�������Ӱ����\n" ) );

	if ( me->query_skill_mapped( "sword" ) != "wuzhan-mei" )
		return(notify_fail( "��û�м�����չ÷������ʩչ��������Ӱ����\n" ) );

	me->add( "neili", -300 );

	message_combatd( HIC "$N����" + weapon->name() + "�Ҷ����ó�һƬ��⣬"
	                 "ʩչ�����ž�ѧ��" + name() + HIC "����\n\n" NOR, me );

	me->add_temp( "apply/attack", skill / 2 );
	for ( int i = 0; i < 5; i++ )
	{
		/* COMBAT_D->do_attack(me,target,TYPE_QUICK); */
		COMBAT_D->do_attack( me, target, weapon, 0 );
	}

	/*
	 * if( random(query("force", target))<query("force", me)/2 )
	 * {
	 *      target->apply_condition("weapon_bleeding", 5+random(3));
	 * }
	 */
	me->add_temp( "apply/attack", -skill / 2 );
	me->start_busy( 2 );
	return(1);
}
