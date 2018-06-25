// beastseller.c

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

#define BEAST_OB          "/clone/npc/magicbeast.c"
#define BEAST_DIR         "/data/beast/"


void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_beast(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);

string *beast_type_name = ({
        "��", "¿", "��", "��", "ţ", "��",
        "ʨ", "��", "��", "¹", "��", "��",
        "��", "��", "��", "��", "��", "��",
        "��", "��",
});

string *beast_id_surfix = ({
        "ma", "lv", "luo", "tuo", "niu", "xiang",
        "shi", "hu", "bao", "lu", "he", "diao",
        "yang", "hou", "xiong", "lang", "hu", "diao",
        "ju", "shou",
});

string *beast_unit_name=({
        "ƥ", "ͷ", "ͷ", "ͷ", "ͷ", "ͷ",
        "ֻ", "ֻ", "ֻ", "ͷ", "ֻ", "ֻ",
        "ͷ", "ֻ", "ֻ", "��", "ֻ", "ֻ",
        "ƥ", "ͷ",
});

void create()
{        
        set_name("���ʹ��", ({ "kuangfeng shizhe", "kuangfeng", "shizhe" }) );
        set("gender", "����" );
        set("age", 21);
        set("long",@LONG
���ʹ������֪��������������ͻȻ���������ݳǣ�������
������ٻ��ޣ������ϲ���Ļ�������Ҳѡ(choose)һֻ��
LONG );
        set("title",HIW"�ٻ�������"NOR);
        set("combat_exp", 5);
        
        set("inquiry", ([ 
                "�ٻ���"     : "ֻҪ����һ�����ƽ������ӵ���ٻ����ˣ�", 
                
        ]));

        set_skill("training", 400);    
        set("chat_chance", 15);
        set("attitude", "friendly");
	        
        setup();
        carry_object("/clone/cloth/cloth")->wear();   
}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_choose", "choose");
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "���ʹ��˵������λ" + RANK_D->query_respect(ob)
                                + "��Ҫ�ٻ���ô��\n");
                        break;
        }
}

int do_choose()
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("����һ��������û����ɡ�\n");
                
        if (file_size(me->query_save_file() + "-beast.o") > 0 &&
            mapp(me->query("can_whistle")))
                return notify_fail("���Ѿ�ӵ�����İ����ٻ����ˡ�\n");
                                   
        if (me->query_skill("training", 1)<200)
                return notify_fail("���Ԧ����̫���ˣ���ʹ�����ٻ��ޣ�Ҳ�ᱳ�����ȥ��\n");
        
        if (! me->query_temp("beast/money"))
        {
                command("say ��λ" + RANK_D->query_respect(me) + "��ÿֻ�ٻ���һ�����ƽ�������ȸ�Ǯ��");
                return 1;
        }
                               
        write("��Ҫ�������ٻ��ޣ�\n");
        write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
        write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
        write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
        write("19. ��  20. ��\n");
        write("��ѡ�����ִ��ţ�(q ��ȡ��)");
        
        input_to( (: get_subtype :), me);
        return 1;
}

void get_subtype(string arg, object ob)
{
        int n;
   
        if (arg == "q" || arg == "Q")    
                return;

        sscanf(arg, "%d", n);
    
        if (n <= 0 || n > 20)  
        {               
                write("��Ҫ�������ٻ��ޣ�\n");
                write(" 1. ��   2. ¿   3. ��   4. ��  5. ţ  6. ��\n");
                write(" 7. ʨ   8. ��   9. ��  10. ¹ 11. �� 12. ��\n");
                write("13. ��  14. ��  15. ��  16. �� 17. �� 18. ��\n");
                write("19. ��  20. ��\n");
                write("��ѡ�����ִ��ţ�(q ��ȡ��)");
                input_to( (: get_subtype :), ob);
                return;
        }
        ob->set_temp("beast/beast_type", n);

        write("\n");
        write("���趨�ٻ��޵��Ա�(���ԣ�1  ���ԣ�0)��");
        input_to( (: get_gender :), ob ); 
}

