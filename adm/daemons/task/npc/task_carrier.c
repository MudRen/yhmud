// task carrier

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";


void do_leave();



void create()
{
        string long_desc;
        string *long_list = ({
                "����һ��ʰ���ߣ�����ȥ��ʵ�ͽ��ġ�������\n" +
                "˵���͹ٸ��н��飬��ñ�ȥ���ǡ�\n",
                "\n",
        });
        ::create();
        set("gender", "����");
        set("age", 53 + random(20));

        long_desc = long_list[random(sizeof(long_list))];
        set("long",long_desc);

        set("attitude", "friendly");
        set("chat_chance", 10);
        set("chat_msg", ({ (: do_leave :) }));
        set("chat_chance_combat", 120);
        set("scale", 150);
        set("no_get", 1);

        set_temp("apply/armor", 100);
        set_temp("apply/damage", 15);
        set_temp("born_time", time());
     //   set_temp("dest_time", 910 + time());

        if (clonep()) keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();

        if (my["max_qi"] > 6000)
                my["max_qi"] = 6000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 3000)
                my["max_jing"] = 3000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        my["quest_count"] = me->query("quest_count");

        exp = me->query("combat_exp") * 11 / 10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);

        my["jiali"] = query_skill("force") / 3;
        set_temp("dest_time", 910 + time());

}

void kill_ob(object ob)     
{

        if (! is_busy())
                exert_function("powerup");

        ::kill_ob(ob);
}


int accept_fight(object ob)
{
        command("say �ã����ǾͱȻ��Ȼ���");
        exert_function("powerup");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say ����ȥ�ɣ�");
        exert_function("powerup");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say �ߣ�������");
        exert_function("powerup");
        return 1;
}
                     
void do_leave()
{
        random_move();
        if ( time() - query_temp("born_time") > 1150 )
        {
                message_vision("$N����ææ�����ˡ�\n", this_object());
                destruct(this_object());
                return;
        }
}

int accept_ask(object me,string arg)
{
        int i;
        object *obj;


        obj = all_inventory(this_object());

                for(i=0; i<sizeof(obj); i++) 
                {
            if ( filter_color( obj[i]->name() ) == arg && ! clonep(obj[i]) )
            {  if ( random(3) == 1 )
               {
                  obj[i]->move(me);

                  message_vision(WHT"$N���˿�$n,���ε�˵������������Ȼ�����ҵ���"
                                 "��Ҳ�޻���˵�ˡ���\n"NOR, this_object(), me);

                  tell_object(me,this_object()->name() + "�ó�" +
                              obj[i]->name() + "���㡣\n");

                  message("vision", this_object()->name() + "�ó�" +
                              obj[i]->name() + "��" + me->name() + "\n",
                              environment(this_object()), ({ me }));


                  message_vision("$N����ææ�����ˡ�\n", this_object());
                  destruct(this_object());

                  return 1;
               }
               else
               {       
                   command("say �������ن���!");
                   return 1;
               }
            }
        }
        return 0;
}

void unconcious()
{
    die();
}

void die()
{
     command("say ����������ģ��ҿɲ���������!");
     message_vision("$N����ææ�����ˡ�\n", this_object());
     destruct(this_object());

}
