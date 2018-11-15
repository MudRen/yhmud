// banker.c ���м�
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands

#include <dbase.h>
#include <ansi.h>
#define REBOOT_CMD      "/cmds/arch/reboot"

int do_check()
{
        // here we use 3 units to display bank infos
        int total = (int)this_player()->query("balance");
        if (!total || total < 0)
        {
                this_player()->set("balance", 0);
                write("���ڱ��̺�û�д�Ǯ��\n");
                return 1;
        }
        write(this_object()->query("name")+"���ĸ����㣺���ڱ��̺Ź�����" + 
              MONEY_D->money_str(total) + "��\n");
        return 1;                                                               
}

int do_convert(string arg)
{
        string from, to;
        int amount, bv1, bv2;
        object from_ob, to_ob;
        object me;

        me = this_player();                                                     

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
        {
           	return notify_fail("�����ʽ��convert|duihuan <����> <���ҵ�λ> to <�»��ҵ�λ>\n");
        }

        from_ob = present(from + "_money", me);
        to_ob = present(to + "_money", me);

        if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
           	return notify_fail("����һ���ʲô��\n");

        if (! from_ob)
           	return notify_fail("������û�д�����Ǯ��\n");

	if (from_ob == to_ob)
		return notify_fail("����ë������\n");

        if (amount < 1)
           	return notify_fail("�����׬����\n");

        if ((int)from_ob->query_amount() < amount)
           	return notify_fail("�����" + from_ob->query("name") +
				   "������\n");

        bv1 = from_ob->query("base_value");
        if (! bv1)
           	return notify_fail("����������ֵǮ��\n");

        bv2 = to_ob ? to_ob->query("base_value")
		    : call_other("/clone/money/" + to, "query", "base_value");
        if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
        if (amount == 0)
           	return notify_fail("��Щ" + from_ob->query("name") +
				   "��������\n ");

	if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
		return notify_fail("Ŷ��...����һ���ӻ��ò�����ô��ɢǮ...\n");

        // allowed to convert now
        me->start_busy(1);

        from_ob->add_amount(-amount);

        if (! to_ob)
        {
                to_ob = new("/clone/money/" + to);
                to_ob->set_amount(amount * bv1 / bv2);
                to_ob->move(me, 1);
        }
        else
                to_ob->add_amount(amount * bv1 / bv2);

        message_vision(sprintf("$N������ȡ��%s%s%s��������%s%s%s��\n",
        		       chinese_number(amount),
			       from_ob->query("base_unit"),
			       from_ob->query("name"),
        		       chinese_number(amount * bv1 / bv2),
			       to_ob->query("base_unit"),
        		       to_ob->query("name")), me);

        return 1;
}                                                                               

int do_deposit(string arg)                                                      
{
        string what;
        int amount/*, money_limit*/;
        object what_ob, me;

        me = this_player();

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (! arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��deposit:cun <����> <���ҵ�λ>\n");

        what_ob = present(what + "_money", me);
        if (! what_ob)
                return notify_fail("������û�д�����Ǯ��\n");

        if (amount < 1)
                return notify_fail("��������" + what_ob->query("name") +
				   "��\n");

        if ((int)what_ob->query_amount() < amount)
                return notify_fail("�����" + what_ob->query("name") +
				   "������\n");

        // deposit it
        me->start_busy(1);

        me->add("balance", what_ob->query("base_value") * amount);
        what_ob->add_amount(-amount);
        message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
        chinese_number(amount), what_ob->query("base_unit"),
        what_ob->query("name")), me);

        return 1;
}

