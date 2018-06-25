// ��ѯ����������������ָ��

#include <ansi.h>
#define INVASIOND "/adm/daemons/invasion/invasiond"
#define TOTAL_INVADER 24
#define TURN 3600

inherit F_CLEAN_UP;

int main(object me)
{
     int i, len, time;
     string msg, title, name, exist, killer, space, number;
     msg = "";
     space = "                                            ";

     if ( ! find_object(INVASIOND) || ! INVASIOND->query("record") )
     {
        write("����û�����ֵ���С�\n");
        return 1;
     }

     write(HIW"Ŀǰ�����˹���������ս����\n"NOR);
     write(HIM"���      �ȼ�         ����                ״̬     ɱ��Ӣ��\n"NOR);

     for(i=0; i< TOTAL_INVADER; i++)
     {
        title = INVASIOND->query("record/" + i + "/title");
        name = INVASIOND->query("record/" + i + "/name");
        if  ( INVASIOND->query("record/" + i + "/exist") == 1 )
        {
           exist = HIG"δ��"NOR + "   ";
        }  else
        {
           exist = HIR"����"NOR + "   ";
        }

        killer = INVASIOND->query("record/" + i + "/killer");
        if ( ! killer )  killer = "";
        if (i < 9 )
        {
           number = " " + HIR + (i + 1) + NOR + "  ";
        } else
        {
           number = HIR + (i + 1) + NOR + "  ";
        }
        len = sizeof(name);
        len = 22 - len;
        msg +=  number +
                title + "  " + name + space[0..len] + exist +
                HIG + killer + NOR + "\n";
     }

     write (msg);
     time = ( TURN - time() + INVASIOND->query("record/born_time") ) / 60;
     if ( time < 0 ) time = 0;
     write(HIC"Ŀǰ������һ��������ֻ���" + time + "���ӡ�\n");
     return 1;
}

int help(object me)
{
        write(@HELP
���ָ����������ѯ�˹�������������������

HELP);
        return 1;
}

