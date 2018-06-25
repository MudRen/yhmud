//yanruyu.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("������", ({ "yan ruyu", "yan", "ruyu" }) );
        set("gender", "Ů��" );
        set("title",HIM "��һЦ��ǡ�" NOR);
        set("age", 23);
        set("long", 
        "����������֮ò����ɫ���������޾��ף������˼����ӣ�\n");
    
        set("str", 30);
        set("dex", 40);
        set("con", 30);
        set("int", 40);
        set("per", 40);
        
        set_skill("literate", 300);
        set_skill("yangyan-shu", 300);
        set_skill("force", 150);
        set_skill("yunv-xinjing", 150);
        set_skill("dodge", 150);
        set_skill("rouyun-steps", 150);
        set_skill("unarmed", 150);
        set_skill("parry", 150);
        set_skill("meinv-quan", 150);

        map_skill("force", "yunv-xinjing");
        map_skill("dodge", "rouyun-steps");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");

        prepare_skill("unarmed", "meinv-quan");

        set("combat_exp", 3000000);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("qi", 1000);
        set("jing", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("attitude", "friendly");

        set("inquiry", ([
                "������" : "����֮�ģ��˽���֮����ѧ��������(yangyan-shu)�ɡ�",
                "ѧ��" : "ѧ������Ҫ������ʮ��������Խ��ѧʱԽ����",
        ]) );

        setup();
        set("chat_chance", 5);
        set("chat_msg", ({
                "������˵��������֮�ģ��˽���֮��\n",
                "������˵��������ѧ��������֮���ɣ���������ڵ��ⶼ��Ư����\n",
                "����������˵��������һЦ��������������������ɫ��\n",
                "������˵�����������ѻ����ݣ�����ָ��¶��Ũ������Ⱥ��ɽͷ����������̨���·ꡣ\n",
        }) );

        carry_object("/d/changan/npc/obj/skirt")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment())
                return;

        command("look " + me->query("id"));

        if (me->query("per") < 20)
        {
                command("say ��������λ" + RANK_D->query_respect(me) +
                        "Ҫѧ����������ѧ�Ѻܱ���Ŷ��");
        }
}

int recognize_apprentice(object me, string skill)
{
        if (me->query("per") >= 30)
        {
                command("say ��ѧ��ȥ�����Ҫ���˼��ʵ�׷�ſ��ˣ�");
                return -1;
        }

        if (skill != "yangyan-shu")
        {
                command("say ��ֻ������������֮����");
                return -1;
        }

        if (! (int)me->query_temp("mark/��"))
                return 0;
        me->add_temp("mark/��", -1);
        return 1;
}

int accept_object(object who, object ob)
{
        if (!(int)who->query_temp("mark/��"))
                who->set_temp("mark/��", 0);

        if (ob->query("money_id") && ob->value() >= 2000)
        {
                message_vision("������ͬ�⴫��$NһЩ��������(yangyan-shu)�ľ��顣\n", who);
                who->add_temp("mark/��", ob->value() / 100);
                destruct(ob);
                return 1;
        }

        command("say ѧ������Ҫ��ʮ������������~");
        return 0;
}
