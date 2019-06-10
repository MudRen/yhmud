// �þ���ħ

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

int  accept_object(object who, object ob);

void random_move();
int  leave();
int  is_stay_in_room()  { return 1; }

void create()
{
    ::create();
    set("gender", random(5) ? "����" : "Ů��");
    set_name("��ħ", ({"xin mo", "mo", "daemon"}));
    // set("age", 20 + random(40));
    set("long", "���������ħ��\n");
    set("attitude", "aggressive");
    set("chat_chance", 1); // 1/120 �Ļ���
    set("chat_msg", ({ (: random_move :) }));
    set("chat_chance_combat", 120);
    set("scale", 100);
    set("no_get", 1);

    set_temp("apply/armor", 100);
    set_temp("apply/damage", 15);
    set_temp("born_time", time());

    add_money("silver", 1 + random(10));
    setup();
    if (clonep()) keep_heart_beat();
}

void set_from_me(object me, int scale)
{
    mapping my;
    int s, f, x, y, z;
    // debug_message("scale = " + scale);
    NPC_D->init_npc_skill(this_object(), NPC_D->get_exp(me));
    my = query_entire_dbase();
    s = this_object()->query_con() + this_object()->query_str();
    f = this_object()->query_int();
    z = (int)this_object()->query_skill("force", 1);

    my["max_jingli"] = my["magic_points"] / 30 + f * 30;
    if (my["animaout"])
        my["max_jingli"] += my["max_jingli"] * 4 / 10;

    my["max_neili"] = z * 15 + my["con"] * 15;
    if (my["breakup"])
        my["max_neili"] += my["max_neili"] * 4 / 10;
    if (my["class"] == "bonze")
        my["max_neili"] += 500;

    my["max_qi"] = 100;
    my["max_qi"] += (my["age"] - 14) * s * 2 / 3;
    my["max_qi"] += (int)my["max_neili"] / 4;

    if ((x = (int)this_object()->query_skill("taoism", 1)) > 39 &&
        (y = (int)this_object()->query_skill("taiji-shengong", 1)) > 39)
    { // ̫������ϵ�ѧ�ķ�����
        if (x > 350)
            x = (x - 350) / 2 + 350;
        if (y > 350)
            y = (y - 350) / 2 + 350;
        if (x > 200)
            x = (x - 200) / 2 + 200;
        if (y > 200)
            y = (y - 200) / 2 + 200;

        my["max_qi"] += (x + 100) * (y + 100) / 100;
    }
    else if ((x = (int)this_object()->query_skill("bihai-chaosheng", 1)) > 39 &&
             (y = (int)this_object()->query_skill("bibo-shengong", 1)) > 39)
    { // �̲�����ϱ̺�����������
        if (x > 250)
            x = (x - 250) / 2 + 250;
        if (y > 250)
            y = (y - 250) / 2 + 250;
        if (x > 120)
            x = (x - 120) / 2 + 120;
        if (y > 120)
            y = (y - 120) / 2 + 120;

        my["max_qi"] += (x + 100) * (y + 100) / 100;
    }

    if (my["breakup"])
        my["max_qi"] += my["max_qi"];

    my["eff_qi"] = my["max_qi"];
    my["qi"] = my["max_qi"];

    my["max_jing"] = 100;
    my["max_jing"] += (my["age"] - 14) * s * 2 / 3;
    my["max_jing"] += (int)my["max_jingli"] / 4;
    if (my["breakup"])
        my["max_jing"] += my["max_jing"];
    if (my["animaout"])
        my["max_jing"] += my["max_jing"];

    my["eff_jing"] = my["max_jing"];
    my["jing"] = my["max_jing"];
    my["eff_jingli"] = my["max_jingli"];
    my["jingli"] = my["max_jingli"];
    my["neili"] = my["max_neili"];
    my["quest_count"] = me->query("quest_count");

    if (my["combat_exp"] > 800000)
    {
        my["jiali"] = query_skill("force") / 3;
    }
    else
    {
        my["jiali"] = query_skill("force") / 6;
    }
}

void kill_ob(object ob)
{
    if (!is_busy())
        exert_function("powerup");

    ::kill_ob(ob);
}

// �������NPC������ʱ�򣬼���Ƿ���Խ��н�����ҡ�
void die(object killer)
{
    int lvl;        // NPC�ĵȼ�
    int exp;        // ��Ҫ�Ϸֵľ���
    int pot;        // ��Ҫ�Ϸֵ�Ǳ��
    int weiwang;    // ��Ҫ�Ϸֵ�����
    int score;      // ��Ҫ�Ϸֵ�����

    // �ҵ�ɱ����(NPC)���Ǵ����ҵ���
    if (!objectp(killer))
        killer = query_temp("last_opponent");

    lvl = NPC_D->check_level(this_object());
    exp = 15 + random(10) + lvl;
    pot = 10 + random(5) + lvl;
    weiwang = 5 + random(5) + lvl / 2;
    score = 5 + random(5) + lvl / 2;

    if (objectp(killer))
    {
        GIFT_D->delay_bonus(killer, ([
            "exp" : exp + random(4),
            "pot" : pot + random(3),
            "weiwang" : weiwang + random(3),
            "score" : score + random(3),
            "prompt" : "����" + name() + "֮��"
        ]));
    }

    // ��������
    ::die();

    return;
}

int accept_fight(object ob)
{
    command("say �ã����ǾͱȻ��Ȼ���");
    kill_ob(ob);
    return 1;
}

int accept_hit(object ob)
{
    command("say ����ȥ�ɣ�");
    kill_ob(ob);
    return 1;
}

int accept_kill(object ob)
{
    command("say �ߣ�������");
    return 1;
}

void random_move()
{
    NPC_D->random_move(this_object());
}

void init()
{
    object me;

    ::init();
    if (!interactive(me = this_player()))
        return;

    remove_call_out("kill_ob");
    call_out("kill_ob", 0, me);
}
