// huashan-jian.c
// Modified by Venus Oct.1997
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "name"  : "�з�����",
        "action": "$Nʹһ�С��з����ǡ�������$w���Ⱪ������$n��$l��ȥ",
        "force" : 70,
		"attack": 10,
		"parry" : 5,
        "dodge" : 10,
        "damage": 30,
        "lvl"   : 0,
        "damage_type":  "����"
]),
([      "name"  : "�ޱ���ľ",
        "action": "$N������ת��һ�С��ޱ���ľ������$n��$l",
        "force" : 120,
		"attack": 20,
		"parry" : 15,
        "dodge" : 20,
        "damage": 40,
        "lvl"   : 20,
        "damage_type":  "����"
]),
([      "name"  : "���ڤڤ",
        "action": "$N�趯$w��һ�С����ڤڤ��Ю�������������$n��$l",
        "force" : 160,
		"attack": 25,
		"parry" : 20,
        "dodge" : 30,
        "damage": 45,
        "lvl"   : 40,
        "damage_type":  "����"
]),
([      "name"  : "ƽɳ����",
        "action": "$N����$w����һ����������ƽɳ���㡹��$n��$l�̳�����",
        "force" : 190,
		"attack": 30,
		"parry" : 28,
        "dodge" : 35,
        "damage": 50,
        "lvl"   : 60,
        "damage_type":  "����"
]),
([      "name"  : "��������",
        "action": "$N����$w���Ⱪ����һ�С��������á���$n$l��ȥ",
        "force" : 220,
		"attack": 40,
		"parry" : 33,
        "dodge" : 40,
        "damage": 55,
        "lvl"   : 80,
        "damage_type":  "����"
]),
([      "name"  : "�׺����",
        "action": "$N����$w����һ���⻡��ֱָ$n$l��һ�С��׺���ա���������������ȥ",
        "force" : 260,
		"attack": 50,
		"parry" : 40,
        "dodge" : -20,
        "damage": 90,
        "lvl"   : 100,
        "damage_type":  "����"
]),
([      "action": " "RED" ��ɽ����֮���� "NOR"",
        "force"  : (int)this_player()->query_skill("force", 1)/2 + random((int)this_player()->query_skill("force", 1)),
        "attack" : (int)this_player()->query_skill("sword", 1)/4 + random((int)this_player()->query_skill("sword", 1)/2),
        "dodge"  : (int)this_player()->query_skill("dodge", 1)/6 + random((int)this_player()->query_skill("force", 1)/3),
        "parry"  : (int)this_player()->query_skill("parry", 1)/6 + random((int)this_player()->query_skill("parry", 1)/3),
        "damage" : (int)this_player()->query_skill("force", 1)/4 + random((int)this_player()->query_skill("sword", 1)/2),
        "lvl"    : 200,
        "skill_name" : "����",
        "damage_type": "����"
]),
});

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_neili") < 100)
        return notify_fail("�������������û�а취����ɽ������\n");

    if (! (ob = me->query_temp("weapon"))
    ||  (string)ob->query("skill_type") != "sword" )
        return notify_fail("���������һ�ѽ�����ѧϰ������\n");

    if (me->query_skill("sword", 1) < me->query_skill("huashan-jian", 1))
	return notify_fail("��Ļ�������������ޣ��޷���������Ļ�ɽ������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level = (int) me->query_skill("huashan-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("�������̫�ͣ�û�а취��ϰ��ɽ������\n");
                
    if ((int)me->query("neili") < 40)
        return notify_fail("�������������û�а취��ϰ��ɽ������\n");

    me->receive_damage("qi", 50);
    me->add("neili", -31);
    return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

//������ϼ����
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvlh, lvlk, lvlz;
        object weapon = me->query_temp("weapon");

        lvlh = me->query_skill("huashan-jian", 1);
		lvlk = me->query_skill("kuangfeng-jian", 1);
		lvlz = me->query_skill("zixia-shengong", 1);

        if (damage_bonus < 100
           || lvlh < 300
		   || lvlk < 300
		   || lvlz < 300
           || random(2)
           || me->query("neili") < 500
           || me->query_skill_mapped("sword") != "huashan-jian" 
		   || me->query_skill_mapped("parry") != "kuangfeng-jian" 
		   || me->query_skill_mapped("force") != "zixia-shengong" )
      		return damage_bonus / 4;

        if (random(lvlh / 2) + random(lvlk / 2) + random(lvlz / 2) > victim->query_skill("force", 1))
        {
                me->add("neili", -60);
                victim->receive_wound("qi", damage_bonus * 4 / 5, me);
      
                return HIW "$N" HIW "����" + weapon->name() + MAG "ͻȻ��ɫ�����ŷ�,��������"
                       "��$n" MAG "��ȥ��\n" NOR;
         }
}

string perform_action_file(string action)
{
        return __DIR__"huashan-jian/" + action;
}
