// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;

#include <ansi.h>
#include <login.h>

#define PET_OBJ        "/clone/npc/pet.c"
#define PET_DIR        "/data/pet/"

int  do_selete();  
void get_type(string arg, object ob);
void get_subtype(string arg, object ob);
void get_gender(string arg,object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_pet(object ob);
int  check_legal_name(string name, int max_len);
int  check_legal_id(string name);
void confirm_dispose(string arg, object ob, object fabao_ob);

string* pet_type_name = ({
        "��", "¿", "��", "��", "ţ", "��",
        "ʨ", "��", "��", "¹", "��", "��",
        "��", "��", "��", "��", "��", "��",
        "��", "��",
});

string* pet_id_surfix = ({
        "ma", "lv", "luo", "tuo", "niu", "xiang",
        "shi", "hu", "bao", "lu", "he", "diao",
        "yang", "hou", "xiong", "lang", "hu", "diao",
        "ju", "shou",
});

string* pet_unit_name=({
        "ƥ", "ͷ", "ͷ", "ͷ", "ͷ", "ͷ",
        "ֻ", "ֻ", "ֻ", "ͷ", "ֻ", "ֻ",
        "ͷ", "ֻ", "ֻ", "��", "ֻ", "ֻ",
        "ƥ", "ͷ",
});

void create()
{
        set_name("���ϰ�", ({"horse boss", "boss"}));
        set("title", HIR"��������"NOR);
        set("gender", "����");
        set("age", 32);
        set("long", "һ���������ص��ϰ壬�ǹض��������פ�����ݳ��ṩ����ġ�\n"
                    "�����������ѡ��(choose)�Լ�������������\n");
                    
        set("attitude", "peaceful");
        set_skill("training", 400);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("coin", 10000);

}

void init()
{
//      object ob;

        ::init();
        add_action("do_selete", "choose");
}

int do_selete()
{
        object me = this_player();
                   
        if (me->query_skill("training", 1) < 100)
                return notify_fail("���Ԧ����̫���ˣ���ʹ�������Ҳ�������ȥ��\n");
        
        if (! me->query_temp("pet/money"))
        {
                command("say ��λ" + RANK_D->query_respect(me) + "��ÿֻ����һǧ���ƽ�");
                return 1;
        }
                               
        write("��Ҫ���������\n");
        write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
        write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
        write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
        write("19. ��  20. ��\n");
        write("��ѡ��(q ��ȡ��)");
        
        input_to( (: get_subtype :), me);
        return 1;
}
void get_subtype(string arg, object ob)
{
        int order;
   
        if (arg == "q" || arg == "Q")    
                return;

        sscanf(arg, "%d", order);
    
        if (order <= 0 || order > 20)  
        {               
                write("��������������͵��ع�أ�ѡ������Ͳ��ܺ���ˣ���������Ҳ��������\n");
                write("��Ҫ���������\n");
                write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
                write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
                write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
                write("19. ��  20. ��\n");
                write("��ѡ��(q ��ȡ��)");
                input_to( (: get_subtype :), ob);
                return;
        }
        
        ob->set_temp("pet/pet_type",  order);

        write("\n");
        write("���趨������Ա�(���ԣ�1  ���ԣ�0)��");
        input_to( (: get_gender :), ob ); 
}

void get_gender(string arg, object ob)
{
        int gender;
        
        sscanf(arg, "%d", gender);

        if (gender != 0 && gender != 1)  
        {
                write("\n");
                write("���趨������Ա�(���ԣ�1  ���ԣ�0)��");
                input_to( (: get_gender :), ob );
                return;
        }
        ob->set_temp("pet/pet_gender", gender ? "����" : "Ů��");

        write("\n");
        write("����������趨Ӣ�� id ����ע�⣬���趨��Ӣ�� id ���Զ����Ϻ�׺�������� id��\n");
        write("���������趨�� id �� biyunwulong ju����ô��ֻҪ���� biyunwulong �Ϳ��ԡ�\n");        
        write("���趨Ӣ�� id ��");
        input_to( (: get_id :), ob );
}

int check_legal_id(string id)
{
        int i;
//      string *legalid;
        object ppl;   
          
        i = strlen(id);
        
        if ((strlen(id) < 3) || (strlen(id) > 20)) 
        {
                write("�Բ���Ӣ�� id ������ 3 �� 20 ��Ӣ����ĸ��\n");
                return 0;
        }
        
        while(i--)
        
        if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))  
        {
                write("�Բ���Ӣ�� id ֻ����Ӣ����ĸ��\n");
                return 0;
        }

        ppl = LOGIN_D->find_body(id);
        
        if (ppl || id == "guest" || id == "new") 
        {
                write("��������������ID��ͬ�ˣ�����");
                return 0;
        }

        if (file_size(sprintf("/data/user/%c/%s", id[0], id)
                    + __SAVE_EXTENSION__) >= 0) 
        {
                write("��������Ѿ���������ʹ���ˣ�����");
                return 0;
        } 
        /*        
        legalid = explode(read_file(BANNED_ID), "\n");
        for (i = 0; i < sizeof(legalid); i++)   
        {
                if (id == legalid[i])   
                {
                        write("�Բ������� id ����������˵����š�\n");
                        return 0;
                }
        }
        */    
        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
//      string  *legalname;             //not implemented..may add later
        
        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len )) 
        {
                write(sprintf("�Բ������������ֱ����� 1 �� %d �������֡�\n",
                      max_len / 2));
                return 0;
        }
        
        if (max_len < 13 && strsrch(NAME_D->who_is(name), "��") >= 0)
        {
                write("�Բ�����������ֲ��ܺ���ҵ������ظ���\n"); 
                return 0;
        }

        if (max_len < 13 && ! is_chinese(name))
        {
                write("�Բ��������á����ġ�Ϊ����ȡ���ֻ�������\n");
                return 0;
        }
        return 1; 
}


