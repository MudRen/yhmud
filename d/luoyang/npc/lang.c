#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("�˷���", ({ "lang fangyun", "lang", "fangyun" }));
        set("title", HIC "������" NOR);
        set("nickname", HIY "����������" NOR);        
        set("long", @LONG
����һλ���صĽ������ϣ�û����֪������������Ҳû��֪
�����Ĺ�ȥ�������ٲ�������ȥ��Ӱ��ֻ�������Ų��£���
ִ���������ϱ���һ���ƺ�«���������磬��ɫ����ʮ��֮
�㲺���꣬˫Ŀ������ؿ��ų��ա�
LONG);
        set("gender", "����");
        set("age", 36);        
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 5000);
        set("max_jing", 4000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 3500000);
        set("score", 800000);

        set_skill("force", 300);
        set_skill("duanshi-xinfa", 300);
        set_skill("dodge", 300);
        set_skill("tiannan-bu", 300);
        set_skill("cuff", 300);
        set_skill("jinyu-quan", 300);
        set_skill("strike", 300);
        set_skill("wuluo-zhang", 300);
        set_skill("sword", 300);
        set_skill("duanjia-jian", 300);
        set_skill("parry", 300);
        set_skill("literate", 300);
        set_skill("martial-cognize", 300);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "duanjia-jian");
        map_skill("sword", "duanjia-jian");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");        

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: perform_action, "sword.jing" :),
                (: perform_action, "sword.lian" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),                           
        }));
        
        set("chat_chance", 120);
        set("chat_msg", ({
                CYN "�˷��������˵��: ������֪�������ڹ��ÿɺã����ˣ�����......\n" NOR,                
                (: random_move :)
        }) );
        
        setup();        
        carry_object("/d/mingjiao/obj/baipao")->wear();
        carry_object("/clone/weapon/changjian")->wield();   
        if (random(4) == 1)
                set_temp("jinzhong", carry_object("/clone/lonely/book/zhaobook")); 
}


