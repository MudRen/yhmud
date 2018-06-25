// invader.c

#include <ansi.h>
#include <command.h>
#define INVASIOND "/adm/daemons/invasion/invasiond"
#define TOTAL_INVADER 24

inherit NPC;

void init()
{
    object ob;
    ob = this_object();

    if ( random(20) == 1 && time() - query("born_time") > 5 &&
         query("lvl") >= 4 &&
         time() - query_temp("last_chat") >60 )
      {
         command("waidi ������ռ����"NOR HIM + environment(ob)->query("short")
                 +NOR HIW"����������Ǽ���ɱѽ��"NOR);
         set_temp("last_chat",time());
         add_temp("total_chat",1);
      }  

}



int accept_fight(object ob)
{
        command("say ���ǲ���Ҳ���������ò��ͷ��ˣ�");
        if (! is_fighting()) this_object()->set("now_killing",ob->query("id"));
        if ( ! is_busy() ) exert_function("powerup");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say ���ǲ���Ҳ���������ò��ͷ��ˣ�");
        if ( ! is_busy() ) exert_function("powerup");
        if (! is_fighting()) this_object()->set("now_killing",ob->query("id"));
        kill_ob(ob);
        return 1;
}

int accept_touxi(object ob)
{
        command("say ��Ȼ͵Ϯ�ң��й�����û�˸�");
        if (! is_fighting()) this_object()->set("now_killing",ob->query("id"));
        if ( ! is_busy() ) exert_function("powerup");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say �ߣ�������ɱ�����й����أ�");
        if (! is_fighting()) this_object()->set("now_killing",ob->query("id"));
        if ( ! is_busy() ) exert_function("powerup");
        return 1;
}                     

void unconcious()
{
        die();
}


void die()
{
     object ob, ob1;
     int exp,pot,tihui,weiwang,score, div;

     ob = find_player(this_object()->query("now_killing"));
     if ( this_object()->query("nation") == "�ձ�" )
     {
        command("waidi �˸�ѽ·���������Ŀ��");
     } else
     if ( this_object()->query("nation") == "Ӣ��"
          || this_object()->query("nation") == "����" )
     {
        command("waidi Oh,Shit! I don't want to die!");
     } else
     if ( random(2) == 0 )
        {
         command("waidi �찡�������й�����Ϊ�˷��ƣ��벻��������ɥ�ڴˣ�������!");
        }
        else
        {
         command("waidi �ϵ۰����������������������!");
        }

      if ( ob )
      {
        switch (query("lvl"))
        {
        case 1:
                pot = 600;
                break;
        case 2:
                pot = 800;
                break;
        case 3:
                pot = 1200;
                break;
        case 4:
                pot = 1500;
                break;
        case 5:
                pot = 2000;
                break;
        }

        if ( ob->query("combat_exp") > query("combat_exp") )
        {
            div = ob->query("combat_exp") / query("combat_exp");
            if  ( div > 5 ) div = 5;
            pot /= div;
        }

        pot = pot + random(100);
        exp = pot * 2 + random(100);
        tihui = pot  / 2 + random(50);
        weiwang = 20 + random(100);
        score = 20 + random(100);

        if ( ob->query("potential") >= ob->query_potential_limit() )
        {  pot = 1; }
        if ( ob->query("experience") >= ob->query_experience_limit() && tihui > 0)
        {  tihui = 1; }   

          ob->add("combat_exp",exp);
          ob->add("potential",pot);
          ob->add("experience",tihui);

          ob->add("weiwang",weiwang);
          ob->add("score",score);

      tell_object( ob, HIW"\n��ɵ���һ���˹�������"NOR + query("rank") + "��\n"
                   + HIG"������"NOR HIR + chinese_number(exp) +
                  HIG"�㾭�飬"NOR HIW + chinese_number(pot) + NOR
                  HIG"��Ǳ���Լ�"HIY +
                  chinese_number(tihui) + HIG"��ʵս��ᡣ\n"NOR +
                  HIC"���������Լ�����Ҳ�����˲�ͬ�̶ȵ���ߡ�\n" NOR);
      if ( ob->query("waidi/born_time") != this_object()->query("born_time") )
      { ob->delete("waidi");
        ob->set("waidi/born_time",this_object()->query("born_time"));
        ob->add("waidi/number",1);
      } else
      {
        ob->add("waidi/number",1);
      }
      }

     if ( ! query_last_damage_from() ) ob1 = ob;
     else ob1 = query_last_damage_from();

     INVASIOND->set("record/" + query("number") + "/exist", 0);
     INVASIOND->set("record/" + query("number") + "/killer",
                    ob1->query("name") + 
                    "(" + ob1->query("id") + ")");
     INVASIOND->add("record/total_killed",1);
     CHANNEL_D->do_channel(ob1, "waidi",
                    "��λ���ˣ�����"NOR
                   HIY + environment()->query("short") + NOR HIR"������" +
                  query("title") + NOR HIG + query("name") + NOR HIW"��\n" NOR);
     if ( INVASIOND->query("record/total_killed")
        >= TOTAL_INVADER )
     INVASIOND->set_reward();
     ::die();
}

int do_leave()
{              
        mapping exits;
        string *dirs, dir;
        object room;

        if (  ! is_fighting() && ! is_busy() )
        {
            if ( time() - query("born_time") > 600 )
            {
                command("say ����ս���Ѿ������ˣ��һ��ǻع��ɡ�");
                message_vision("$N����ææ�����ˡ�\n", this_object());
                INVASIOND->set("record/" + this_object()->query("number")
                            + "/exist", 0);
                destruct(this_object());
                return 0;
             }     

            if (! mapp(exits = environment()->query("exits")) ||
                 ! sizeof(exits) )
                return 0;
           
                dirs = keys(exits);
                dir =  dirs[random(sizeof(dirs))];
                if ( ! dir ) return 0;
                room = find_object( environment()->query("exits/" + dir) ); 
                if (! room)
                room = load_object(environment()->query("exits/" + dir));
                if ( room->query("no_fight") ) return 0;
                command("go " + dir);
         }
        return 1;
}