void get_id(string arg, object ob)
{
        arg = lower_case(arg);
        
        if (! check_legal_id(arg))   
        {
                write("\n");
                write("����������趨Ӣ�� id ����ע�⣬���趨��Ӣ�� id ���Զ����Ϻ�׺�������� id��\n");
                write("���������趨�� id �� biyunwulong ju����ô��ֻҪ���� biyunwulong �Ϳ��ԡ�\n");                    
                write("���趨Ӣ�� id ��");
                input_to( (: get_id :), ob ); 
                return;
        }

        arg = replace_string(arg, " ", "_");    
        
       ob->set_temp("pet/pet_id", arg + " " + pet_id_surfix[ob->query_temp("pet/pet_type") - 1]);
        ob->set_temp("pet/pet_bz", arg);
        //ob->set_temp("pet/pet_bz", arg + " " + pet_id_surfix[ob->query_temp("pet/pet_type") - 1]);
        write("\n");
        write("����������趨����������ע�⣬���趨������������ϻ�������\n");
        write("������ѡ�����ʨ��������ΪС�ף����־ͻ�ΪС��ʨ��\n");
        write("���趨��������(�ɼ���ɫ)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        
                
        arg_old = arg;
        /*
        arg = trans_color(arg, 1);
        arg = filter_color(arg);
        */
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");

        if (! check_legal_name(arg, 12))  
        {
                write("����������趨����������ע�⣬���趨������������ϻ�������\n");
                write("������ѡ�����ʨ��������ΪС�ף����־ͻ�ΪС��ʨ��\n");
                write("���趨��������(�ɼ���ɫ)");
                input_to( (: get_name :), ob);
                return;
        }

        arg = arg_old;
        // arg = trans_color(arg, 1); 
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        
        ob->set_temp("pet/pet_name", arg);
        
        write("\n");
        write("���������(���ɼ���ɫ)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
       
                
        if (! check_legal_name(arg, 60))  
        {
                write("���������(���ɼ���ɫ)");
                input_to( (: get_desc :), ob);
                return;
        }

        ob->set_temp("pet/pet_desc",  arg);
        write("ok\n");
        //������к�
        build_pet(ob);
}

void build_pet(object ob)
{
        string *id_list;       
        string msg;
        string fn;
        string fc;
//      int rev;
        object pet;
             
        string pet_type = ob->query_temp("pet/pet_type");
        string pet_id = ob->query_temp("pet/pet_id");
        string pet_name = ob->query_temp("pet/pet_name");
        string pet_desc = ob->query_temp("pet/pet_desc");
//      string pet_bz = ob->query_temp("pet/pet_bz");
        string bpet_name = pet_type_name[(int)pet_type - 1];     
        string pet_gender = ob->query_temp("pet/pet_gender");

        pet_name += bpet_name + NOR;
        
        id_list = ({ pet_id });
        
        fc = read_file(PET_OBJ);
        
        //������к�
        fc = replace_string(fc, "PET_NAME", pet_name);
        fc = replace_string(fc, "PET_ID", pet_id);                                                       
        fc = replace_string(fc, "PET_GENDER", pet_gender);
                            
        fc = replace_string(fc, "PET_UNIT",
                            pet_unit_name[(int)pet_type - 1]);
                            
        fc = replace_string(fc, "LONG_DESCRIPTION", 
                            pet_desc + "\n" + "����" + 
                            ob->query("name") + "�����\n");
        
        fc = replace_string(fc, "OWNER_ID", ob->query("id"));
        fc = replace_string(fc, "OWNER_NAME", ob->query("name"));
                            
        fn = PET_DIR + ob->query("id") + "-" + "pet";
        
        if (file_size(fn + ".c") > 0)
        {
                if (pet = find_object(fn)) destruct(pet);
                rm(fn + ".c");
        }

        assure_file(fn);
        write_file(fn + ".c", fc); // д���ļ�
        VERSION_D->append_sn(fn + ".c"); // ����Ʒ����ʶ����

        pet = load_object(fn);
        
        msg = "$N���ݺ�����������ǣ��" + pet_name + "������\n" +
               "��ϲ$n����" + pet_name + "���Ժ�$n��Ҫ�úô�����\n";
               
        message_vision(msg, this_object(), ob);    
            
        pet->move(environment(ob));
        command("say ����Դ��������ٻ�������<whistle " + pet_id +">\n");
        ob->set("can_whistle/" + pet_id, fn);
        ob->delete_temp("pet");
        ob->save();
        return;
       
       
}

int accept_object(object me, object ob)
{
        command("xixi");
        command("say �Ǻǣ���л��λ" + RANK_D->query_respect(me) + " ��");

        if (me->query_skill("training", 1) < 100)
        {
                command("say ���Ԧ������������ʹ�������Ҳ�������ȥ��");
                return 0;
        }

        if (ob->query("money_id"))
        {
                if (ob->value() < 10000000)
                {
                        command("say ��λ����δ�����˵㣡ÿֻ����Ҫһǧ���ƽ�");
                        return 0;
                }
                else
                {
                        me->set_temp("pet/money",1);
                        command("say ���������ˣ�");
                        command("say " + me->name() +
                                     "�������������и��ֿɵ�������Ķ��");
                        command("say ��ѡ����Ҫ�Ķ��� < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}
int recognize_apprentice(object me, string skill) 
{
        if (skill == "training") 
                return 1;                
        else 
                return 0;
}