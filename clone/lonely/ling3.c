#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + YEL "ʥ����" NOR, ({ "shenghuo ling", "shenghuo", "ling" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "��");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "�����̵ģ�����������ҲֵǮ��");
                set("long", NOR + YEL "
����һ�����������ĺ��ƣ�����ȥ�ǽ���������ʵ�ȴ�Ǽ�Ӳ
�ޱȡ��������ƾ�����͸���������������л�����ڣ�ʵ����
����ӳ�⣬��ɫ��á����Ͽ̵��в��ٲ�˹�ģ������ƺ�����
ѧ�йأ�������£�������Ҫ��ϸ�ж�һ�����ܹ�����\n" NOR);
                set("wield_msg", HIR "$N" HIR "��������һƬ�����"
                                 "�����������С�\n" NOR);
                set("unwield_msg", HIR "$N" HIR "����һ�����ѽ�ʥ��"
                                 "���������䡣\n" NOR);
                set("skill", ([
                        "name"         : "shenghuo-ling",
                        "exp_required" : 1500000,
                        "jing_cost"    : 120,
                        "difficulty"   : 80,
                        "max_skill"    : 149,
                        "min_skill"    : 120,
                        "need"         : ([ "sanscrit" : 200 ]),
                ]));
        }
        init_sword(80);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int ap, dp;
        int n;

        ap = me->query_skill("sword");
        dp = victim->query_skill("dodge");

        if (me->query_skill_mapped("sword") != "shenghuo-ling" ||
            me->query_skill("shenghuo-ling", 1) < 100 ||
            ap / 2 + random(ap) < dp)
                return damage_bonus / 2;

        switch (random(3))
        {
        case 0:
                if (! victim->is_busy())
                      victim->start_busy(me->query_skill("sword") / 10 + 4);
                return HIY "$N" HIY "ŭ��һ����ʥ������������һ�㣬�����ζ������𵭵���⣬��"
                       "��$n" HIY "�����ڽ���Ӱ֮�¡�\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n * 2 / 3, me);
                victim->receive_wound("qi", n * 2 / 3, me);
                return  HIY "$N" HIY "�������ʥ����������£��������߰���趯�ž���$n" HIY
                        "���������Ѩ��\n" NOR;

        }
        return damage_bonus;
}