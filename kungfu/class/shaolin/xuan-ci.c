// Npc: /kungfu/class/shaolin/xuan-ci.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define IS_XUAN_CI      1

#include "xuan.h"

string ask_me();
void create()
{
        set_name("���ȴ�ʦ", ({
                "xuanci dashi",
                "xuanci",
                "dashi",
        }));
        set("long",
                "����һλ�����ü����ɮ����һϮ��˿������ġ�\n"
                "������������ͣ���ȴ�����⣬Ŀ�̴�Ц���Ե��������㡣\n"
        );

        set("nickname", "�����·���");
        set("gender", "����");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("combat_exp", 1450000);
        set("score", 500000);

        set_skill("force", 180);
        set_skill("hunyuan-yiqi", 180);
        set_skill("dodge", 180);
        set_skill("shaolin-shenfa", 180);
        set_skill("finger", 180);
        set_skill("jingang-zhi", 180);
        
        //Ϊ��Ͻ��ָ��������ѧ by н������
        set_skill("jingluo-xue", 200);

        set_skill("strike", 180);
        set_skill("hand", 180);
        set_skill("claw", 180);
        set_skill("parry", 180);
        set_skill("cuff", 180);
        set_skill("nianhua-zhi", 180);
        
        //����wuji4���κ�ָ��Ӧ����ָ�� by н������
        set_skill("duoluoye-zhi", 180);
        set_skill("wuxiang-zhi", 180);
        set_skill("xiuluo-zhi", 180);
        set_skill("tianzhu-fuzhi", 180);
        
        set_skill("sanhua-zhang", 180);
        
        //�������ư˴� by н������
        set_skill("shenzhang-bada", 180);
        
        
        set_skill("fengyun-shou", 180);
        set_skill("longzhua-gong", 180);
        set_skill("yintuoluo-zhua", 180);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("medical", 200);
        set_skill("shaolin-yishu", 200);
        set_skill("unarmed",180);
        set_skill("shaolin-tantui",180);
        set_skill("qinna-shibada",180);
        set_skill("pona-gong",180);
        
        set_skill("qufannao-zhi",180);
        
        set_skill("woshi-zhang",180);
        set_skill("dacidabei-shou",180);
        
        set_skill("fuhu-quan",180);
        set_skill("zuiquan-sanda",180);
        set_skill("jimie-zhua",180);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("������", 36, "����");
        

        set("inquiry", ([
                "pfm"       : (: ask_me :),
                "����"     : (: ask_me :)
        ]));
        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}


string ask_me()
{
        mapping my_fam; 
        object fighter, me;
        //string *sname;
        //int i,j;

        fighter = this_player();
        me = this_object();
        my_fam  = me->query("family");

        if (my_fam && my_fam["family_name"] != "������")
                return RANK_D->query_respect(fighter) +
                       "�ֲ������������µ��ˣ��������־�����ʲô��";
        return "���������ѧϰ���о���: һָ������,��շ�ħ��,��Ѫ����צ��\n";

}

//����pfm����
int accept_ask(object me, string topic)  
{
        switch (topic)  
        {        
        
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;
        
                 
         case "һָ������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/jingang-zhi/san",  
                           "name"    : "һָ������",  
                           "sk1"     : "jingang-zhi",  
                           "lv1"     : 200,  
                           "force"   : 300,  
                           "neili"   : 3000,  
                           "gongxian": 3000,  
                           "shen"    : 50000, ]));  
                break;  
         
         case "��շ�ħ��" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/jingang-zhi/fumo",  
                           "name"    : "��շ�ħ��",  
                           "sk1"     : "jingang-zhi",  
                           "lv1"     : 150,  
                           "force"   : 200,  
                           "neili"   : 2000,  
                           "gongxian": 1000,  
                           "shen"    : 30000, ]));  
                break;  
         
         case "��Ѫ����צ" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/yintuoluo-zhua/chixue",  
                           "name"    : "��Ѫ����צ",  
                           "sk1"     : "yintuoluo-zhua",  
                           "lv1"     : 200,  
                           "force"   : 300,  
                           "neili"   : 3000,  
                           "gongxian": 1500,  
                           "shen"    : 50000, ]));  
                break;  
                            
        default:  
                return 0;  
        }
}