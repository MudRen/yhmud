#include <ansi.h> 

inherit NPC;
inherit F_MASTER; 
inherit F_COAGENT;

mixed ask_skill1(); 

void create()
{
        set_name("������ɮ", ({ "wuming laoseng", "wuming" }));
        set("long",
                "����һλ�뷢���׵���ɮ�����Ŵֲ���������"
                "������������ӵ�ɮ�ˡ�\n"
        );

        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 98);
        set("shen_type", 1);
        set("str", 37);
        set("int", 42);
        set("con", 41);
        set("dex", 36);
        set("max_qi", 7000);
        set("max_jing", 3500);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 85);
        set("combat_exp", 3000000);

        set_skill("buddhism", 450);
        set_skill("literate", 300);

        set_skill("blade", 300);
        set_skill("claw", 300);
        set_skill("club", 300);
    set_skill("unarmed", 300);
    set_skill("jiasha-fumogong", 300);
        set_skill("cuff", 300);
        set_skill("dodge", 300);
        set_skill("finger", 300);
        set_skill("force", 350);
        set_skill("hand", 300);

        set_skill("parry", 300);
        set_skill("staff", 300);
        set_skill("strike", 300);
        set_skill("sword", 300);
        set_skill("whip", 300);

        set_skill("banruo-zhang", 300);
        set_skill("cibei-dao", 300);
        set_skill("damo-jian", 300);
        set_skill("luohan-fumogong", 300);
        set_skill("fengyun-shou", 300);
        set_skill("fumo-jian", 300);
        set_skill("hunyuan-yiqi", 300);
        set_skill("ruying-suixingtui", 300);

        set_skill("shaolin-xinfa", 300);
        set_skill("jingang-quan", 300);
        set_skill("longzhua-gong", 300);
        set_skill("luohan-quan", 300);
        set_skill("nianhua-zhi", 300);
        set_skill("pudu-zhang", 300);
        set_skill("qianye-shou", 300);
        set_skill("rulai-zhang", 300);
        set_skill("sanhua-zhang", 300);
        set_skill("riyue-bian", 300);
        set_skill("shaolin-shenfa", 300);
        set_skill("weituo-gun", 300);
        set_skill("wuchang-zhang", 300);
        set_skill("xiuluo-dao", 300);
        set_skill("yingzhua-gong", 300);
        set_skill("yijinjing", 350);
        set_skill("yizhi-chan", 300);
        set_skill("zui-gun", 300);
        set_skill("jingang-buhuaiti", 300);

        map_skill("blade","cibei-dao");
        map_skill("claw", "longzhua-gong");
        map_skill("club", "wuchang-zhang");
        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijinjing");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "jingang-buhuaiti");
        map_skill("staff", "weituo-gun");
        map_skill("strike", "rulai-zhang");
        map_skill("sword", "fumo-jian");
        map_skill("whip", "riyue-bian");

            prepare_skill("strike", "rulai-zhang"); 

        set("inquiry", ([ 

                "�����" : (: ask_skill1 :), 
        ])); 

        create_family("������", 0, "����ɮ��");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
        (: perform_action, "strike.zong" :),
                (: perform_action, "finger.fuxue" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 300);
        set_temp("apply/defense", 300);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 300);

        setup();

        carry_object("/d/shaolin/obj/cheng-cloth")->wear();

}

void attempt_apprentice(object ob)
{
              if (ob->query("family/family_name") == query("family/family_name"))
              {
                      command("say ����Ͳ���ͽ���ˣ�������Ҳ������"
                              "���ֵĵ��ӣ��ʹ���һЩ��ɮ�Ĵ�ǳ����ɣ�"
                              "�Ҿͽ�����Ӱ������(ruying-suixingtui)��ǧ��������(rulai-zhang)�ɣ�");
              } else 
                      command("say ��ֻ�����ֵ�һ��ɨ��ɮ�����ﶮʲô�书��");
}


