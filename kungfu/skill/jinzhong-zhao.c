// jingang-buhuaiti.c
// Created by Doing

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 350)
                return notify_fail("����ڹ���򲻹���������ϰ����񹦡�\n");
                
        if (me->query("con") < 33)
                return notify_fail("����������̫���ˣ�������ϰ����񹦡�\n");        

        if (me->query("str") < 33)
                return notify_fail("����������̫���ˣ�������ϰ����񹦡�\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("�����������������ϰ����񹦡�\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("jinzhong-zhao", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷���������Ľ����֡�\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        //int ap, dp, mp;
        int ap, dp;
        int cost; 
        //string msg;

        if ((int)me->query_skill("jinzhong-zhao", 1) < 150 || (int)me->query("neili") < 400 || ob->query_temp("weapon") || ! living(me) || ! me->query_temp("jinzhongzhao"))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        //mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (dp / 2 + random(dp) > ap)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(5))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "���˷�����һ����������ֱ��$N"
                                            HIG "���������мܣ������˺�\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIY "ֻ��$N" HIY "����$n�����Ȼһ�г�$n"
                                            HIY "�ĺ�����ȥ�������Ϸ�������������\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "����$n����������������ȫ��һ������$n" HIW "���ϣ���"
                                            "�������ϵ���һ����ǽֱײ\n��������$N�Ĺ���Ӳ�����ص�����\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "$N" HIC "һ������$n" HIC "���ϣ��ɼ�$n"
                                            HIC "�������ܣ�ֻ��ȫ��Ѹ��һ����$N" HIC "�����������������������"
                                            "������\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" MAG "��$N�������׹����������������һЦ������һԾ"
                                            MAG "ֱ��$N������ײȥ������\n$N������������Ǳ�����!\n" NOR]);
                        break;
                }
                return result;
        } 

}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jinzhong-zhao", 1);
        if (lvl < 100) return 0;
        if (lvl < 150) return 20;
        if (lvl < 200) return 30;
        if (lvl < 250) return 40;
        if (lvl < 300) return 50;
        if (lvl < 350) return 60;
        if (lvl < 400) return 80;
        if (lvl < 480) return 90;
        if (lvl < 500) return 100;
        return 120;
}

int practice_skill(object me)
{
        if (me->query_skill("jinzhong-zhao", 1) < 100)
                return notify_fail("������Ż����񹦵��˽���ǳ�������������ж�����\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("jing") < 100)
                return notify_fail("�������̫���ˡ�\n");


        if ((int)me->query("neili") < 120)
                return notify_fail("������������������֡�\n");

        me->receive_damage("jing", 100);
        me->add("neili", -100);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinzhong-zhao/" + action;
}

