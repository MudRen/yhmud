// ask.c

#include <ansi.h>

inherit F_CLEAN_UP;

string query_inquiry(object me, object ob);

string *msg_dunno = ({
	CYN "$n" CYN "ҡҡͷ��˵������û��˵����û��˵������\n" NOR,
	CYN "$n" CYN "�ɻ�ؿ���$N" CYN "��ҡ��ҡͷ��\n" NOR,
	CYN "$n" CYN "�����۾�����$N" CYN "����Ȼ��֪��$P" CYN "��˵ʲô��\n" NOR,
	CYN "$n" CYN "�����ʼ磬�ܱ�Ǹ��˵�����Բ����޿ɷ�档��\n" NOR,
	CYN "$n" CYN "˵�������š������ҿɲ��������������ʱ��˰ɡ���\n" NOR,
	CYN "$n" CYN "����һ�����˵�������Բ������ʵ�����ʵ��û��ӡ�󡣡�\n" NOR,
	CYN "$n" CYN "����$N" CYN "��������üͷ��˵�������Ҵ�û��˵�����£���ȥ�ʱ��˰ɡ���\n" NOR,
});

int main(object me, string arg)
{
        string dest, topic, msg;
        object ob;
        //mapping inquiry;
        object env;
        mixed info;

        seteuid(getuid());

        if (! arg)
                return notify_fail("��Ҫ��˭ʲô�£�\n");

        if (sscanf(arg, "%s about %s", dest, topic) != 2 &&
            sscanf(arg, "%s %s", dest, topic) != 2)
                return notify_fail("��Ҫ��˭ʲô�£�\n");

        env = environment(me);
        if (info = env->query("no_say"))
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("����ط����ܽ�����\n");
                return 1;
        }

        if (! objectp(ob = present(dest, env)))
                return notify_fail("����û������ˡ�\n");

        if (me->ban_say(1) && playerp(ob))
                return 0;

        if (! ob->is_character())
        {
                message_vision("$N����$n��������....\n", me, ob);
                return 1;
        }

        if (ob == me)
        {
                message_vision("$N�Լ��������\n", me);
                return 1;
        }

        if (me->query("jing") < 30 && ! playerp(ob) && ! me->is_ghost())
        {
                write("�����ڵľ���̫�ã�û���ͱ����״ɡ�\n");
                return 1;
        }

        if (! ob->query("can_speak"))
        {
                message_vision(CYN "$N" CYN "��$n" CYN 
                               "�����йء�" HIG + topic + NOR CYN "��"
                               "����Ϣ������$p��Ȼ�������˻���\n" NOR, me, ob);
                return 1;
        }

        if (! INQUIRY_D->parse_inquiry(me, ob, topic))
                message_vision(CYN "$N" CYN "��$n" CYN "�����йء�" HIG +
                               topic + NOR CYN "������Ϣ��\n" NOR, me, ob);

        if (! living(ob))
        {
                message_vision("���Ǻ���Ȼ�ģ�$n���ڵ�״��û�а취��$N�κδ𸲡�\n",
                        me, ob);
                return 1;
        }

        if (playerp(ob) || ob->is_chatter())
        {
                ob->set_temp("ask_you", me->query("id"));
                return 1;
        }

        if (! me->is_ghost()) me->receive_damage("jing", 10 + random(10));
        if (msg = ob->query("inquiry/" + topic) ||
            msg = ob->accept_ask(me, topic))
        {
                if (stringp(msg))
                {
                        message_vision(CYN "$N˵����" + msg + "\n" NOR, ob);
                        return 1;
                }
        } else
        if (topic == "all")
        {               
                 query_inquiry(me, ob);
                 return 1;
        } else
                message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);

        return 1;
}

// �� npc ���϶�ȡ inquiry
string query_inquiry(object me, object ob)
{
        int i = 0;
        mapping inq;
        string str = "", *indexs;
        
        if (mapp(inq = ob->query("inquiry")))
        {
                indexs = keys(inq);
                for (i = 0; i < sizeof(indexs); i++)
                {
                        //str += HIB + indexs[i] + " " NOR;
                        str += HIY "  ��" + chinese_number(i+1) + "����" HIG + indexs[i] + "\n" NOR;
                }
                str = "�й���\n" + str + "��Щ���飬������֪���Ļ��������ң�";    
                tell_room(environment(me), CYN + ob->name() + "��" + me->name() + "����С����˵��Щ����\n" NOR, ({ me, ob }));
                tell_object( me, GRN + ob->name() + "����Ķ�������˵����" + str + "\n" NOR);
                return "\n";
        }
        tell_object( me, ob->name(1) + "����˵����ʵ���ǶԲ�����ʲôҲ��֪��ѽ��\n");
        return "\n";
}

int help(object me)
{
        write( @HELP
ָ���ʽ: ask <someone> about <something>

���ָ���ڽ���ʱ����Ҫ, ͨ��������ɴ�һָ�����
��ý�һ������Ѷ��
Ԥ���ѯ������:
        here
        name
        all
        clue
        rumor

���е�about����ʡ�ԡ�
HELP );
        return 1;
}

