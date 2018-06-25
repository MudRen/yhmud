// news cmds
// by Doing
#include <ansi.h> 
inherit F_CLEAN_UP;

#ifndef NEWS_D
#define NEWS_D          "/adm/daemons/newsd"
#endif

int main(object me, string arg)
{
	/*
        if (! arg || arg == "" || arg == "all")
        {
                NEWS_D->show_news(me, (arg != "all") ? 1 : 0);
                return 1;
        }

        if (sscanf(arg, "discard %s", arg))
        {
                NEWS_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                NEWS_D->do_post(me, arg);
                return 1;
        }

        NEWS_D->do_read(me, arg);
        return 1;
        */
         if( !wizardp(me) && time() - me->query_temp("last_news")<3 )
        {
                write("ϵͳ�������̾���������� ....\n");  
                return 1;
        }
        me->set_temp("last_news", time());
        
        if (! arg || arg == "" || arg == "all")
        {
                NEWS_D->show_news(me, (arg != "all") ? 1 : 0);
                write(HIC "�Ķ�����ָ���ʽ��" HIY "news " NOR "<" HIY "new" NOR "|" HIY "all" NOR "|" HIY "���ű��" NOR ">\n"
                      HIC "��������ָ���ʽ��" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "�ؼ���" NOR "|" HIM "�ؼ���" NOR ">\n");
                return 1;
        }

        if (sscanf(arg, "discard %s", arg) || sscanf(arg, "del %s", arg))
        {
                NEWS_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg) || sscanf(arg, "add %s", arg))
        {
                NEWS_D->do_post(me, arg);
                return 1;
        }

        if (sscanf(arg, "search %s", arg) || sscanf(arg, "find %s", arg))
        {
                NEWS_D->do_search(me, arg);
                //write(HIC "�Ķ�����ָ���ʽ��" HIY "news " NOR "<" HIY "new" NOR "|" HIY "���ű��" NOR ">\n"
                     // HIC "��������ָ���ʽ��" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "�ؼ���" NOR "|" HIM "�ؼ���" NOR ">\n");
                return 1;
        }

        NEWS_D->do_read(me, arg);
        //write(HIC "�Ķ�����ָ���ʽ��" HIY "news " NOR "<" HIY "new" NOR "|" HIY "next" NOR "|" HIY "���ű��" NOR ">\n"
         //     HIC "��������ָ���ʽ��" HIG "news search " NOR "<" HIG "title" NOR "|" HIG "author" NOR "|" HIG "document" NOR "> <" HIM "�ؼ���" NOR "|" HIM "�ؼ���" NOR ">\n");
        return 1;
}
/*
int help(object me)
{
	write(@HELP
ָ���ʽ : news [next] | [<���ű��>] | new | all

����ָ������������Ķ���Ϸ�е����š����еĸ��º���Ϣ����ͨ��
���ŷ����ġ�

ʹ�� new �������������Ķ���û�ж��������š�
ʹ�� all ������������鿴ϵͳĿǰ���е����š�

��վ����ʦ����ͨ��news post <����>���������š�news discard��
ɾ�����š�
HELP );
    return 1;
}
*/
int help(object me)
{
        write(@HELP
ָ���ʽ : news [<���ű��>] | new | all
           news search <title|author|document> <�ؼ���|�ؼ���>

����ָ����������Ķ���Ϸ�е����š����еĸ��º���Ϣ����ͨ������
�����ġ�

ʹ�� new �������������Ķ���û�ж��������š�
ʹ�� all ������������鿴ϵͳĿǰ���е����š�
ʹ�� search ���������������ϵͳĿǰ�����������������š�
     search <title|author|document> <�ؼ���|�ؼ���>
     ���ݱ��⡢���ߡ�������������ָ���ؼ��ֻ��߹ؼ��ʵ����š�
     ���磺news search title ת��ϵͳ ----���������б����а�
     ����ת��ϵͳ�������š�

��ʦ����ͨ��news post <����>���������š�news discard��ɾ�����š�
HELP );
    return 1;
}