int recognize_apprentice(object ob, string skill) 
{
        if (ob->query("family/family_name") != "������") 
        {
                command("hmm"); 
                command("say �������������ԨԴ����̸���ڶ��֣�\n"); 
                return -1; 
        }


        if ((int)ob->query("shen") < 50000) 
        {
                command("hmm"); 
                command("say �������������ն�����Ϊ���������ƺ����Ļ�������"); 
                return -1; 
        } 

        if (skill != "strike" && skill != "rulai-zhang" && 
        skill != "unarmed" && skill != "ruying-suixingtui") 
        {
                command("shake"); 
                command("say ��ֻ������һЩȭ�ź��Ʒ��Ĺ���������������ʦ��ѧ�ɡ�"); 
                return -1; 
        }

        if (skill == "strike" && ob->query_skill("strike", 1) > 179) 
        {
                command("say ����Ʒ������Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�"); 
                return -1; 
        }

        if (skill == "unarmed" && ob->query_skill("unarmed", 1) > 179) 
        {
                command("say ���ȭ�Ź����Ѿ���ͬ�����ˣ�ʣ�¾��Լ�ȥ���ɡ�"); 
                return -1; 
        }

        if (! ob->query_temp("can_learn/wuming")) 
        { 
                command("say ���¼�Ȼ�Ѿ��ݴ�Ħ��ʦ��������ǵõ���ɮ��"); 
                command("say ����Ӱ�����ȡ�ǧ����������������ֺ���书���ʹ�������ˡ�"); 
                command("say ���������һ�����Ĺ��ľ��У���֪������ѧ����"); 
                ob->set_temp("can_learn/wuming", 1); 
        } 
        return 1; 
}

mixed ask_skill1() 
{
        object me; 

        me = this_player(); 
        if (me->query("can_perform/rulai-zhang/zong")) 
                return "���Ѿ�ѧ���˴��У��������Ŀ�������Ц��"; 

        if (me->query("family/family_name") != "������" ) 
                return "�������������ԨԴ����֪�����⻰�Ӻζ�����"; 

        if (me->query_skill("rulai-zhang", 1) < 1) 
                return "����ǧ�������ƶ�ûѧ����̸ʲô���п��ԣ�"; 

        if (me->query("gongxian") < 800) 
                return "�ţ�����������ûʲô��Ϊ�������Ҳ����㡣"; 

        if (me->query("shen") < 150000) 
                return "�������������ò����������Ҳ��ܴ��㡣"; 

        if (me->query_skill("force") < 350) 
                return "����ڹ�����㣬�ò�����һ�У�"; 

        if (me->query_skill("rulai-zhang", 1) < 220) 
                return "��ǧ����������δ�����þ���������ô��С�"; 

        message_vision(HIY "$n" HIY "��$N" HIY "Ц��Ц���漴˫�����" 
                       "����һ�ƻ����\n�����Ƶ���;��ͻȻ����" 
                       "��һ�ƻ�Ϊ���ƣ����ƻ�Ϊ\n���ƣ��̶���Ϊ" 
                       "���ƣ����ƻ�ʮ���ƣ�����ǵ�����\n�޾���" 
                       "ֻ����$N" HIY "Ŀ�ɿڴ���\n" NOR, 
                       me, this_object()); 
        command("nod"); 
        command("say ��ɿ������ˣ�"); 
        tell_object(me, HIC "��ѧ���ˡ�����ڡ���\n" NOR); 

        if (me->can_improve_skill("strike")) 
                me->improve_skill("strike", 1500000); 
        if (me->can_improve_skill("rulai-zhang")) 
                me->improve_skill("rulai-zhang", 1500000); 
        me->improve_skill("martial-cognize", 1500000); 
        me->set("can_perform/rulai-zhang/zong", 1); 
        me->add("gongxian", -800); 
        return 1; 
}

int accept_ask(object me, string topic)  
{
        switch (topic)  
        {
        case "��Ӱ����" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/ruying-suixingtui/ruying",  
                           "name"    : "��Ӱ����",  
                           "sk1"     : "ruying-suixingtui",  
                           "lv1"     : 160,  
                           "force"   : 250,  
                           "neili"   : 2000,  
                           "gongxian": 800,  
                           "shen"    : 30000, ]));  
                break;
                
        case "��������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/jiasha-fumogong/zhe",  
                           "name"    : "��������",  
                           "sk1"     : "jiasha-fumogong",  
                           "lv1"     : 180,  
                           "force"   : 300,  
                           "neili"   : 3500,  
                           "gongxian": 1000,  
                           "shen"    : 70000, ]));  
                break;  

        default:  
                return 0;  
        }
}

