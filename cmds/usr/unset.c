// unset.c
#include <ansi.h>

inherit F_CLEAN_UP;

int help();

int main(object me, string arg)
{
	if( !arg || arg=="" ) return help();

	me->delete("env/" + arg);
        //if (arg == "show_map")
                //write(ESC+"[r"+TOBOT(50));
	write("Ok.\n");
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��unset <������>

���ָ������ɾ�������������趨��

�޸ı����趨���� unset ָ�
TEXT
	);
	return 1;
}
