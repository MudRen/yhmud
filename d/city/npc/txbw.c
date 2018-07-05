
#include <ansi.h>

inherit NPC;
inherit F_DEALER;

mixed  show_all();
mixed  ask_txbw();

void create()
{
        set_name(WHT "ʹ��" NOR, ({"shi zhe", "shi"}));
        set("long", "���²��为���ˡ�\n");
		set("title", YEL "���²���" NOR );
        set("gender", "����");
        set("age", 45);

        set("inquiry", ([
                "���²���" : (: show_all :),
                "ѧ����"     : (: show_all :),
        ]));
		
        setup();
}

void init()
{
        add_action("do_txbw", "txbw");
}

mixed show_all()
{
        object me = this_player();

        tell_object(me, "�����������ѧϰ�������ָ����ɵ������书������Ҫ֧��СС�ķ��ã�ֱ�ӿ۴��(5000 gold)��\n"
						"��ʽ��txbw <��������>, ������txbw shaolin-shenfa\n\n"
							"�Ṧ(dodge)  ��������(shaolin-shenfa), ��ɽ��(henshan-shenfa)\n"
							"צ��(claw)   ��С������(xiao-qinna),     ��ץ������(huzhua-shou)\n"
							"�ַ�(hand)   ��������(qingyun-shou),     ������(sanyin-shou),       ���ڴ���ӡ(dashou-yin)\n"
							"ȭ��(cuff)   ������ȭ��(bagua-quan),     ��ɽȭ��(songshan-quan),   ����ȭ��(qixing-quan)\n"
							"ָ��(finger) ������ָ��(canglang-zhi),   ����ָ��(zhongnan-zhi),    ���ָѨ��(tiangang-zhi)\n"
							"�Ʒ�(strike) ��������(jueqing-zhang),    ��ɽ�Ʒ�(huashan-zhangfa), ����������(benlei-zhang)\n"
							"ȭ��(unarmed)���Ʊ���(pobei-tui),        ��Ůȭ��(meinv-quan)\n"
							"�޷�(whip)   ��������(chanhun-suo),      Ыβ��(xiewei-bian)\n"
							"����(club)   �����๦(caiyan-gong),      ��Գ����(jinyuan-gun)\n"
							"�ȷ�(staff)  �������ȷ�(yinhu-zhang),    �����ȷ�(lingshe-zhangfa)\n"
							"����(blade)  ����Ѫ����(tiexue-dao),     ��������(chuangwang-dao)\n"
							"����(hammer) �������̷�(fenglei-panfa),  ���ϴ�����(dali-chu)\n"
							"�̱�(dagger) �����αʷ�(hexing-bifa),    ������Ѩ��(qingliang-daxuefa)\n\n");
        
        return 1;
}

int do_txbw(string arg)
{
	int i, n;
	string skill;
	object me = this_player();
	
	string *skill_list = ({
                "shaolin-shenfa",
				"henshan-shenfa",
				"xiao-qinna",
				"huzhua-shou",
				"qingyun-shou",
				"sanyin-shou",
				"dashou-yin",
				"bagua-quan",
				"songshan-quan",
				"qixing-quan",
				"canglang-zhi",
				"zhongnan-zhi",
				"tiangang-zhi",
				"jueqing-zhang",
				"huashan-zhangfa",
				"benlei-zhang",
				"pobei-tui",
				"meinv-quan",
				"chanhun-suo",
				"xiewei-bian",
				"caiyan-gong",
				"jinyuan-gun",
				"yinhu-zhang",
				"lingshe-zhangfa",
				"tiexue-dao",
				"chuangwang-dao",
				"fenglei-panfa",
				"dali-chu",
				"hexing-bifa",
				"qingliang-daxuefa",
        });
		
	if (! arg)
        {
                write("��ʽ��txbw <��������>, ������txbw shaolin-shenfa\n");
                return 1;
        }
		
	if (sscanf(arg, "%s", skill) != 1)
        {
                write("��ʽ��txbw <��������>, ������txbw shaolin-shenfa\n");
                return 1;
        }
	
	if ((int)me->query("combat_exp") < 800000)
        {
                write("���ʵս���鲻�㣬����Ҫ��Ŭ��������\n");
                return 1;
        }

    if ((int)me->query("balance") < 5000 * 100 * 100)//5000gold
        {
                write("��Ĵ��㡣\n");
                return 1;
        }
		
	for(i = 0; i < sizeof(skill_list); i++)
	{
		if (skill == skill_list[i])
		{
			if (me->query_skill(skill_list[i], 1) > 0)
			{
				write("����������Ѿ����գ���Ҫ���˷ѽ�Ǯ�ˣ�\n");
				return 1;
			}
			else
			{
				me->improve_skill(skill_list[i], 1500000);
				me->add("balance", -5000 * 100 * 100);
				n = 0;
				return 1;
			}
		}
		n = 1;
	}
	
	if (n > 0)
		{
                write("������ˣ�����û����Ҫѧ�ļ��ܣ�\n");
                return 1;
        }
}