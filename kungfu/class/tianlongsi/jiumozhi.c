//���浶 ���� �Ħ��
#include <ansi.h>
#define MIJI "/clone/lonely/book/liumai-shenjian"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("�Ħ��", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "��������" NOR);
        set("long",@LONG
������ѩɽ�µ����ţ��˳ƴ����������Ħ�ǡ����Է��о�����о���
��һ��������ģ�ͷ��ɮñ��
LONG
        );
        set("title","ѩɽ������");
        set("gender", "����");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);
       
		set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);
        set("combat_exp", 4000000);
        set("score", 40000);

        set_skill("force", 260);
        set_skill("xiaowuxiang", 260);
        set_skill("mizong-neigong", 260);
        set_skill("dodge", 260);
        set_skill("shenkong-xing", 260);
        set_skill("parry", 260);
        set_skill("unarmed", 260);
        set_skill("sword", 260);
        set_skill("mingwang-jian", 260);
        set_skill("hammer", 260);
        set_skill("dali-chu", 260);
        set_skill("xiangmo-chu", 260);
        set_skill("lamaism", 260);
        set_skill("literate", 260);
        set_skill("strike", 600 );
        set_skill("huoyan-dao", 260);
        set_skill("cuff", 260);
        set_skill("yujiamu-quan", 260);
        set_skill("hand", 260);
        set_skill("dashou-yin", 260);
        set_skill("martial-cognize", 260);
        set_skill("longxiang-gong", 260);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "huoyan-dao");
        map_skill("sword", "mingwang-jian");
        map_skill("strike", "huoyan-dao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hammer", "xiangmo-chu");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("cuff", "yujiamu-quan");

        create_family("����", 1, "����");
        set("class", "bonze");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                //(: perform_action, "strike.fen" :),
                //(: perform_action, "strike.yan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );
		
		set("inquiry", ([
                "����" : (: ask_me :),
                "�������" : (: ask_skill :),
        ]));
		
        setup();

        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if(me->query("can_perform/huoyan-dao/fen"))
                return "�������Ѿ�ѧ���ˣ�ʣ�µľ�Ҫ�����Լ�����ϰ�ˡ�";

        if (me->query_skill("huoyan-dao", 1) < 180)
                return "��Ļ��浶����Ϊ��������������������˵�ɣ�";
			
		if (me->query("shen") > -65000 )
                return "��Ϊ��̫������������ʱ�����ܴ��㡣";

        if(me->query("gongxian") < 600 )
                return "��Ĺ��׻�������������ʱ�����ܴ��㡣";

        message_vision(HIC "$n" HIC "����һ������·���ε���Ϯ����$N"
                       HIC "��$N" HIC "��æ���ָ񵲣���������$n"
                       HIC "���������ÿ�ν�ǰ������\n" NOR,
                       me, this_object());
        command("simle");
        tell_object(me, HIG "��ͨ���˷���İ��\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/huoyan-dao/fen", 1);
        me->add("gongxian", -600);
        return 1;
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if (me->query("can_perform/huoyan-dao/yan") )
                return "��������ʲô���Լ���ȥ������";

        if (me->query("gongxian") < 1200 )
                return "��Ĺ��׻�������������ʱ�����ܴ��㡣";

        if (me->query("shen") > -120000 )
                return "��Ϊ��̫������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 220)
                return "����ڹ���Ϊ���㣬��ѧ������һ�С�";

        if (me->query("max_neili") < 5000 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("huoyan-dao", 1) < 220)
                return "����ѻ��浶�������������ҡ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ���ȵ���������"
                     "ϸ�ˡ����������䣬ֻ��$n" HIY "�߾����еĸյ�����"
                     "���л�����̣����ƾ��ˣ����ڴ�ʱ���Ǳ��յ���Я��"
                     "������ײ��֮����Ȼ���䡣ֱ��$N" HIY "����Ŀ�ɿڴ�"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say �������˾��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������ס���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/huoyan-dao/yan", 1);
        me->add("gongxian", -1200);

        return 1;
}
int accept_object(object who, object ob)
{
        object me;
        me = this_player();

        if (base_name(ob) != MIJI)
        {
                command("say ����������ɶ��");
                return -1;
        }
		
		if (me->query_skill("huoyan-dao", 1))
		{
			command("say ���Ѿ�ûʲô�ɽ̸����ˣ�������ʲô���֣�");
            return -1;
		}
		
		if (me->query("family/family_name" == "ѩɽ��"))
		{
			me->add("skybook/tianlong/jiumozhi", 8);
			command("say ԭ������ѩɽ�ĺ󱲣�");
		}
		
		if (me->add("skybook/tianlong/jiumozhi", 1 + random(6)) < 10)
		{
			command("say ллʩ���������������ס�");
			command("heihei");
		}else
		{
			command("haha");
			tell_object(who, HIC "\n�Ħ��ͬ�⴫���㡸���浶����\n" NOR);
			me->set_skill("huoyan-dao", 10);
		}

        destruct(ob);
        return 1;
}
