
//�������  

#include <ansi.h>
              
inherit NPC;
inherit F_UNIQUE;


#define MIRROR        "/adm/daemons/task/mirror"


int ask_mirror();
int ask_hulu();

void create()
{         seteuid(getuid());
        set_name("�������", ({ "zixu daoren", "zixu", "daoren" }));
        set("long", @LONG
�������ŵ��ۣ��뷢�԰ף�һ���ɷ���ǵ���
�ɡ�����������кųơ��������С���������
��������ˡ���˵�������ѵõ����ɣ���ͨ��
�硣
LONG);
        set("nickname", HIW "�ɷ����" NOR);
        set("title", HIC "����۹���" NOR);
        set("gender", "����" );
        set("age", 108);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                       "Ǭ������"      : (: ask_mirror :),
                       "����"      : (: ask_mirror :),
                       "mirror"      : (: ask_mirror :),    
//              "�Ͻ��«"    : (: ask_hulu :),
//                 "hulu"    : (: ask_hulu :),
        ]));

        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));

    
        setup();
        carry_object("/d/wudang/obj/whiterobe")->wear();

}


int ask_mirror()
{       
    
      object me, ob, *obj;
      int i,have;
      me = this_player();
      have = 0;

      obj = all_inventory(me);
                for(i=0; i<sizeof(obj); i++) 
                {       
                        if (base_name(obj[i]) == MIRROR)
                        {
                  have = 1;
                        }  
         }

            if ( have == 1 )

            {
               message_vision(HIG "$N��$n˵�������������Ѿ���һ�������ˣ�"
                                                  "��̰�����ᣡ��\n"NOR,
                                this_object(),me );
               return 1;
            }
            else
            {

           ob = new(MIRROR);
           ob->move(me);

       message_vision(HIG "$N����$n���˿���˵�������ţ����������ɵ����ã�\n"
                         "�ú�����������������ж����͹۲����ɡ���\n"NOR
                         CYN"$N�ӻ����ó�һ��Ǭ����������$n��\n"NOR,
                            this_object(), me);
              return 1;
            }

      return 1;

}


void unconcious()
{
        die();
}
