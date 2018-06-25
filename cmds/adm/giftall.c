// giveall.c

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object ob;
        int count;
        string target, gift_file, str;
        object pob;
        mapping ips;
        string ip, *ks;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg)
                return notify_fail("�������������ң�ͬIP������ѡ��һλ��\n\n�����ʽ�� giftall </·��/../Ŀ���ļ���> <����>\n\n");

        if (sscanf(arg, "%s %d", target, count) != 2)
                target = arg;

        if (sscanf(target, "%*s.c") != 1)
                target += ".c";
        gift_file = target;

        if (file_size(gift_file) == -1)
                return notify_fail("·������ȷ���޷��ҵ���Ʒ��\n");

        seteuid(getuid());

        ips = ([ ]);
        foreach (pob in all_interactive())
        {
                if( wizardp(pob) || !pob->query("born") || 
                    ! living(pob) || ! environment(pob) ||
                    pob->is_ghost())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (sizeof(ips) >= 1)
        {
                ks = keys(ips);
                foreach(ip in ks)
                {
                        pob = ips[ip][random(sizeof(ips[ip]))];
                        ob = new(target);

                        if( count>1 && ob->query("base_unit") )
                                ob->set_amount(count);

                        ob->move(pob);

                        tell_object(pob, HIW "\n\n��Ȼ�Ӽ��߼�Զ������м��ٽ���һֻ���������"HIR"���"HIW"��������ҫ�߲ʹ�â��\n" NOR);
                        tell_object(pob, HIC "��צ���ƺ�ץ��ʲô������ͻȻ"HIR"���"HIC"�ɿ���צ���и�����ֱ�������������\n" NOR);
                        tell_object(pob, HIG "����һ��������һԾ�ɸ߽�����ץ�����У���������Ʈ����档\n\n" NOR);

                }
                str=sprintf("����%dλ��ҵõ���%s��\n\n",sizeof(ks),get_object(target)->query("name"));
                me->start_more(str);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ��giftall|gift <��Ʒ·��> <����>

�����ߵ�ÿһ��IP�����һ�����
HELP
        );
        return 1;
}
