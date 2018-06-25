#include <ansi.h>
#define INVASIOND "/u/ivy/invasion/invasiond"

inherit NPC;
mixed ask_reward();

void create()
{
	set_name("��ǰ����", ({ "shi wei", "shi", "wei" }));
	set("age", 32);
	set("gender", "����");
	set("long", "��ǰ���������������Ͻ����еĺ��֣�ǧ���ȥ���ǡ�\n");
	set("attitude", "peaceful");

	set("str", 30);
	set("dex", 30);
	set("combat_exp", 100000);
	set("shen_type", 1);

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("sword", 100);
	set_skill("force", 100);
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 60);
	set_temp("apply/armor", 60);

    set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"��ǰ�����ȵ���������ͽ������֮�У�����������\n",
	}));
    set("inquiry", ([
           	"�ʹ�" : (: ask_reward :),
           	"����" : (: ask_reward :),
           	"����" : (: ask_reward :),
            "reward" : (: ask_reward :),
        ]));
	setup();
	carry_object("/d/beijing/npc/obj/sword4")->wield();
    carry_object("/d/beijing/npc/obj/guanfu1")->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && 
		(int)ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}

int accept_fight(object me)
{
	command("say ���������������ҵģ��ݵù������顣\n");
	me->apply_condition("killer", 500);
	kill_ob(me);
	return 1;
}

mixed ask_reward()

{
        object me;
        me = this_player();

        if (me->query_condition("killer")) return 1;

        if ( ! find_object(INVASIOND) || ! INVASIOND->query("record") )
           return command("say ����ް˹���������ѽ��");
        if ( ! INVASIOND->query("record/all_killed") )
           return command("say ʥ�ϲ�δ��׼�ʹͣ�����������ȥ��");
        if ( me->query("waidi/born_time") != INVASIOND->query("record/born_time"))
           return command("say ����ʹ��Ѿ������ˣ�");
        if ( environment(me) == find_object("/d/beijing/hg") )
           return command("say ������������Ͱɣ�");

        command("say ����ԭ���ǿ����˹���������ʿ��������룡");
        command("say �����������빬���ʥ�ϣ�");
        message_vision(HIW "\n$N" HIW "�󲽵��߽��ʹ���$n"
                       HIW "�������\n\n" NOR, this_object(), me);
        me->move("/d/beijing/hg");
        this_object()->move("/d/beijing/hg");
        command("say ���ˣ��Ҵ��㵽����ˣ���������ʥ�������ˡ�");
        message_vision("$NͷҲ���ص���ȥ�ˡ�\n", this_object());

        this_object()->move(query("startroom"));
        message_vision("$N���Ҵҵ����˹�����\n", this_object());
        return 1;

}

void unconcious()
{
        die();
}

/*
inherit NPC;

void create()
{
	set_name("��ǰ����", ({ "shi wei", "shi", "wei" }));
	set("age", 32);
	set("gender", "����");
	set("long", "��ǰ���������������Ͻ����еĺ��֣�ǧ���ȥ���ǡ�\n");
	set("attitude", "peaceful");

	set("str", 30);
	set("dex", 30);
	set("combat_exp", 100000);
	set("shen_type", 1);

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("sword", 100);
	set_skill("force", 100);
	set_temp("apply/attack", 100);
	set_temp("apply/defense", 100);
	set_temp("apply/damage", 60);
	set_temp("apply/armor", 60);

       set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"��ǰ�����ȵ���������ͽ������֮�У�����������\n",
	}));
	setup();
	carry_object("/d/beijing/npc/obj/sword4")->wield();
       carry_object("/d/beijing/npc/obj/guanfu1")->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && 
		(int)ob->query_condition("killer")) {
		remove_call_out("kill_ob");
		call_out("kill_ob", 1, ob);
	}
}

int accept_fight(object me)
{
	command("say ���������������ҵģ��ݵù������顣\n");
	me->apply_condition("killer", 500);
	kill_ob(me);
	return 1;
}
*/