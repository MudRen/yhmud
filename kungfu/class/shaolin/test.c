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

        set_skill("force", 170);
        set_skill("hunyuan-yiqi", 170);
        set_skill("dodge", 160);
        set_skill("shaolin-shenfa", 160);
        set_skill("finger", 170);
        set_skill("strike", 170);
        set_skill("hand", 160);
        set_skill("claw", 160);
        set_skill("parry", 160);
        set_skill("nianhua-zhi", 170);
        set_skill("sanhua-zhang", 170);
        set_skill("fengyun-shou", 160);
        set_skill("longzhua-gong", 160);
        set_skill("buddhism", 160);
        set_skill("literate", 160);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);
        set_skill("unarmed",180);
        set_skill("tan-tui",180);
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
        mapping fam, my_fam, skl; 
        object fighter, me, room, monk;
        string *sname;
        int i,j;

        fighter = this_player();
        me = this_object();
        my_fam  = me->query("family");

        if (my_fam && my_fam["family_name"] != "������")
                return RANK_D->query_respect(fighter) +
                       "�ֲ������������µ��ˣ��������־�����ʲô��";
        return "�����������ʦ�ֵ�ѧϰ�й� �ȱ��־�,��������,��Ѫצ,�޺���ħ,��ʯ����,һָ������,��Ӱ����,������,���ָѨ,��������,��������,��ϼ����,���ƾ���";

}
