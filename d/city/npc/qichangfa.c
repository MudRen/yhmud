// qi.c �ݳ���

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
	set_name("�ݳ���", ({ "qi changfa","changfa", "qi" }));
	set("title", HIB"�������"NOR);
  set("nickname", HIR "���˲��õ���" HIC "Ը" HIR "���Ϲ�" NOR);
	set("gender", "����");
	set("age", 48);
	set("str", 100);
	set("long",
		"���ϰ����������ƣ���ν�����겻���ţ����Ź����ꡣ\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("higgling", 500);	
	set_temp("apply/damage", 15);

	set("combat_exp", 800000);
	set("attitude", "friendly");

        set("inquiry", ([
                "����" : (: do_answer :),
                "����"     : "�ߣ����������н��޳���",
                "�ҵ�Ǯ"     : "ʲô���Ǯ�����ϵľ����ҵģ�",
                "Ǯ"         : "��Ǯ�����Լ�ȥ����",
                "����"   : "�ӵ���û�ˣ��ٺ١�",
		            "����������" : "���������������ƽ�һ����",
		            "�����"     : "���ΰٶ������������ܻ",
		            "�쾦���"   : "��Ȼ������������������������������ܽ�ٶ���",
        ]));
//�ۼ�100gold���ϵ����� 2017-02-20
	set("vendor_goods", ([
		"/d/shenlong/obj/hua4"    : 2000000,
		"/clone/misc/zhujingchan" : 500000,
		"/clone/fam/gift/str2"    : 5000000,
		"/clone/fam/gift/int2"    : 5000000,
		"/clone/fam/gift/con2"    : 5000000,
		"/clone/fam/gift/dex2"    : 5000000,
    "/clone/fam/gift/kardan"  : 1000000,
    "/clone/fam/gift/perwan"  : 1000000,
    "/clone/medicine/baoming" : 1000000,
    	//�ۼ�100gold���µĲ���
    "/clone/book/tianmo_book" : 200000,
    "/clone/book/zhengqi_book": 200000,
    "/clone/weapon/goldbow3.c": 200000,
	]));

	setup();
	set_max_encumbrance(100000000);
}

void init()
{
        add_action("do_buy", "buy");
	add_action("do_list", "list");
        add_action("do_drop", "drop");
        //add_action("do_look", ({"guankan", "kan"}));
}

int do_drop(string arg)
{
        int i;
        object *ob;

        if (! arg)
                return 0;

        if (! DROP_CMD->main(this_player(), arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;

        ob = all_inventory(this_object());
        for (i = 0; i < sizeof(ob); i++)
                if (! ob[i]->is_character()) destruct(ob[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say �ջ����ۣ�С��֮·��");
                        break;
                case 1:
                        command("kok " + this_player()->query("id"));
                        command("say �������������������Ԫ��");
                        break;
                case 2:
                        command("say �ܼ��ӣ��ܼ��ӣ�");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}

int do_answer()
{
        write(name() + "�����������˵������");
        ::do_list();
        write("������ǻ����ʵ��ͯ�����۰���\n");
        return 1;
}

int accept_object(object who, object ob)
{
        switch(random(6))
        {
        case 0:
                command("say �ã��ã�");
                break;
        case 1:
                command("say ��Ҫ�͸��ң�");
                break;
        }
        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }

        return 1;
}

void recover()
{
        mapping p;

        clear_condition(0);
        p = query_entire_dbase();
        p["eff_qi"] = p["max_qi"];
        p["qi" ] = p["max_qi"];
        p["eff_jing"] = p["max_jing"];
        p["jing" ] = p["max_jing"];
}
/*
int recognize_apprentice(object me, string skill) 
{
        if (skill == "higgling") 
                return 1;                
        else 
                return 0;
}
*/
void unconcious()
{
        message_vision("\n$N�ߺ�������������������...Ŷ����\n",
                       this_object());
        recover();
}

void die()
{
        message_vision("\n$N���һ����������ʹ����������æ�ͳ������������������š�\n",
                       this_object());
        recover();
}
