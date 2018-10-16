// dizangwang

#include <ansi.h>
#define QILIN_XUE    "/d/death/obj/qilinxue"

inherit NPC;

mixed ask_xue();
mixed ask_zhuan();

void create()
{
        set_name("�ز���", ({ "dizang", }));
        set("long", "����ò���ϣ�����һ�����ۣ��������ƹ��˼����������ɡ�\n");
        set("gender", "����");
        set("age", 99);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 18);
        set("attitude", "peaceful");
        set("str", 31);
        set("int", 39);
        set("con", 34);
        set("dex", 36);

        set("max_qi", 49999);
        set("max_jing", 29999);
        set("neili", 49999);
        set("max_neili", 49999);
        set("jiali", 400);

        set("combat_exp", 50000000);
                
        set_skill("unarmed", 800);
        set_skill("finger", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);
        set_skill("force", 800);
        set_skill("sword", 800);
        set_skill("count", 800);
        set_skill("kuihua-mogong", 800);
        set_skill("martial-cognize", 800);
        set_skill("literate", 220);

        map_skill("parry", "kuihua-mogong");
        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("finger", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");

        prepare_skill("finger", "kuihua-mogong");     
           
        set("inquiry", ([
                "����ѥ" : (: ask_xue :),
                "ת��"   : (: ask_zhuan :),                
        ]));
        
        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/misc/spin")->wield();
                
        create_family("ڤ���ز�����ǰ", 1, "��ڤ֮��");
        set("title", HIR "��ڤ֮��" NOR);
}

int attempt_apprentice(object ob)
{
        if (! ob->query("born"))
        {
                command("say ���Ͷ̥ȥ��������Ϲ����ʲô��");
                return 0;
        }

        command("say ��������һ�߶�ȥ��");
}

mixed ask_xue()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if (! me->query("hell_quest/������"))
                return "����ѥ���ҵı�����������ʲô��";

        ob = find_object(QILIN_XUE);
        if (! ob) ob = load_object(QILIN_XUE);
	owner = environment(ob);
        while (owner)
	{
                if (owner->is_character() || ! environment(owner))
                        break;
		owner = environment(owner);
	}

        if (owner == me)
                return "����ѥ�������������ô����ô�����������أ�";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "���Ѿ�������ѥ���ȥ�ˡ�";

                        return "����ѥ��������" + owner->query("name") +
                               "���У���ȥ�����һ����ɡ�";
        }

        ob->move(this_object());
        message_vision("$N���ͷ�������ã���Ȼ����Ϊ���Ϸ��������֮�£��Ϸ�ͽ����ɣ���\n", 
                       this_object(), me);
        command("give boots to " + me->query("id"));
        return 1;
}

mixed ask_zhuan()
{
        object who;
        
        who = this_player();
        /*
        if ((int)who->query("combat_exp") < 800000000 || 
            ! ultrap(who)) 
        {
                message_vision("$N��$nһ���֣��������鲻�������ܲ��죬ǿ��������Ȼ��\n", 
                               this_object(), who);
                return 1;
        }
        
        if (! who->query("animaout")) 
        {
                message_vision("$N��$nһ���֣������㻹û�д�ͨ�����������ء�\n", 
                               this_object(), who);
                return 1;
        }
        */
        if (! who->query("HellZhenPass"))
        {
                message_vision("$N��$nһ���֣���������ת���ȹ���ʮ�˲������һ����˵��\n", 
                               this_object(), who);
                return 1;
        }
        
        if (who->query("SkyPass"))
        {
                message_vision("$N��$nһ���֣�������Ԫ����ȡ������ȡ���˾Ϳ���ң�\n", 
                               this_object(), who);
                return 1;
        }
     
        message_vision("$N��$n������Ц�˼�����˵��������·�㲻�ߣ����������㴳������\n",
                       this_object(), who);         

        message("channel:rumor", HIB "�����ܵظ���" + who->query("name") +
                "Ҫ����ڤ�ظ��������һ�أ��ߣ�������ʬ�ɣ�\n" NOR, users());                                          
        
        environment(this_object())->set("no_fight", 0);
        competition_with(who);
        this_object()->fight_ob(who);
        who->fight_ob(this_object());
        
        return 1;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIB "$N" HIR "һ�����ȣ����"
                       "��ʱ��������ԩ�꣬һ�����ް�����\n" NOR, this_object(), ob);

        ::fight_ob(ob);
}

void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(HIB "$N���˿�$n���ٺ�Ц��������֪����򲻰�����ζ��ʲô��"
                       "����ζ��������������������\n" NOR,
                       this_object(), ob);
                       
        call_out("ob_die", 1, ob);  
        environment(this_object())->set("no_fight", 1); 
        ::win();
}

void ob_die(object me)
{
        me->set_temp("die_reason", "���ز��������ɱ����");
        me->die();       
}

void lost()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(HIB "$N��ѽһ������$nŭ���������������ң��´ο�û����ô�����ˣ���\n" NOR,
                       this_object(), ob);
        message_sort(HIB "$N˵��ӻ����ͳ����������ó��йٱ������湴��һ�ᣬ��϶�$n˵����"
                     "��ת����������ػ�����������ý���ʮ�����콫��Ԫ��ȡ�����ҷ��ܰ�"
                     "���ת��֮�ţ�ʮ���������ɭ�ϣ��Ϸ�ֻ�����㵽���ţ�������·��"
                     "���Լ����ˣ�\n" NOR, this_object(), ob);
        ob->set("DiZangPass", 1);
        ob->move("/d/death/sky/tianmen");
        environment(this_object())->set("no_fight", 1);
        message("channel:rumor", HIB "�����ܵظ�����ϲ" + ob->query("name") +
                "������ڤ�ظ����飬�������ʮ�����죡\n" NOR, users());             
                
        ::lost();
}

int accept_kill(object ob)
{
        return 0;
}

int accept_hit(object ob)
{
        return 0;
}

int accept_object(object me, object ob)
{
       //object obn;

        if ( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("��û�����������\n");

        if ( (string)ob->query("id") != "jingyuan dan" )
        {
                message_vision(CYN "�ز���ҡ��ҡͷ����������������ʲô��\n" NOR, me);
                return 0;
        }

        if (! me->query("SkyPass") || ! me->query("DiZangPass"))
        {
                message_vision(CYN "�ز��������޹�����»������㻹���Լ����Űɡ�\n"
                               NOR, me);
                return 0;
        }
        
        message_vision(CYN "�ز��������ܺúܺã�û���뵽����ʮ��������һ��Ҳ���ˣ��������⡣\n"
                       "�Ϸ�Ҳֻ��˳��������ˣ�ȥ�ɡ�\n"
                       NOR, me);
                       
        message_vision(CYN "�ز�������һ�У�ͻȻ����һ�����磬��Ԫ����ס���Ԫ�������������ֻء�\n"
                       NOR, me);

        message("channel:rumor", HIB "�����ܵظ�����ϲ" + me->query("name") +
                "�������ʮ�����죬���������ֻ�ʱ�գ����⣿��Ϊ��������\n" NOR, users());                             
              
        destruct(ob);
        
        me->move("/d/death/liudaolunhui/tiandao");
        me->move("/d/death/liudaolunhui/diyudao");
        me->move("/d/death/liudaolunhui/rendao");
        me->move("/d/death/liudaolunhui/eguidao");
        me->move("/d/death/liudaolunhui/chushengdao");
        me->move("/d/death/liudaolunhui/xiuluodao");
        me->move("/d/death/liudaolunhui/wujiandao");
        
        return 1;
}
