// Modified by Lonely

#include <ansi.h>
inherit NPC;

mixed ask_quest();
mixed ask_zhuan();

int check_status(object who);
int failed(object who);
int remove_all();
int winning(object who);
int message_ob(object who);
int round_1(object who);
int round_2(object who);
int round_3(object who);
int round_4(object who);
int round_5(object who);
int round_6(object who);
int round_7(object who);
int round_8(object who);
int round_9(object who);
int round_10(object who);
int round_11(object who);
int round_12(object who);
int round_13(object who);
int round_14(object who);
int round_15(object who);
int round_16(object who);
int round_17(object who);
int round_18(object who);

void create()
{
        set_name("ʮ������", ({ "shidian yanluo", "shidian", "yanluo", "shi", "yan"}));
        set("long", "һλ������ף��������룬�����۵Ĵ󺺡�\n"
                    "����������ʮ�����ޡ�\n");
        set("title", HIR "ڤ���ز�����ǰ" NOR);
        set("nickname", HIY "��˾�ܹ�" NOR);
        set("gender", "����");
        set("age", 3000);
        set("attitude", "friendly");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jiali", 800);

        set("combat_exp", 100000000);

        set_skill("unarmed", 999);
        set_skill("finger", 999);
        set_skill("claw", 999);
        set_skill("strike", 999);
        set_skill("hand", 999);
        set_skill("cuff", 999);
        set_skill("parry", 999);
        set_skill("dodge", 999);
        set_skill("force", 999);
        set_skill("jiuyin-shengong", 999);
        set_skill("magic", 999);
        set_skill("literate", 999);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "ʮ�����������̾�˿�����\n" NOR,
                CYN "ʮ������̾��������׿Ǻ���ȸ��ë���õ㣬�����������Ͱ׻�����Ū������\n" NOR,
                CYN "ʮ������̾������ס������������л��ǣ�������Ѱ찡��\n" NOR,
                CYN "ʮ������̾�������޾�Ҫ���ˣ��ز��ϴ�Ҫ�����Ƶ�������ԭ�ϻ�û���룬�������Ǻð���\n" NOR,
                CYN "ʮ������̾�����ز��ϴ�����������Ҫ������\n" NOR,
                CYN "ʮ�����ޱ�Թ����ƽ���޹ʵ�Ҫʲô���������ϴ�Ҳ���ǵġ�\n" NOR,
        }));

        set("inquiry", ([
                "������"   : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "ԭ��"     : (: ask_quest :),
                "ҩ��"     : (: ask_quest :),
                "ת��"     : (: ask_zhuan :),
                "name"     : "�ߣ����Ϸ򶼲��ϵã������ǻ��̫���ˣ�\n",
                "here"     : "��������޵ظ���������һ̸���ٺ٣�û�˲��£�\n",
                "����"     : "�������ף��벻����ʧ�����ˣ�\n",           
                "�ز���"   : "����������ϴ�û���ǵ�������",
                "����"     : "�����������������ĵ������˳��˿���ƽ����������Ҳ����Ҫһ����������",
                "������"   : "�����������������ĵ������˳��˿���ƽ����������Ҳ����Ҫһ����������",
                "����"     : "������Ҫһ���׻��Ĺ�ͷ��������������ô������ô��",
                "�׻���"   : "������Ҫһ���׻��Ĺ�ͷ��������������ô������ô��",
                "��ȸ��ë" : "�Ƕ���������ûʲô�õģ���ȴ����������������ԭ�ϡ�",
                "����"     : "�Ƕ���������ûʲô�õģ���ȴ����������������ԭ�ϡ�",
                "����׿�" : "�ǿ����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "���"     : "����׿����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "�׿�"     : "����׿����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "����"     : "����������ʱ����ڱ�ˮ��̶��û��������ȥ׽ʱȴû������",
                "��ˮ��̶" : "��ˮ��̶�����κ������棬��վ�������������͵��ˣ���������ȥ��ô��ϡ�����Ѫ������",
                "����Ѫ��" : "�ⶫ�������ڵظ��ֻ�˾��Ѱ�ҵ������š�Ҫ���ǡ�������Ե����",
                "�׻�"     : "�Ǵ�����Ϣ�ڼ���˾����ĺ�ɭ��������˺ü�������ȥ׽�������ȫ�����ˡ�",
                "��ɭ��"   : "��ɭ����ȫ�����������С�ָ�ϳ�����Ҫ������û�����Ϸ���",
                "ָ�ϳ�"   : "���ǻƵ����������ķ���֮һ���������䵽�����������û������",
                "����˾"   : "����˾�������޵�Ķ��ߡ�",
                "�ֻ�˾"   : "�ֻ�˾�������޵�Ķ��ߡ�",
                "���޵�"   : "�����Ҳ���ң����Ǳ����İ���",
                "��ȸ"     : "��������������������������ȸ��������˵�Ǳ�ë���������ޱ�֮�أ�ҪѰ�����ϱ���Ҫ���б��",
                "����"     : "�ظ��и���ʯ��Ի����ɫ��󡹣����Ǹ����ö���ı��",
                "��ɫ���" : "�����ţ��ⶫ���������������ع��������",
                "�ع���"   : "������һ����Ҳ������ʮ��֮һ��",
                "������"   : "�������ߵ����������ǵظ�����ߵĽ�����ƽʱ�����濴�ء�",
                "����"     : "�Ϳ����κ��ŵ�ţͷһ�����ǵظ���������",
                "����"     : "�ǳ��ڹ��������Ѫ�ص�����������⣬��ôŪ����������",
                "������"   : "�Ҳ٣������Ҳ���ң���ȥ������ԳԿ���֪���ˡ�",
                "Ѫ�ص���" : "Ѫ�ص����������޵�ı��ߣ���Ҫ��ȥ����ô��ϡ�����ѥ����",
                "����ѥ"   : "���ǵز����Ķ�������Ҳֻ�Ƽ���һ�Ρ�",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.zhi" :),
                (: perform_action, "strike.zhang" :),
                (: perform_action, "cuff.quan" :),
                (: perform_action, "hand.shou" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
        }) );

        set("count", 1);
        create_family("��˾", 0, "�ܹ�");

        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

mixed ask_quest()
{
        //object ob;
        object me;
        me = this_player();

        if (me->query_temp("to_answer")) 
                return "��������ô��ô���£����׸ɻ��ǲ��ɰ���";

        if (me->query("over_quest/hell_quest/������"))
                return "�ϴε��������Ƕ�лл���ˡ�";

        if (me->query("hell_quest/������"))
                return "��Ҫ��ԭ���㶼����������������ô��ô���£�";

        if ( ! me->is_ghost() && ! wizardp(me))
                return "�ף�������ô���������ˣ�";

        if (query("over") > 1)
                return "�����Ҷ��Ѿ�׼�����ˣ�����Ҫ��İ�æ�ˡ�";

        if (query("count") < 1)
                return "���ˣ����Ѿ�������ȥ�ˡ�";

        if (me->query("combat_exp") < 10000000)
                return "����������������̫���ˣ��ǰﲻ���ҵġ�";

        message_vision(HIC "\nʮ��������ϸ�Ĵ�����$N" HIC "��һ��\n" NOR, me);
        command("say ��������");
        command("whisper " + me->query("id") + " ���Ǹմ��������İɣ�����������ƺ�"
                "�书�������ܹ����Ҹ�æ�𣿵ز�\n�������ڽ�����Ϊ��������������������"
                "��������ǧ����������Ѿ�׼�����ˣ������в����������ǡ���\n��������"
                "������ҩ�������ܰ���ȥŪ���³�֮����Ȼ����ĺô���");

        remove_call_out("answer");
        call_out("answer", 2, me);
        me->set_temp("to_answer", 1);
        add_action("do_accept", "accept");
        return 1;
}

void answer(object me)
{
        tell_object(me, HIR "\n��Ը�����(accept)ʮ�����޵�������\n" NOR);
}

int do_accept()
{
        object me = this_player();
        if (me->query_temp("to_answer")) 
        {
                tell_object(me, HIR "\n���������ʮ������Ѱ����������"
                                "����ԭ�ϡ�\n" NOR);
                message_vision( CYN "\nʮ�����ޡ�����������Ц������\n"
                                NOR, me);
                message_vision( CYN "ʮ�����޶�$N" CYN "˵�������Ϸ��"
                                "��лл���ˡ�\n"NOR, me);
                me->set("hell_quest/������", 1);
                me->set("wang_get/����", 1);
                me->set("wang_get/����", 1);
                me->set("wang_get/��Ƥ", 1);
                me->set("wang_get/����", 1);
                me->set("wang_get/���", 1);
                me->delete_temp("to_answer", 1);
                remove_call_out("give_gold");
                call_out("give_gold", 2, me);
                add("count", -1);
        }
        return 1;
}

int give_gold(object me)
{
        message_vision(HIW "\nʮ����������һ�ӣ���ʱ���һ��ѽ��ӣ���"
                       "��$N" HIW "��\n"NOR, me);
        message_vision(CYN "ʮ������˵����������������������ٻ�����"
                       "��������Ļƽ��㹻�㹺����ߡ�\n"NOR, me);
        tell_object(me, HIC "\n������һǧ��" NOR + YEL "�ƽ�" NOR + 
                        HIC "��\n" NOR);
        MONEY_D->pay_player(me, 10000000);
        return 1;
}

int accept_object(object me, object ob)
{
        object obn;

        int exp, pot, mp;

        exp = 150000 + random(20000);
        pot = 5000 + random(5000);
        mp = 15 + random(10);

        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("��û�����������\n");

        if ( (string)ob->query("id") != "long dan"
          && (string)ob->query("id") != "hu gu"
          && (string)ob->query("id") != "zhu yu"
          && (string)ob->query("id") != "xuanwu jiake" )
        {
                message_vision(CYN "ʮ������ҡ��ҡͷ����������������ʲô��\n" NOR, me);
                        return 0;
        }

        if (me->query("over_quest/hell_quest/������"))
        {
                message_vision(CYN "ʮ�����޶�$N" CYN "Ц�������Ѿ����ұ������е�ԭ��"
                               "�ˣ���������������Լ��ðɡ�\n" NOR, me);
                        return 0;
        }

        if (! me->query("hell_quest/������"))
        {
                message_vision(CYN "ʮ�����޵����޹�����»������㻹���Լ����Űɡ�\n"
                               NOR, me);
                        return 0;
        }

        if ( (string)ob->query("id") == "long dan" )
        {
                if ( me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/���") )
                {
                        message_vision(HIW "ʮ�����޼�����������ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        me->add("combat_exp", exp);
                        me->add("potential", pot);
                        me->add("magic_points", mp);
                        if (me->query("potential") > me->query_potential_limit()) 
                                me->set("potential", me->query_potential_limit());

                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        me->set("over_quest/hell_quest/������", 1);
                        me->delete("hell_quest/������", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/���", 1);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        add("over", 1);
                        return 1;
                }
           else {
                        if ( me->query("over_quest/hell_quest/ԭ��/����") )
                        {
                                message_vision( HIY "ʮ�����޼�����������$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿�����������ϲ����̫��"
                                                  "�ˣ������������׻������ҵõ��ˡ�\n"
                                                  NOR, environment(me));
                                me->set("over_quest/hell_quest/ԭ��/����", 1);
                                destruct(ob);
                                return 1;
                        }
                }
        }

        if ( (string)ob->query("id") == "hu gu" )
        {
                if ( me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/���") )
                {
                        message_vision(HIW "ʮ�����޼��ǻ��ǣ���ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        me->add("combat_exp", exp);
                        me->add("potential", pot);
                        me->add("magic_points", mp);
                        if (me->query("potential") > me->query_potential_limit()) 
                                me->set("potential", me->query_potential_limit());

                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        me->set("over_quest/hell_quest/������", 1);
                        me->delete("hell_quest/������", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/���", 1);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        add("over", 1);
                        return 1;
                }
           else {
                        if ( me->query("over_quest/hell_quest/ԭ��/����") )
                        {
                                message_vision( HIY "ʮ�����޼��ǻ��ǣ���$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޼��ǻ��ǣ���ϲ����̫��"
                                                  "�ˣ��ǰ׻������������ǵùԹԵİѹ�"
                                                  "ͷ��������\n"
                                                  NOR, environment(me));
                                me->set("over_quest/hell_quest/ԭ��/����", 1);
                                destruct(ob);
                                return 1;
                        }
                }
        }

        if ( (string)ob->query("id") == "zhu yu" )
        {
                if ( me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/���") )
                {
                        message_vision(HIW "ʮ�����޼������𣬴�ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        me->add("combat_exp", exp);
                        me->add("potential", pot);
                        me->add("magic_points", mp);
                        if (me->query("potential") > me->query_potential_limit()) 
                                me->set("potential", me->query_potential_limit());

                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        me->set("over_quest/hell_quest/������", 1);
                        me->delete("hell_quest/������", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/���", 1);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        add("over", 1);
                        return 1;
                }
           else {
                        if ( me->query("over_quest/hell_quest/ԭ��/����") )
                        {
                                message_vision( HIY "ʮ�����޼������𣬶�$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿������𣬴�ϲ��������"
                                                  "�������ȷ����ȸ��ë������лл���ˡ�\n"
                                                  NOR, environment(me));
                                me->set("over_quest/hell_quest/ԭ��/����", 1);
                                destruct(ob);
                                return 1;
                        }
                }
        }

        if ( (string)ob->query("id") == "xuanwu jiake" )
        {
                if ( me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/����")
                  && me->query("over_quest/hell_quest/ԭ��/����") )
                {
                        message_vision(HIW "ʮ�����޼�������׿ǣ���ϲ��������������"
                                       "ԭ�϶��ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ��������"
                                       "�ˣ������\n��İ��������������ǰ�Ҵ�������"
                                       "ɽ�����ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        me->add("combat_exp", exp);
                        me->add("potential", pot);
                        me->add("magic_points", mp);
                        if (me->query("potential") > me->query_potential_limit()) 
                                me->set("potential", me->query_potential_limit());

                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        me->set("over_quest/hell_quest/������", 1);
                        me->delete("hell_quest/������", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        me->delete("over_quest/hell_quest/ԭ��/����", 1);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        add("over", 1);
                        return 1;
                }
           else {
                        if ( me->query("over_quest/hell_quest/ԭ��/���") )
                        {
                                message_vision( HIY "ʮ�����޼�������׿ǣ���$N" HIY "ҡ"
                                                "ͷ�����ⶫ�����Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿�������׿ǣ���ϲ�����ã�"
                                                  "̫���ˣ��ǳ��ڹ걻��ɵ��˰ɣ�\n"
                                                  NOR, environment(me));
                                me->set("over_quest/hell_quest/ԭ��/���", 1);
                                destruct(ob);
                                return 1;
                        }
                }
        }

}

void attempt_apprentice(object ob)
{
        command("say ��������ô˵Ҳ�������еײ�Ĺ����ģ�Ҫ�ݵظ������μ�ȥ�� ");
        return;
}

mixed ask_zhuan()
{
        object who;
        
        who = this_player();
        
        //����ֻ��ת��һ�� by н������
        /*if (who->query("reborn"))
        {
        	
                message_vision("$N��$nһ���֣��������Ѿ�ת����һ���ˣ�ÿ��ֻ��ת��һ�Ρ�\n", 
                               this_object(), who);
                return 1;                
        }*/

        if ((int)who->query("combat_exp") < 20000000 || ! ultrap(who)) 
        {
                message_vision("$N��$nһ���֣��������鲻�������ܲ��죬ǿ��������Ȼ��\n", 
                               this_object(), who);
                return 1;
        }
        
        if (! who->query("animaout")) 
        {
                message_vision("$N��$nһ���֣������㻹û��������ԪӤ�����ء�\n", 
                               this_object(), who);
                return 1;
        }
        
        if (who->query("couple"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���ļ�ͥ����������ת���ɡ�\n", 
                               this_object(), who);
                return 1;                
        }
                                
        if (who->query("bunch"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���İ�������������ת���ɡ�\n", 
                               this_object(), who);
                return 1;                
        }
                        
        if (who->query("brothers"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���Ľ����ֵ�����������ת���ɡ�\n", 
                               this_object(), who);
                return 1;                
        }                
        
        if (who->query("league"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ����ͬ������������ת���ɡ�\n", 
                               this_object(), who);
                return 1;                
        }
        
        if (! who->query("over_quest/hell_quest/������"))
        {
                message_vision("$N��$nһ���֣��������Ȱ����ҵ���������ҩ�������ܵõ�ת���Ļ��ᡣ\n", 
                               this_object(), who);
                return 1;
        }                
   
        if (who->query("HellZhenPass")) 
        {
                message_vision("$N��$nһ���֣����������书��ǿ���ҵ�������ǣ��⡣�����������˰ɣ�\n",
                               this_object(), who);
                return 1;
        }
        
        if (this_object()->query_temp("SomeonePassing")) 
        {
                message_vision("$N��$nһ���֣�������ʱ��Ե���ɣ����������ɡ�\n",
                               this_object(), who);
                return 1;
        }

        message_vision("$N��$n������Ц�˼�����˵��������·�㲻�ߣ����������㴳������\n",
                       this_object(), who);
                       
        this_object()->set_temp("SomeonePassing");

        message("channel:rumor", HIB "�����ܵظ���" + who->query("name") +
                "Ҫ������ڤ�ظ�ʮ�˲�������ߣ�������ʬ�ɣ�\n" NOR, users());          

        message_vision("$N˫������һ�£�$n����ͻȻ������ȥ������\n", 
                       this_object(), who);
        who->delete("env/brief");
        who->move("/d/death/emptyroom");

        command("grin");
        this_object()->move("/clone/misc/void");
   
        call_out("message_ob", 2, who);
        call_out("round_1", 3, who);
        return 1;
}

int check_status(object who)
{
        if ((int)who->query("qi") < 500 ||
            (int)who->query("eff_qi") < 500) 
        {
                remove_call_out("round_2");
                remove_call_out("round_3");
                remove_call_out("round_4");
                remove_call_out("round_5");
                remove_call_out("round_6");
                remove_call_out("round_7");
                remove_call_out("round_8");
                remove_call_out("round_9");
                remove_call_out("round_10");
                remove_call_out("round_11");
                remove_call_out("round_12");
                remove_call_out("round_13");
                remove_call_out("round_14");
                remove_call_out("round_15");
                remove_call_out("round_16");
                remove_call_out("round_17");
                remove_call_out("round_18");
                remove_call_out("message_ob");
                remove_call_out("winning");
                call_out("failed", 1, who);
                return 1;
        }
}

int failed(object who)
{           
        message("channel:rumor", HIB "�����ܵظ��������в������ģ���ϧ"
                "�����Ӳ������������ģ�\n" NOR, users()); 
                
        this_object()->delete_temp("SomeonePassing");
        who->move("/clone/misc/void");
        who->unconcious();
        this_object()->move("/d/death/youmingdian");
        call_out("remove_all", 3);
        return 1;
}


int remove_all()
{   
        int i;
        object *list, empty;

        if (! (empty = find_object("/d/death/emptyroom")))
                empty = load_object("/d/death/emptyroom");
                
        write(HIB "���ܹ���һ�����硣����\n" NOR);
        
        if (empty = find_object("/d/death/emptyroom")) 
        {
                list = all_inventory(empty);
                i = sizeof(list);
                while (i--)
                {
                        object ob=list[i];
                        ob->move("/d/city/wumiao");
                }
        }
        return 1;
}

int winning(object who)
{
        message("channel:rumor", HIB "�����ܵظ�����ϲ" + who->query("name") +
                "������ڤ�ظ�ʮ�˲������������Σ�յ��ں��棡\n" NOR, users());            
        who->set("HellZhenPass", 1);
        who->move("/d/death/yanluodian");
        this_object()->move("/d/death/youmingdian");
        this_object()->delete_temp("SomeonePassing");
        call_out("remove_all", 3);
        return 1;
} 

int message_ob(object who)
{
        switch(random(5)) 
        {
        case 0:
                tell_room(environment(who), "\n������Լ������½�����Χ������ʵ����ɣ�����עĿ��\n");
                break;
        case 1:
                tell_room(environment(who), "\n������Լ������½���\n");
                break;
        case 2:
                tell_room(environment(who),"\n������Լ������½�������ƺ�û�˽��ޡ�����\n");
                break;
        case 3:
                tell_room(environment(who),"\n������Լ������½�����Χһ�ж�����ת������\n");
                break;
        case 4:
                tell_room(environment(who),"\n������Լ������½����½����ƺ��������޾�����Ԩ��\n");
                break;
        }
        return 1;
}

int round_1(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/1");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),RED"                **************************************\n"NOR);
        tell_room(environment(who),RED"                **               ������             **\n"NOR);
        tell_room(environment(who),RED"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_2", 3, who);
        
        return 1;
}

int round_2(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/2");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),GRN"                **************************************\n"NOR);
        tell_room(environment(who),GRN"                **               ������             **\n"NOR);
        tell_room(environment(who),GRN"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_3", 3, who);
        
        return 1;
} 
int round_3(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/3");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),YEL"                **************************************\n"NOR);
        tell_room(environment(who),YEL"                **               ����             **\n"NOR);
        tell_room(environment(who),YEL"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_4", 3, who);  
        
        return 1;
}
int round_4(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/4");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),BLU"                **************************************\n"NOR);
        tell_room(environment(who),BLU"                **               ۺ����             **\n"NOR);
        tell_room(environment(who),BLU"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_5", 3, who);
          
        return 1;
}
int round_5(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/5");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),MAG"                **************************************\n"NOR);
        tell_room(environment(who),MAG"                **               ������             **\n"NOR);
        tell_room(environment(who),MAG"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_6", 3, who);  
        
        return 1;
}
int round_6(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/6");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),CYN"                **************************************\n"NOR);
        tell_room(environment(who),CYN"                **               ��Ƥ��             **\n"NOR);
        tell_room(environment(who),CYN"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_7", 3, who);
          
        return 1;
}
int round_7(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/7"); 
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIR"                **************************************\n"NOR);
        tell_room(environment(who),HIR"                **               ĥ����             **\n"NOR);
        tell_room(environment(who),HIR"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_8", 3, who);  
        return 1;
} 

int round_8(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/8");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIG"                **************************************\n"NOR);
        tell_room(environment(who),HIG"                **               ׶����             **\n"NOR);
        tell_room(environment(who),HIG"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_9", 3, who); 
         
        return 1;
}
int round_9(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/9");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIY"                **************************************\n"NOR);
        tell_room(environment(who),HIY"                **               ������             **\n"NOR);
        tell_room(environment(who),HIY"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_10", 3, who);  
        
        return 1;
}
int round_10(object who)
{
        object ghost;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/10");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIB"                **************************************\n"NOR);
        tell_room(environment(who),HIB"                **               ������             **\n"NOR);
        tell_room(environment(who),HIB"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 2, who);
        call_out("round_11", 3, who);  
        
        return 1;
}

int round_11(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/15");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/11");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIM"                **************************************\n"NOR);
        tell_room(environment(who),HIM"                **               �ѿ���             **\n"NOR);
        tell_room(environment(who),HIM"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_12", 6, who);  
        
        return 1;
}
int round_12(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/11");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/12");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIC"                **************************************\n"NOR);
        tell_room(environment(who),HIC"                **               �鳦��             **\n"NOR);
        tell_room(environment(who),HIC"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_13", 6, who); 
         
        return 1;
}
int round_13(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/16");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/13");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),HIW"                **************************************\n"NOR);
        tell_room(environment(who),HIW"                **               �͹���             **\n"NOR);
        tell_room(environment(who),HIW"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_14", 6, who);  
        
        return 1;
}
int round_14(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/18");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/14");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),RED"                **************************************\n"NOR);
        tell_room(environment(who),RED"                **               �ڰ���             **\n"NOR);
        tell_room(environment(who),RED"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_15", 6, who);  
        
        return 1;
}
int round_15(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/15");
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/14");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),GRN"                **************************************\n"NOR);
        tell_room(environment(who),GRN"                **               ��ɽ��             **\n"NOR);
        tell_room(environment(who),GRN"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_16", 6, who);  
        
        return 1;
}


int round_16(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/15");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/16");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),YEL"                **************************************\n"NOR);
        tell_room(environment(who),YEL"                **               Ѫ����             **\n"NOR);
        tell_room(environment(who),YEL"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_17", 6, who);  
        
        return 1;
}
int round_17(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/16");
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/17");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),BLU"                **************************************\n"NOR);
        tell_room(environment(who),BLU"                **               ������             **\n"NOR);
        tell_room(environment(who),BLU"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("message_ob", 4, who);
        call_out("round_18", 6, who); 
         
        return 1;
}
int round_18(object who)
{
        object ghost, ghostb;
        seteuid(getuid());
        
        ghost = new("/d/death/HellZhen/18");
        seteuid(getuid());
        
        ghostb = new("/d/death/HellZhen/17");
        
        tell_room(environment(who),"\nͻȻ��һ������������\n\n");
        tell_room(environment(who),CYN"                **************************************\n"NOR);
        tell_room(environment(who),CYN"                **               �Ӹ���             **\n"NOR);
        tell_room(environment(who),CYN"                **************************************\n"NOR);
        
        ghost->move(environment(who));
        ghost->invocation(who);
        
        ghostb->move(environment(who));
        ghostb->invocation(who);
        
        call_out("check_status", 1, who);
        call_out("winning", 3, who); 
         
        return 1;
}
