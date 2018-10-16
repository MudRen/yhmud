// special

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string msg, msg1, msg2;
		mixed files;
        mapping ss;
        string  skill;
        object ob;
        string pro;
		int i, m;

        if (wizardp(me) && stringp(arg) &&
            objectp(ob = find_player(arg)))
                // �鿴������ҵ����⼼��
                arg = 0;
        else
                ob = me;

        pro = (ob == me) ? "��" : ob->name(1);

        if (! ob->query("born") && ! ob->query("reborn"))
                return notify_fail(pro + "��û�г����ţ���ʲô�ؼ���\n");

        if (! mapp(ss = ob->query("special_skill")) ||
            ! sizeof(ss))
                return notify_fail(pro + "���ں���ʲô�ؼ�������Ŷ��\n");

        if (arg && (ob == me))
        {
                // �в����������ؼ���
                if (me->is_busy())
                        return notify_fail("������æ���أ�����ʹ���ؼ���\n");

                if (sscanf(arg, "%s %s", skill, arg) != 2)
                        skill = arg;

                if (! me->query("special_skill/" + skill))
                        return notify_fail("�㲻�������ؼ�����\n");

                if (file_size(SPECIAL_D(skill) + ".c") < 0)
                        return notify_fail("����û�������ؼ�...\n");

                return SPECIAL_D(skill)->perform(me, skill, arg);
        }

		files = ({ "guibian", "guimai", "jinshen", "piyi",
                   "qinzong", "wuxing", "shenyan", "tiandao",
                });
				
        msg = pro + "���ڻ�������Щ�ؼ���\n";
		msg1 = "";
		msg2 = "";
 /*       foreach (skill in keys(ss))
        {
                if (file_size(SPECIAL_D(skill) + ".c") < 0)
                {
                        write("�����ڼ��ܣ�" + skill + "\n");
                        continue;
                }
                msg += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
        }*/
		foreach (skill in keys(ss))
		{
			m = 0;
			for (i = 0; i < sizeof(files); i++)
			{
				if (skill == files[i])
				{
					msg2 += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
					m = 1;
				}
				
			}
			if (m < 1)
				msg1 += SPECIAL_D(skill)->name() + "(" YEL + skill + NOR ")\n";
		}
		msg += msg1;
		if (msg2 != "")
		{
			msg += HIG " ת ��\n";
			msg += msg2;
		}
        write(msg);
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : special <skill> | <���ID>

ʹ������������Բ鿴����ؼ������Ҫ��������ؼ�������Լ���
����ָ��ʹ��ʲô�ؼ������磺special hatred������ɱ����

��ʦ���Բ鿴���������������⼼�ܡ�

HELP );
    return 1;
}
