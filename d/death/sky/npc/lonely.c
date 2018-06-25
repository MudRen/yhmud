#include <ansi.h>
inherit NPC;

void create()
{
        set_name("�ߴ���ʤ��", ({ "gaochu busheng han", "gaochu", "han", "lonely" }) );
        set("gender", "����" );
        set("age", 2100);
        set("long", HIC "��������̶����Ĵ�boss�����ߴ���ʤ����\n" NOR);
        set("attitude", "friendly");
        set("max_jing", 25000);
        set("max_qi", 25000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 375);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 100000000);
        //set("level", 999);

        set("inquiry", ([
                "��Ԫ��" : "��Ԫ���ҵ�ȷ�У���������������֮�ˣ�����¶һ�ָ������ơ�\n",                
        ]));
                
        set_skill("unarmed", 999);
        set_skill("sword", 999);
        set_skill("blade", 999);
        set_skill("staff", 999);
        set_skill("hammer", 999);
        set_skill("club", 999);
        set_skill("whip", 999);
        set_skill("dagger", 999);
        set_skill("throwing", 999);
        set_skill("parry", 999);
        set_skill("dodge", 999);
        set_skill("force", 999);
        set_skill("count", 999);
        set_skill("never-defeated", 999);
        set_skill("martial-cognize", 999);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.po" :),
                (: exert_function, "sword.juemie" :),
                (: exert_function, "sword.lei" :),
                (: exert_function, "sword.tianhua" :),
                (: exert_function, "sword.wanli" :),
                (: exert_function, "sword.yuce" :),
        }) );
        
        setup();

        set_temp("apply/damage", 300); 
        set_temp("apply/unarmed_damage", 300); 
        set_temp("apply/armor", 600); 
                
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();
        
        create_family("����ħ����", 1, "����֮��");
        set("title", HIR "����֮��" NOR);        
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "΢΢һЦ����$n"
                               CYN "���˵�ͷ��\n" NOR,
                               this_object(), me);
        }
}

int accept_fight(object ob)
{
        if (query_competitor() == ob)
                return 1;

        if (is_fighting())
        {
                command("say ��Ȼᣬ���Ұ���ǰ������һ�ŵ���˵��");
                return 0;
        }

        if (query("qi") < query("eff_qi") * 2 / 3
           || query("jing") < query("eff_jing") * 2 / 3
           || query("neili") < query("max_neili") * 2 / 3)
        {
                command("say �������е�ƣ�룬����Ъ�����˵��");
                return 0;
        }

        command("nod");
        command("say ��������һ��������֣������㾿����ɶˮƽ��");
        competition_with(ob);
        return 1;
}

void lost()
{
        object me, ob;

        me = query_competitor();

        ob = new("/d/death/obj/jingyuandan");
        ob->move(this_object());

        command("say ��������������Ȼ��ʤ�����ң������Ԫ������ȥ�ɡ�");
        command("give jingyuan dan to " + me->query("id"));
        me->set("SkyPass", 1);
        message_vision(HIR "ֻ��һ����������㣬����������޵\n" NOR, 
                       this_object(), me);        
        me->move("/d/death/yanluodian");
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        command("say �������ˮƽҲ�봳���ʮ�����죿��ȥ���������ɡ�");
        message_vision(HIR "ֻ��һ����������㣬����������޵\n" NOR, 
                       this_object(), me);        
        me->move("/d/death/yanluodian");
        ::win();
}

int accept_kill(object me)
{
        if (me->query("combat_exp") < 20000000)
        {
                message_vision(CYN "$N" CYN "��ŭ����������С����"
                               "ʲô�ң����ҹ�����˵��һ�ư�$n" CYN
                               "�����ڵء�\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}
