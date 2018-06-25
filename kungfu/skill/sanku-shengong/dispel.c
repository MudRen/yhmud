/* dispel.c */

#include <ansi.h>

int exert( object me, object target )
{
	int	i;
	string	force_name;
	mapping conditions;

	if ( me->query( "neili" ) < 300 )
	{
		write( "����������㣬�޷�����һ�����졣\n" );
		return(1);
	}

	force_name = to_chinese( me->query_skill_mapped( "force" ) );

	if ( me == target )
	{
		message_vision( HIW "$N" HIW "����һ�������ֻ��������˳�����\n" NOR, me );
		tell_object( me, YEL "��Ĭ��" + force_name +
			     "����ʼ�ų������е��쳣֢״��\n" NOR );
		me->add( "neili", -100 );
	} else{
		message_vision( HIW "$N" HIW "����һ������������ճ��$n"
				HIW "�ı���\n" NOR,
				me, target );
		tell_object( me, YEL "��Ĭ��" + force_name + "����ʼ����" +
			     target->name() + "�ų������е��쳣֢״��\n" NOR );
		tell_object( target, YEL + me->name() +
			     "�����˹��������ų������е��쳣֢״��\n" NOR );
		me->add( "neili", -250 );
	}

	conditions = target->query_condition();
	if ( conditions )
	{
		target->clear_condition();

		tell_object( target, YEL + me->name() + "�����˹����������е��쳣֢״�����ų���\n" NOR );
		if ( me == target )
		{
			tell_object( me, WHT "���Ϣ��ϣ��������ջص�"
				     "�\n" NOR );
			me->start_busy( 1 + random( 2 ) );
		} else{
			tell_object( me, WHT "���Ϣ��ϣ��������ջ�"
				     "���\n" NOR );
			tell_object( target, WHT "�������Ϣһ����������" +
				     me->name() + "�չ��ˡ�\n" );
			me->start_busy( 2 + random( 3 ) );
			if ( !target->is_busy() )
				target->start_busy( 1 + random( 2 ) );
			message_vision( WHT "$N�����ƴ�$n�������˻�"
					"����\n" NOR, me, target );
		}
	}

	return(1);
}