void get_gender(string arg, object ob)
{
        int n;
        object beast;
        
        sscanf(arg, "%d", n);

        if (n != 0 && n != 1)  
        {
                write("\n");
                write("���趨�ٻ��޵��Ա�(���ԣ�1  ���ԣ�0)��");
                input_to( (: get_gender :), ob );
                return;
        }
        ob->set_temp("beast/beast_gender", n ? "����" : "Ů��");
          
        write("\n");
       
        write(sort_string(CYN "�㰴�տ��ʹ�ߵ�ָ�㿪ʼ�ɿ�������������ļ�"
                "֤֮�£����������ǻۡ���������һ���ǿ���������ѽ����"
                "������������ԣ������ҵ����ߣ��ң�" + ob->query("name") +
                "��������޽�������Ѫ֮��Լ���մ���Ω��������Ϊ����֮����"
                "��������\n" NOR, 64));        

        write(sort_string(WHT "ֻ�������еĻ�����ȴ����һ���������������е�ħ"
                "�������¶��쳣�����ߣ������������ֵĸ��£��������������ж�"
                "����ĸо���$N�����ڴ��У�ԭ���⻪����ǿ��ǳ����Ѻۣ�Ȼ"
                "���ѺۼӴ�һ�����أ�˵����������ζ����ʼɢ�����������"
                "�ռ䡣���ţ�һ�����۴�С��ͷ���˳������������е���" + 
                beast_type_name[ob->query_temp("beast/beast_type") - 1] +  "�����ӣ�������������ȫ¶"
                "�˳���������ֻ�а��Ʋ����Ĵ�С��һ��Ӧ������ɫ�ģ�����Ϊմ"
                "����ʪ���Һ����������ɫ��С���޿���$Nһ�ۣ����С��ͷ��"
                "��Ĵָ�����˼��£�����һ���������Ľ������漴��ʼ�����ѿǣ�"
                "һ���ӣ�������������ѿ�һ���Ӿͱ��Թ��ˣ�ֻ�����ɰ��Ĵ���"
                "�����ã�������������������$N�������С�\n" NOR, 64));
                
        write("\n");
        write("���趨�ٻ��޵�Ӣ�� id ��");
        input_to( (: get_id :), ob ); 
}