int do_withdraw(string arg)
{
        string what;
        int amount/*, money_limit*/;
        object /*what_ob,*/ me;
        int v;

        me = this_player();

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if (this_object()->is_fighting())
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
                return notify_fail("�����ʽ��withdraw|qu <����> <���ҵ�λ>\n");

        if (amount < 1)
                return notify_fail("����ȡ������Ǯ��\n");

        if(amount >= 10000)
                return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

        if (file_size("/clone/money/" + what + ".c") < 0)
                return notify_fail("����ȡ��ʲôǮ��\n");

        what = "/clone/money/" + what;
        if ((v = amount * what->query("base_value")) > me->query("balance") ||
            v <= 0)
               return notify_fail("����Ǯ����ȡ��\n");

        me->start_busy(1);

        me->add("balance",  -v);
        MONEY_D->pay_player(me, v);

        message_vision(sprintf("$N��������ȡ��%s��\n", MONEY_D->money_str(v)), me);

        return 1;
}

int do_transfer(string arg)
{
        string who, what;
        int value;
        object me, ob;
        int amount;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( REBOOT_CMD->is_rebooting() )
                return notify_fail("���ڱ�վ����׼��������������Ǯׯ��ͣת�ʹ��ܡ�\n");

        if( !arg || sscanf(arg, "%d %s to %s", amount, what, who) != 3 )
                return notify_fail("�����ʽ��transfer|zhuan <����> <���ҵ�λ> to <ĳ��>\n");

		if( amount < 1 )
                return notify_fail("����ת�ʶ���Ǯ��\n");

        if( amount > 10000 )
                return notify_fail("��ô�����Ŀ����ϴǮ�����ɣ�����ɲ��ҷ�����\n");

        if( file_size("/clone/money/" + what + ".c") < 0 )
                return notify_fail("����ת��Ǯ�ĵ�λ�ǣ�\n");
			
		what = "/clone/money/" + what;
        value = amount * what->query("base_value");

		if( value > me->query("balance") || value <= 0 )
               return notify_fail("����Ǯ����ת�ʡ�\n");

		if( !objectp(ob = UPDATE_D->global_find_player(who)) )
                return notify_fail("û������ˣ�\n");
		
        me->start_busy(1);

        me->add("balance", -value);
        ob->add("balance", value);
        me->save();
        ob->save();
        
        tell_object(ob, HIR + me->query("name") + HIR "�������ﻮת"+ MONEY_D->money_str(value) + "������ʻ��ϡ�\n" NOR);
        tell_object(me, HIR "��������ﻮת"+ MONEY_D->money_str(value) + "��" + ob->query("name") + HIR "���ʻ��ϡ�\n" NOR);
        UPDATE_D->global_destruct_player(ob);
        return 1;
}

int do_zhuans(string arg)
{
        string who;
        object me, ob;
        int amount;

        me = this_player();

        if( me->is_busy() )
                return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

        if( this_object()->is_fighting() )
                return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

        if( REBOOT_CMD->is_rebooting() )
                return notify_fail("���ڱ�վ����׼��������������Ǯׯ��ͣת�ʹ��ܡ�\n");

        if( !arg || sscanf(arg, "%d to %s", amount, who) != 2 )
                return notify_fail("�����ʽ��zhuans <����> to <ĳ��>\n");

		if( amount < 1 )
                return notify_fail("����ת�����Ź���\n");
			
		if( amount < 10000 )
                return notify_fail("һ������ת1w��\n");

        if( amount > 500000 )
                return notify_fail("һ�����ת50w��\n");

        if( amount > me->query("gongxian"))
               return notify_fail("����Ź����񲻹��ɡ�\n");

		if( !objectp(ob = UPDATE_D->global_find_player(who)) )
                return notify_fail("û������ˣ�\n");
		
        me->start_busy(1);

        me->add("gongxian", -amount);
        ob->add("gongxian", amount / 2);
        me->save();
        ob->save();
        
        tell_object(ob, HIR + me->query("name") + HIR "ת��"+ amount + "�Ź����㡣\n" NOR);
        tell_object(me, HIR "��ת��" + amount + "�Ź���" + ob->query("name") + "��\n" NOR);
        UPDATE_D->global_destruct_player(ob);
        return 1;
}