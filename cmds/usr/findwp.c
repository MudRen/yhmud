// findwp Ѱ������

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
    object ob, owner;
    string msg, *ks;
    mapping summon;
    int i;

	if (! str)
    {
            summon = me->query("can_summon");
            if (! mapp(summon) || ! sizeof(summon))
                    return notify_fail("��ҪѰ��ʲô��Ʒ��\n");

            ks = keys(summon);
            msg = "�����ڿ���Ѱ�ҵ���Ʒ�У�\n";

            for( i=0; i<sizeof(ks); i++ )
            {
                    if( !get_object(summon[ks[i]]) ) continue;
                    msg += sprintf(HIW "��ƷID��" MAG "%-15s" NOR HIW"    ��Ʒ���֣�%-20s\n"NOR,ks[i],summon[ks[i]]->name());
            }
            write(msg);
            return 1;
    }

    if (! stringp(str = me->query("can_summon/" + str)))
            return notify_fail("�㲻֪�����Ѱ�������Ʒ��\n");

    if (me->is_ghost())
        return notify_fail("���㻹�������ٻ��ɡ�\n");

    ob = find_object(str);
	if (! ob) ob = load_object(str);
	
	owner = environment(ob);
	if (owner == me)
	{
		tell_object(me, "��Ϲ�������������Լ�������\n");
		
	} 
	else
	if (! owner)
		tell_object(me, "����˺�����ʧ�ˣ�\n");
	else
		tell_object(me, "���"+ ob->query("name") + "��" + owner->query("name") + "�����ȥ�����ɡ�\n");
	
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : findwp <��Ʒ��ID>

��ָ�������Ѱ���Լ���������Ʒ��
HELP
    );
    return 1;
}
