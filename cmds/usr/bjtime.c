/* bjtime.c */
#include <ansi.h>
#include <festival.h>

inherit F_CLEAN_UP;

int main( object me, string arg )
{
	int day, day1, day2, month, *date;
	write( sprintf( "���ڵ�ʱ���Ǳ���ʱ�� " + ctime( time() ) + "��\n" ) );
	date	= localtime( time() + 8 * 60 * 60 );
	month	= date[4] + 1;
	day		= date[3];
	day1	= BEGIN_DAY - day;
	day2	= END_DAY - day;

	if ( month == FETEMONTH )
	{
		if ( day1 > 1 )
			write( sprintf( BBLU HIR "\n\t\t����" HIY + FETEDAY + HIR "����" HIY "%s" HIR "�죡\t\t\n" NOR,
					chinese_number( BEGIN_DAY - day - 1) ) );
		else if ( day1 == 1 )
			write( sprintf( BBLU HIR "\n\t\t������" HIY + FETEDAY + HIR "��\t\t\n\n" NOR ) );
		else if ( day1 == 0 )
			write( sprintf( BBLU HIY "\n\t\t������" + FETEDAY + "��\t\t\n\n" NOR ) );
		else if ( day2 > 0 )
			write( sprintf( BBLU HIR "\n\t\t����" HIY + FETEDAY + HIR "��������" HIY "%s" HIR "�죡\t\t\n" NOR,
					chinese_number( END_DAY - day ) ) );
		else if ( day2 == 0 )
			write( sprintf( BBLU HIR "\n\t\t������" HIY + FETEDAY + HIR "���һ�죡\t\t\n" NOR ) );
	}
	return(1);
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ���������ʵ���������ڵ�ʱ�䡣

HELP);
    return 1;
}
