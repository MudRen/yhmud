// liuhongying.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("������", ({ "liu hongying", "liu" }));
        set("title","��ţ��ݽ�ϰ");
        set("long", "����ͷ����ݵ�������ϰ����ɱ�С����Ŷ��\n");
        set("gender", "Ů��");
        set("age", 32);

        set_skill("dodge", 180);
        set_skill("force", 180);
        set_skill("parry", 180);
        set_skill("strike", 180);
        set_skill("sword", 180);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 600000);
        set("shen_type", 1);
        setup();
}

int recognize_apprentice(object ob)
{
        if (!(int)ob->query_temp("marks/jinniu_paied") == 1) return 0;
        return 1;
}
