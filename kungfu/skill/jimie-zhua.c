// jimie-zhua.c ����צ 
 
inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action" : "$Nȫ��εض���һʽ���������ҡ���˫צѸ�͵�ץ��$n��$l", 
        "force" : 100, 
        "parry" : 5, 
        "lvl" : 0, 
        "skills_name" : "��������", 
        "damage_type" : "����" 
]), 
([      "action" : "$N���һ��������������ץ��һʽ��������Ե����˫צץ��$n��ͷ�����ز�", 
        "force" : 120, 
        "parry" : 10, 
        "lvl" : 10, 
        "skills_name" : "������Ե", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһʽ���һ����ơ���˫�ƻ�ָ����ʱ�䣬һ�����ͱ��˵���������$n", 
        "force" : 80, 
        "parry" : 10, 
        "lvl" : 20, 
        "skills_name" : "�һ�����", 
        "damage_type" : "����" 
]), 
([      "action" : "$N˫צ����һʽ���ն�����������������ֱ�Ϯ��$n����Ҹ����", 
        "force" : 220, 
        "parry" : 15, 
        "lvl" : 30, 
        "skills_name" : "�ն�����", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһʽ�����Ǿۻ᡹����צͻ������צ������˫צ�����ץ��$n���ؿ�", 
        "force" : 180, 
        "parry" : 20, 
        "lvl" : 40, 
        "skills_name" : "���Ǿۻ�", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nԭ�ز�����һʽ�����ݴ��͡���ֻ��$nϮ����˫צϮ��$n���д�Ѩ���ɲ�", 
        "force" : 230, 
        "parry" : 25, 
        "lvl" : 50, 
        "skills_name" : "���ݴ���", 
        "damage_type" : "����" 
]), 
([      "action" : "$N��˫צ�����������ƿն�������һʽ�������޷졹��Ѹ���ޱȵػ���$n", 
        "force" : 260, 
        "parry" : 30, 
        "lvl" : 55, 
        "skills_name" : "�����޷�", 
        "damage_type" : "����" 
]), 
([      "action" : "$N�ڿո߷����ɣ�һʽ�������Ƶء���һʱ����г�������$N����Ӱ����$n", 
        "force" : 190, 
        "parry" : 40, 
        "lvl" : 60, 
        "skills_name" : "�����Ƶ�", 
        "damage_type" : "����" 
]) 
}); 
 
int valid_enable(string usage) { return usage=="claw" || usage=="parry"; } 
 
//int valid_combine(string combo) { return combo=="mohe-zhi"; } 
 
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("������צ������֡�\n"); 
        if ((int)me->query("max_neili") < 600) 
                return notify_fail("�������̫�����޷�ѧϰ����צ��\n"); 
        return 1;
} 
 
string query_skill_name(int level) 
{ 
        int i; 
        for(i = sizeof(action)-1; i >= 0; i--) 
                if(level >= action[i]["lvl"]) 
                        return action[i]["skill_name"]; 
} 
 
mapping query_action(object me, object weapon) 
{ 
        int i, level; 
        level   = (int) me->query_skill("jimie-zhua",1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
 
int practice_skill(object me) 
{ 
        if ((int)me->query("qi") < 50) 
                return notify_fail("�������̫���ˡ�\n"); 
        if ((int)me->query("neili") < 40) 
                return notify_fail("�����������������צ��\n"); 
        me->add("qi", -40); 
        me->add("neili", -30); 
        return 1; 
} 
string perform_action_file(string action)
{
        return __DIR__"jimie-zhua/" + action;
}

