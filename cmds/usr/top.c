// top.c

#include <ansi.h>
#include <mudlib.h>

inherit ITEM;

int top_list(object ob1, object ob2);
int get_score(object ob);

void init()
{
    add_action("do_view", "view");
}

int main(string arg)
{
    object *list, *ob, me;
    int i;
    int index = 0;
    string msg, zhuans;

    me = this_player();

    // ��ֹϵͳ��Դ���Ĺ�����ʱ�����
    if (!wizardp(me) && time() - me->query_temp("last_view") < 60)
        return notify_fail(HIW "\nͻȻ��Ӣ�۱���һ���⻪������ʹ��"
                               "���Ա�����ϵ��ּ���\n" NOR);

    ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
    list = sort_array(ob, (: top_list :));

    msg = HIW "\n            ��������" HIG " Ӣ �� �� " HIW "��������\n";
    msg += "���������ө��ߩ����������������ө����ߩ��ө���������\n";
    msg += "�� " HIG "����" HIW " ��    " HIG "��        ��" HIW
           "    �� " HIG "��  ��" HIW " �� " HIG "��  ��" HIW " ��\n";
    msg += "�ĩ������ة��������������������ة��������ة���������\n";

    for (i = 0; i < 10; i++)
    {
        if (i >= sizeof(list) || list[i]->query("id") == 0 || get_score(list[i]) < 10) //ivy
        {
            msg += HIW "��        ��ʱ��ȱ              ��             -  ��\n" NOR;
            continue;
        }
        if (list[i]->query("name") == me->query("name"))
            index = i + 1;
        if (list[i]->query("reborn/count"))
            zhuans = "*";
        else
            zhuans = "";
        msg += sprintf(HIW "��" HIG "  %-5s %-22s%-10s %5d  " HIW "��\n" NOR,
                       chinese_number(i + 1),
                       list[i]->query("name") + "(" +
                           capitalize(list[i]->query("id")) + ")" + zhuans,
                       list[i]->query("family") ? list[i]->query("family/family_name") : "��������",
                       get_score(list[i]));
    }
    if (index == 0)
        for (i = 10; i < sizeof(list); i++)
        {
            if (list[i]->query("name") == me->query("name"))
            {
                index = i + 1;
                break;
            }
        }

    msg += HIW "����������������������������������������������������\n" NOR;
    msg += HIG + NATURE_D->game_time() + "�ǡ�\n" NOR;
    msg += WHT "Ӣ�۱�������һ��С�ֿ��ţ�" + me->query("name") + "��Ŀǰ���� " +
           get_score(me);
    if (index)
    {
        msg += "�����е�" + chinese_number(index) + "��\n" NOR;
    }
    else
    {
        msg += "��\n" NOR;
    }

    write(msg);
    me->set_temp("last_view", time());
    return 1;
}

int top_list(object ob1, object ob2)
{
    int score1, score2;

    score1 = get_score(ob1);
    score2 = get_score(ob2);

    return score2 - score1;
}

int get_score(object ob)
{
    //int tlvl, i, score;
    int tlvl, score;
    //string *ski;
    //mapping skills;

    reset_eval_cost();

    /*
        //ȡ�����ܵļӷ�Ȩ�أ�ʹ���ָ��Ӻ�������ϵͳ����
        skills = ob->query_skills();

        if (! sizeof(skills))
                return 1;

        ski  = keys(skills);
        for(i = 0; i < sizeof(ski); i++)
        {
                tlvl += skills[ski[i]];
        }
        score = tlvl / 15;
        */
    //��������dodge,parry,force,martial-cognize
    tlvl = (int)ob->query_skill("force", 1) + (int)ob->query_skill("dodge", 1) + (int)ob->query_skill("parry", 1) + (int)ob->query_skill("martial-cognize", 1);
    score = tlvl;
    score += ob->query("max_neili") / 30;
    score += ob->query("max_jingli") / 30;
    score += ob->query_str() +
             ob->query_int() +
             ob->query_dex() +
             ob->query_con() - 80;
    score += (int)ob->query("combat_exp") / 5000;
    return score;
}
