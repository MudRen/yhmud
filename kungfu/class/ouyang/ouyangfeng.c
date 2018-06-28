// ouyangfeng.c

#include <ansi.h>
#include "ouyang.h"

#define LINGSHE_ZHANG    "/d/baituo/obj/lingshezhang"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;


mixed ask_music_book();
mixed ask_zhang();
mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();

void create()
{
	set_name("ŷ����", ({ "ouyang feng", "ouyang", "feng" }));
	set("long", "�����ǰ���ɽׯ�����ųơ���������ŷ���档����������\n"
		    "�����⺷����Ȼ�ܵ�������ƭ��ѧϰ�ˡ������澭������\n"
                    "����ħ��һ�ȱ�þ�����ң�����������Ȼ�ָ���������\n"
                    "ʤ������\n");
	set("title", "����ɽׯ��");
	set("gender", "����");
	set("age", 53);
	set("nickname", HIR "����" NOR);
	set("shen_type",-1);
	set("attitude", "peaceful");

	set("str", 32);
	set("int", 34);
	set("con", 34);
	set("dex", 32);

	set("qi", 6000);
	set("max_qi", 6000);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 7300);
	set("max_neili", 7300);
	set("jiali", 120);

	set("combat_exp", 2500000);

	set_skill("force", 350);
	set_skill("strike", 350);
	set_skill("dodge", 350);
	set_skill("parry", 350);
	set_skill("cuff", 350);
  set_skill("finger", 350);
	set_skill("staff", 350);
	set_skill("training", 400);
  set_skill("poison", 400);
  set_skill("shedu-qiqiao", 350);
	set_skill("hamagong", 350);
	set_skill("baituo-xinfa", 350);
	set_skill("chanchu-bufa", 350);
	set_skill("lingshe-quan", 350);
	set_skill("lingshe-zhangfa", 350);
	set_skill("baibian-daxue", 350);
  set_skill("guzheng-jifa", 400);
  set_skill("xiyu-tiezheng", 400);
  set_skill("wushe-qu", 400);
  set_skill("literate", 300);
	set_skill("medical", 350);
	set_skill("baituo-michuan", 350);

	map_skill("force", "hamagong");
	map_skill("dodge", "chanchu-bufa");
	map_skill("strike", "hamagong");
	map_skill("cuff",  "lingshe-quan");
	map_skill("parry", "lingshe-zhangfa");
	map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

	create_family("ŷ������", 5, "����");
        set("chat_chance", 2);
        set("chat_msg",({
                "ŷ���������������������ŷ���ϲ����ذԽ����ء�\n",
                "ŷ��������Ҷ�ŷ���˱��ܹ������Ҽ��۷磡\n",
                "ŷ������������ն����������ģ�\n",
        }));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "staff.chan" :),
		(: perform_action, "staff.qianshe" :),
		(: perform_action, "staff.wuji" :),
		(: perform_action, "strike.zhen" :),
		(: perform_action, "cuff.rou" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

        set("inquiry", ([              
		            "����"   : (: ask_music_book :),
		            "���ݼ���": (: ask_music_book :),
		            "������" : (: ask_zhang :),
		            "�����޼�": (: ask_skill1 :),
		            "ǧ�߳���": (: ask_skill2 :),
                "ǧ������": (: ask_skill3 :),
        ]));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

	set("music_book", 1);

	setup();
	carry_object("/d/baituo/obj/shezhang")->wield();
	carry_object("/clone/misc/cloth")->wear();
        carry_object("d/baituo/obj/tiezheng");
	add_money("silver", 50);
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "guzheng-jifa")
                return 0;

        if (me->query_temp("can_learn/ouyang/guzheng-jifa"))
                return 1;

        command("say �ðɣ���Ը��ѧ�Ҿʹ���һ�����֮����");
        me->set_temp("can_learn/ouyang/guzheng-jifa", 1);
        return 1;
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))
                return;

        if((int)ob->query("combat_exp") < 200000)
        {
                if (random(2))
                        command("smile");
                else
                        command("pat " + ob->query("id"));

                command("say ��ľ��黹�������Ⱥ��ҵ�ֶ��ŷ����ѧϰ�书�ɡ�");
	        return ;
        }

        command("sigh");
        command("pat " + ob->query("id"));
        command("recruit " + ob->query("id"));
        message_vision("ŷ���������������ŷ�������Ǻ�����˰���\n",
                       this_object());
        return;
}

