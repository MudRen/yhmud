//  ��Ц̸���¡�����[Opop]��Ӣ�����¡��ա��⡢����������

inherit F_DBASE;

#include <ansi.h>
#define   INVADE_NPC  "/adm/daemons/invasion/npc"
#define TOTAL_INVADER 24
#define TURN 3600

void create()
{
        seteuid(getuid());
        set("name", HIG "��������������ļ�" NOR);
        set("id", "invasion");
        call_out("main", 600);
}


void main()
{
   int i,lvl;

   message( "invasion", HIR"��������֡�" BLINK
            "�������������˹��������뱱���ˣ�\n" NOR
            HIR"��������֡�"NOR HIY"���λ��Ϻ��������������У�"+
            "��waidiƵ���ɻ�֪ս����\n"NOR, users() );
   this_object()->delete("record");
   this_object()->set("record/born_time",time());

   for (i = 0; i < TOTAL_INVADER; i++)
   {
        if ( i == 0 ) lvl = 5;
        if ( i >= 1 && i <= 2 ) lvl = 4;
        if ( i >= 3 && i <= 5 ) lvl = 3;
        if ( i >= 6 && i <=11 ) lvl = 2;
        if ( i >= 12 && i <= 23 ) lvl = 1;

        call_other(__FILE__, "create_invader", lvl, i);
   }

      remove_call_out("main");
      call_out("main", TURN);

}

// generate an invader with nation & skill level
object create_invader(int lvl, int number)
{
        object ob;

        string *n, *place, nation, locate;

        n = ({ "�ձ�", "�ձ�", "Ӣ��", "����˹", "�¹�", "����", "����",
               "���ٵ۹�", "�����"});  
  
        place = ({"/d/beijing/tiananmen", "/d/beijing/dianmen",
                  "/d/beijing/huangling", "/d/beijing/wenmiao",
                  "/d/beijing/xingchang", "/d/beijing/minju_y",
                  "/d/beijing/mianguan", "/d/beijing/yong_3",
                  "/d/beijing/tiantan", "/d/beijing/caishi"});

        nation = n[random(sizeof(n))];
        locate = place[random(sizeof(place))];

        switch (nation)
        {
        case "�ձ�":
                ob = new(INVADE_NPC + "/japanese");
                NPC_D->generate_jp_name(ob);
                break;
        case "Ӣ��":
        case "����":
                ob = new(INVADE_NPC + "/english");
                NPC_D->generate_e_name(ob);
                break;
        case "����":
        case "�¹�":
        case "����˹":
        case "�����":
        case "���ٵ۹�":
                ob = new(INVADE_NPC + "/european");
                NPC_D->generate_e_name(ob);
                break;
        }

        ob->set("nation", nation);
        ob->set("number", number);
        ob->set("born_time",this_object()->query("record/born_time"));

        call_other(__FILE__, "set_invader_skill",ob, lvl);
        ob->move(locate);
        if ( objectp(locate) )
        tell_room(locate,ob->query("name") + "ɱ�˹�����\n");
}


// set the the level of the invader's skill

void set_invader_skill(object ob, int lvl)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp, qi, jing, neili;
        string rank;

        sk_lvl = lvl * 50 + 200 + random(50);
        switch(lvl)
        {
         case 1 :
                      sk_lvl = 180 + random(10);
                      qi = 10000;
                      rank = HIW"��Ӷ��"NOR;
                      break;
         case 2 :
                      sk_lvl = 300 + random(50);
                      qi = 15000;
                      rank = HIB"СͷĿ"NOR;
                      break;
         case 3 :
                      sk_lvl = 400 + random(50);
                      rank = HIC"��ͷĿ"NOR;
                      qi = 18000;                 
                      break;
         case 4 :
                      sk_lvl = 450 + random(50);
                      qi = 20000;
                      rank = YEL"��˾��"NOR;                
                      break;
         case 5 :
                      sk_lvl = 500 + random(50);
                      rank = HIR"��˾��"NOR;
                      qi = 30000;             
                      break;
        }

        ob->set("title", HIY + "�˹�����"NOR + rank + NOR);
        ob->set("nickname",HIW + ob->query("nation") + "��Ӷ��"NOR);
        ob->set("lvl",lvl);
        ob->set("rank",rank);
        ob->set("kind","invader");

        exp = sk_lvl * sk_lvl * sk_lvl / 10 + random( 1000 * lvl );
        ob->set("combat_exp", exp);
        //����skill
        if (! ob->query_skills())
                return;

        ks = keys(ob->query_skills());

        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);

        jing = qi / 2;
        neili = qi * 8 / 5;

        ob->set("max_qi", qi);
        ob->set("max_jing", jing);
        ob->set("max_neili", neili);
	    ob->set("eff_jing", jing);
	    ob->set("jing", jing);
        ob->set("eff_qi", qi);
	    ob->set("qi", qi);
        ob->set("neili", neili * 2);
        ob->set("jiali", ob->query_skill("force") / 2);

        this_object()->set("record/" + ob->query("number") + "/name",
                            ob->query("name"));
        this_object()->set("record/" + ob->query("number") + "/title",
                            ob->query("title"));
        this_object()->set("record/" + ob->query("number") + "/exist", 1);  
        return;
}

void set_reward()
{
   this_object()->set("record/all_killed",1);
   message( "invasion", HIR"��������֡�"NOR HIG"�����ܹ�[Danei zongguan]:ʥּ����\n"NOR
         HIY"                   ������ˣ��ʵ�گԻ��\n"
            "           ��������֮��б��ҷ���ʿȫ�ߣ��������մ��֣�\n"
            "           ���������п�������й��߽������͡�\n"
            "                                �մˣ�\n" NOR,users());
}
