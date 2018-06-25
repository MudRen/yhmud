// summon. ȡ�ر���

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
    object ob;
    string msg, *ks;
    mapping summon;
    int i;

    if (! str)
    {
            summon = me->query("can_summon");
            if (! mapp(summon) || ! sizeof(summon))
                    return notify_fail("��Ҫ�ٻ�ʲô��Ʒ��\n");

            ks = keys(summon);
            msg = "�����ڿ����ٻ�����Ʒ�У�\n";

            for( i=0; i<sizeof(ks); i++ )
            {
                    if( !get_object(summon[ks[i]]) ) continue;
                    msg += sprintf(HIW "��ƷID��" MAG "%-15s" NOR HIW"    ��Ʒ���֣�%-20s\n"NOR,ks[i],summon[ks[i]]->name());
            }
            write(msg);
            return 1;
    }

    if (! stringp(str = me->query("can_summon/" + str)))
            return notify_fail("�㲻֪������ٻ������Ʒ��\n");

    if (me->is_ghost())
        return notify_fail("���㻹�������ٻ��ɡ�\n");

    call_other(str, "???");
    ob = find_object(str);
    if (! ob || ! ob->receive_summon(me))
    {
            message_vision(HIM "$N" HIM "��������������������"
                           "�ʡ�\nȻ��ʲôҲû�з��� :)\n", me);
    }

    return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : summon <��Ʒ��ID>

��ָ��������ĳЩ��Ʒ����������װ���ϣ���Ȼ�����һ����
����ʩչ�������С�
HELP
    );
    return 1;
}
