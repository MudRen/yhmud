// giveall.c

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count, num = 0;
        string target, gift_file, str;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
                
        if (! arg)  
                return notify_fail("������������鳬��5���������ҡ�\n\n"
				                   "�����ʽ�� gift </·��/Ŀ���ļ���> [����]\n\n"); 
    
        if (sscanf(arg, "%s %d", target, count) != 2) 
                target = arg;   
        
        if (sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target; 
        
        if (file_size(gift_file) == -1)
                return notify_fail("·������ȷ������ָ���������޷��ҵ���\n");
        
        seteuid(getuid());

        foreach(object player in users())
        {
                ob = new(target); 
                
                if (count > 1 && ob->query("base_unit")) 
                        ob->set_amount(count); 
                if (player->query("combat_exp") > 50000)
                {
                        num++ ;
                        ob -> move(player); 
                        tell_object(player, HIW "\n\n��Ȼ�Ӽ��߼�Զ������м��ٽ���һֻ���������"HIR"���"HIW"��������ҫ�߲ʹ�â��\n" NOR);
                        tell_object(player, HIC "��צ���ƺ�ץ��ʲô������ͻȻ"HIR"���"HIC"�ɿ���צ���и�����ֱ�������������\n" NOR);
                        tell_object(player, HIG "����һ��������һԾ�ɸ߽�����ץ�����У���������Ʈ����档\n\n" NOR);
                }
        }
        //str = sprintf("���� %d λ��ҵõ���%s��\n\n", sizeof(users()), target->query("name"));    
        str = sprintf("���� %d λ��ҵõ���%s��\n\n", num, target->query("name"));    
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��giveall ��Ʒ·�� [����]

�����ߵ�������ҷ�����Ʒ��
HELP
        );
        return 1;
}