void get_id(string arg, object ob)
{
        arg = lower_case(arg);
        
        if (! check_legal_id(arg))   
        {
                write("\n");
             
                write("���趨�ٻ��޵�Ӣ�� id ��");
                input_to( (: get_id :), ob ); 
                return;
        }

        arg = replace_string(arg, " ", "_");    
        
        // ob->set_temp("beast/beast_id", arg + " " + beast_id_surfix[ob->query_temp("beast/beast_type") - 1]);
        ob->set_temp("beast/beast_id", arg);
        ob->set_temp("beast/beast_unit", beast_unit_name[ob->query_temp("beast/beast_type") - 1]);
        
        write("\n");
        write("���趨�ٻ��޵���������(�ɼ���ɫ)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        string  result;
       
                
        arg_old = arg;
        
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
                write("���趨�ٻ��޵���������(�ɼ���ɫ)");
                input_to( (: get_name :), ob);
                return;
        }

        if (stringp(result = NAME_D->invalid_new_name(arg)))
        {
                write("�Բ���" + result);
                write(HIR "��ֹʹ��������������ͬ��ӽ����ٻ�����������ѭRULES�ж����ֵ���ع涨��"NOR+"\n");
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
        
        ob->set_temp("beast/beast_name", arg);
        
        write("\n");
        write("�������ٻ��ޣ�(���ɼ���ɫ)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");  
        if (! check_legal_name(arg, 60))  
        {
                write("�������ٻ��ޣ�");
                input_to( (: get_desc :), ob);
                return;
        }

        ob->set_temp("beast/beast_desc",  arg);
        write("ok\n");
        build_beast(ob);
}

void build_beast(object ob)
{
        string file, filename;
        object beast, money;        
        string beast_id;
        string beast_name;
        string beast_unit;
        string beast_desc;
        string beast_gender;

        beast_id = ob->query_temp("beast/beast_id");
        beast_name = ob->query_temp("beast/beast_name");
        beast_name += NOR;
        beast_unit = ob->query_temp("beast/beast_unit");
        beast_desc = ob->query_temp("beast/beast_desc");
        beast_desc += NOR;
        beast_gender = ob->query_temp("beast/beast_gender");
        
        file = read_file(BEAST_OB);
        
        file = replace_string(file, "BEAST_NAME", beast_name);
        file = replace_string(file, "BEAST_ID", beast_id);                                                       
        file = replace_string(file, "BEAST_GENDER", beast_gender);                           
        file = replace_string(file, "BEAST_UNIT", beast_unit);                          
        file = replace_string(file, "LONG_DESCRIPTION", 
                            beast_desc + "\n" + "����" + 
                            ob->query("name") + "���ٻ��ޡ�\n");
        
        file = replace_string(file, "OWNER_ID", ob->query("id"));
        file = replace_string(file, "OWNER_NAME", ob->query("name"));
                            
        filename = BEAST_DIR + ob->query("id") + "-" + "beast";
        
        if (file_size(filename + ".c") > 0)
        {
                if (beast = find_object(filename)) 
                        destruct(beast);
                DBASE_D->clear_object(filename);
                rm(filename + ".c");
        }

        assure_file(filename);
        write_file(filename + ".c", file); // д���ļ�
        VERSION_D->append_sn(filename + ".c"); // ����Ʒ����ʶ����
  
        catch(call_other(filename, "???"));
        beast = find_object(filename);
        if (! beast)
        {
                ob->delete_temp("beast"); 
                money = new("/clone/money/gold");
                money->set_amount(100);
                money->move(ob, 1);
                message_vision("$Nһ������$n������Ǹ��Ǹ������һЩ���⣡Ǯ�һ��ǻ���ɡ�\n",
                               this_object(), ob);
                return;
        }
        

        beast->save();
        destruct(beast);              

        ob->set("can_whistle/" + beast_id, filename);     
        ob->delete_temp("beast");        
        command("say ����Դ��������ٻ�����ٻ��ޣ�<whistle " + beast_id +">\n");
        return;
}

int accept_object(object me, object ob)
{
        string filename;
        string file;
       

        if (me->query_skill("training", 1) < 30)
        {
                command("say ���Ԧ������������ʹ�����ٻ��ޣ�Ҳ�������ȥ��");
                return 0;
        }

        if (ob->query("money_id"))
        {
                if (ob->value() < 1000000)
                {
                        command("say ��λ����δ�����˵㣡ÿֻ�ٻ�����Ҫһ�����ƽ�");
                        return 0;
                }
                else
                {
                        me->set_temp("beast/money",1);
                        command("say ���������ˣ�");
                        command("say " + me->name() +
                                     "�������������и����ٻ����ѣ�");
                        command("say ��ѡ����Ҫ���ٻ����� < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}

int check_legal_id(string id)
{
        int i;
        //array legalid;
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

        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later
        
        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len )) 
        {
                write(sprintf("�Բ����ٻ��������ֱ����� 1 �� %d �������֡�\n",
                      max_len / 2));
                return 0;
        }
        
        if (max_len < 13 && ! is_chinese(name))
        {
                write("�Բ��������á����ġ�Ϊ����ȡ���ֻ�������\n");
                return 0;
        }
        return 1; 
}

int attempt_apprentice(object ob)
{
        command("say ��������һ�߶�ȥ��");
}

int recognize_apprentice(object me, string skill) 
{
        if (skill == "training") 
                return 1;                
        else 
                return 0;
}
