// xiaofei.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "xiao fei", "xiao" }));
        set("title","��ţ��ݽ�ϰ");
        set("long", "����ͷ����ݵ�������ϰ�������ĵ���Ҳ���ڽ�����ͷ���ˡ�\n");
        set("gender", "����");
        set("age", 35);

        set_skill("dodge", 180);
        set_skill("force", 180);
        set_skill("parry", 180);
        set_skill("finger", 180);
        set_skill("throwing", 180);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 600000);
        set("shen_type", 1);
        setup();
}

int recognize_apprentice(object ob)
{
        if (! (int)ob->query_temp("marks/jinniu_paied") == 1) return 0;
        return 1;
}