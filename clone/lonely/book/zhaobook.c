// zhaobook.c 

inherit BOOK;
inherit F_UNIQUE;

#include <ansi.h>; 

void setup()
{}

void create()
{
        set_name(YEL"��������¡�" NOR, ({ "can zhang","book", }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "paper");
                set("long",
        "����һ��������С���ӣ�������ʮ�ֵĲоɣ�����д��һ\n"
        "Щ���������С�֣���֪��������ʲô�ġ�\n", );
		set("skill", ([
			"name"        : "jinzhong-zhao",
			"exp_required":	800000,
			"jing_cost"   :	150,
			"neili_cost"  :	150,
			"difficulty"  :	98,
			"max_skill"   : 180,
			"min_skill"   : 0,
		]));
        }
}

void init()
{
       
        add_action("do_yanjiu", "yanjiu");
        add_action("do_yanjiu", "research");
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        //object ob;

        string skill, book, msg;
        //int lv;

        if (! arg)
        {
                write("�ж�����������ָ���ʽ��read <����> from <����������>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", skill, book) != 2)
        {
                write("�ж�����������ָ���ʽ��read <����> from <����������>\n");
                return 1;
        }
        
        if (me->query("con") < 33)
        {
                write("����������̫�û����������ֵľ���\n");
                return 1;
        }
        
        if (me->query("str") < 33)
        {
                write("����������̫�û����������ֵľ���\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (where->query("no_fight")
           && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж����������š�\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (! id(book))
        {
                write("����û���Ȿ�顣\n");
                return 1;
        }

        if (skill != "zhao")
        {
                write("�����������ϲ�û�м���������о������ݡ�\n" NOR);
                return 1;
        }

        if ((int)me->query("combat_exp") < 2000000)
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if (skill == "zhao")
        {
           if (me->query("can_perform/jinzhong-zhao/zhao"))
           {
                write("�㲻���Ѿ�������\n");
                return 1;
           }
           if (me->query_skill("jinzhong-zhao", 1) < 150)
           {
                write("��Խ����ֵ�֪ʶ�������죬�޷��ж��˾��У�\n");
                return 1;
           }

           if (random (5) != 1)
           {
                write("���о��˰��죬��Ȼ�޷����������֡��ڻ��ͨ��\n");
                me->start_busy(15); 
                me->set("jing", 1);
                return 1;
           }
           msg = HIG "$N" HIG "��ͣ�����ط������ϵ����ݣ���ϸ�о����������ص���ѧ�����Ǽ��������"
                     "����\n" NOR;

           msg += HIG "$N" HIG "�������������쳤Хһ����һ����������˲�佫���Χ����!\n" NOR; 
           message_vision(msg, me); 

           if (me->can_improve_skill("parry"))
                   me->improve_skill("parry", 1500000);
           if (me->can_improve_skill("jinzhong-zhao"))
                   me->improve_skill("jinzhong-zhao", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "��ѧ���ˡ�" HIW "������" HIW "����\n" NOR);
           me->set("can_perform/jinzhong-zhao/zhao", 1);
           
           return 1;
        }    
}

int do_yanjiu(string arg)
{
        object me = this_player();
        object where = environment(me);
        //object ob;
        string pfm, canzhang;
       // int lv;

        if (! arg)
        {
                write("�о�������ָ���ʽ��research|yanjiu <����> from <�������>\n");
                return 1;
        }

        if (sscanf(arg, "%s from %s", pfm, canzhang) != 2)
        {
                write("�о�������ָ���ʽ��research|yanjiu <����> from <�������>\n");
                return 1;
        }

        if (me->is_busy())
        {
                write("��������æ���ء�\n");
                return 1;
        }

        if (me->is_fighting())
        {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }

        if (where->query("no_fight") && me->query("doing") != "scheme")
        {
                write("���޷������ﾲ�������ж�������¡�\n");
                return 1;
        }

        if (! me->query_skill("literate", 1))
        {
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }

        if (! id(canzhang))
        {
                write("��Ҫ�о�ʲô��\n");
                return 1;
        }

        if (pfm != "zhao")
        {
                write("�Ȿ���ϲ�û�м��������о��ľ��С�\n");
                return 1;
        }

        if ((int)me->query("combat_exp") < 300000)
        {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }
                   
        if (pfm == "zhao")
        {
           if (me->query("can_perform/jinzhong-zhao/zhao"))
           {
                write("�㲻���Ѿ�������\n");
                return 1;
           }
           if (me->query_skill("jinzhong-zhao", 1) < 150)
           {
                write("��Խ����ֵ�֪ʶ�������죬�޷��ж��˾��У�\n");
                return 1;
           }

           if (random (5) != 1)
           {
                write("���о��˰��죬��Ȼ�޷����������֡��ڻ��ͨ��\n");
                me->start_busy(15); 
                me->set("jing", 1);
                return 1;
           }
           message_vision(HIG "$N" HIG "��ͣ�����ط������ϵ����ݣ���ϸ�о����������ص���ѧ�����Ǽ��������"
                     "����\n" NOR,me);

           message_vision(HIG "$N" HIG "�������������쳤Хһ����һ����������˲�佫���Χ����!\n" NOR,me); 
//           message_vision(msg, me); 

           if (me->can_improve_skill("parry"))
                   me->improve_skill("parry", 1500000);
           if (me->can_improve_skill("jinzhong-zhao"))
                   me->improve_skill("jinzhong-zhao", 1500000);
           if (me->can_improve_skill("martial-cognize"))
                   me->improve_skill("martial-cognize", 1500000);

           write(HIW "��ѧ���ˡ�" HIW "������" HIW "����\n" NOR);
           me->set("can_perform/jinzhong-zhao/zhao", 1);
           
           return 1;
        }    
}