mixed ask_skill1()
{
        object me; 
        me = this_player(); 

        if (me->query("can_perform/lingshe-zhangfa/wuji")) 
                return "�㻹����ȥ����ȥ���úð�����ŷ���ҷ�����"; 

        if (me->query("family/family_name") != query("family/family_name"))   
                return ("������ҰС�Ӹ���������Ұ��\n");
                
        if (me->query("gongxian") < 500)
                return "��Ϊ��ŷ����Ч�����������������Ȳ�æ���㡣";

        if (me->query_skill("lingshe-zhangfa", 1) < 100) 
                return ("����ȷ��������ң�ѧ���ˡ������޼ɡ���\n"); 

        command("say �ðɣ��㿴���ˡ�");  
        tell_object(me, HIR"ŷ���彫�������޼ɡ�������һ�飬������ĬĬ���ǣ����о�̾���ѡ�\n"NOR);  
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/lingshe-zhangfa/wuji", 1);
        me->add("gongxian",-500);
        return 1;   
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if (me->query("can_perform/lingshe-zhangfa/qianshe"))
                return "�㻹����ȥ����ȥ���úð�����ŷ���ҷ�����";

        if (me->query("family/family_name") != query("family/family_name"))
                return "�����Ķ����ģ�����ô��";

        if (me->query("shen") > -40000)
                return "�������ֶβ����ݶ��������ڻ����ܴ�����У�";
                
                if (me->query("gongxian") < 800)
                return "��Ϊ��ŷ����Ч�����������������Ȳ�æ���㡣";

        if (me->query_skill("lingshe-zhangfa", 1) < 120)
                return "���Ⱥúð������ȷ���������˵��";

        message_vision(HIY "$n" HIY "�ȵ�������ϸ�ˣ�˵�ѵ�"
                       "�ۺ�ɨ�����������������Ǳ�������$N"
                       HIY "���۾�����ֱ�ˡ�\n" NOR,
                       me, this_object());
        command("heihei");
        command("say ����ʾ����ô������㿴����û�У�");
        tell_object(me, HIG "��ѧ����ǧ�߳�����\n" NOR);
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/lingshe-zhangfa/qianshe", 1);
        me->add("gongxian",-800);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();
        if (me->query("can_perform/lingshe-zhangfa/wanshi"))
                return "�Լ��úö���ϰ�ɣ�";

        if (me->query("family/family_name") != query("family/family_name"))
                return RANK_D->query_respect(me) + "��������ŷ�����ҵ��ˣ��γ����ԣ�";

        if (me->query("shen") > -120000)
                return "�����»������ݶ���ѧ�������С�ǧ�����ɡ���";
                
                if (me->query("gongxian") < 1000)
                return "��Ϊ��ŷ����Ч�����������������Ȳ�æ���㡣";

        if (me->query_skill("lingshe-zhangfa", 1) < 180)
                return "��������ȷ��������ң�Ҫ��������";

        message_vision(HIY "$n" HIY "΢΢��ף����ּ���һ��ľ������$N"
                       HIY "$N" HIY "�����л�����ֻ����������һ��\n"
                       "��Ȼ$p" HIY "����һ�䣬ľ�������벻���ĽǶȹ�"
                       "����$P" HIY "���һ�������Ҳ�����\n" NOR,
                       me, this_object());
        command("smile");
        command("say ��������ˣ�");
        tell_object(me, HIG "��ѧ����ǧ�����ɡ�\n" NOR);
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("staff")) 
                me->improve_skill("staff", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        if (me->can_improve_skill("lingshe-zhangfa")) 
                me->improve_skill("lingshe-zhangfa", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/lingshe-zhangfa/wanshi", 1);
        me->add("gongxian",1000);
        return 1;
}

mixed ask_music_book()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "�ҵ������Ѿ����ȥ�ˡ�\n";

        ob = new("/clone/book/zhengpu");
        ob->move(me, 1);
        message_vision("$n�����׸���$N����������ȥ�Լ��ú���ĥ�ɡ�\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

mixed ask_zhang()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_good())
        {
                if (me->query("family/family_name") == "ŷ������")
                        message_vision("$N��ŭ����$n����������Ϊ���ҵ��ӣ�"
                                       "����ȥѧʲô���壬���������ת����\n",
                                       this_object(), me);
                else
                        message_vision("$N��ŭ����$n�ȵ�������һ����С�ӣ�"
                                       "��Ȼ�ҿ��������ȣ���\n",
                                       this_object(), me);
                return 1;
        }

        if (me->query("family/family_name") != "ŷ������")
                return "������������ŷ���ҵı�����������ʲô��";

        if (me->query("family/master_id") != query("id"))
                return "ֻ���ҵĵ��Ӳ����������ȣ��㻹����ذɡ�";

        if (me->query("shen") > -60000)
                return "�㻹�����ĺ��������Ҳ��ܰ������Ƚ����㡣";

        ob = find_object(LINGSHE_ZHANG);
        if (! ob) ob = load_object(LINGSHE_ZHANG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "�����Ȳ������������ô����ô�����������أ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���Ѿ��������Ƚ��ȥ�ˡ�";

                if (owner->query("family/master_id") == query("id"))
                        return "������������" + owner->query("name") +
                               "���У���Ҫ���þ�ȥ�����ɡ�";
                else
                        return "��������������" + owner->query("name") +
                               "���У���ȥ�����һ����ɡ�";
        }

        ob->move(this_object());
        message_vision("$N���ͷ�������ã��������������ȥ�Ը���Щ����"
                       "��ʿ�ɣ���\n", this_object(), me);
        command("give lingshe zhang to " + me->query("id"));
        //ob->start_borrowing();
        return 1;
}

void reset()
{
        set("music_book", 1);
}

void unconcious()
{
        die();
}
