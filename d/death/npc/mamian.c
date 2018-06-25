#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "ma mian", "ma", "mian" }) );
        set("title", HIR "ڤ���ز�����ǰ" NOR);
        set("nickname", HIY "���" NOR + HIW "����" NOR);
        set("gender", "����");
        set("age", 623);
        set("long", @LONG
һ���ߴ�������������Ĺ���������ܲ����ǡ�
LONG );
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("per", 35);

        set("max_qi", 7000);
        set("max_jing", 5000);
        set("max_neili", 9000);
        set("neili", 9000);
        set("jiali", 250);
        set("combat_exp", 8000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

         set_skill("unarmed", 450);
        set_skill("sword", 450);
        set_skill("blade", 450);
        set_skill("staff", 450);
        set_skill("hammer", 450);
        set_skill("club", 450);
        set_skill("whip", 450);
        set_skill("dagger", 450);
	set_skill("throwing", 450);
        set_skill("parry", 450);
        set_skill("dodge", 450);
        set_skill("force", 450);
        set_skill("count", 450);
        set_skill("never-defeated", 450);
        set_skill("martial-cognize", 450);

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

        prepare_skill("blade", "never-defeated");
        
        setup();

        carry_object(__DIR__"obj/armor1")->wear();
        carry_object(__DIR__"obj/armor2")->wear();
        carry_object(__DIR__"obj/blade1")->wield();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIR "$N" HIR "��ŭ��һ�����ȣ����"
                       "��ʱ��������ԩ�꣬һ�����ް�����\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        return 1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}
