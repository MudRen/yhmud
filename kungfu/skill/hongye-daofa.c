// hongye-daofa.c ��Ҷ���� 
    
inherit SHAOLIN_SKILL; 
  
mapping *action = ({ 
([      "action" : "$N����$w��ӣ�һ�С���ȥ������������һת��һ����$n��$l��ȥ", 
        "force" : 100, 
        "attack" : 10, 
        "dodge" : -10, 
        "parry" : -1, 
        "damage" : 30, 
        "lvl" : 0, 
        "skill_name" : "��ȥ����", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ�С�������¥���������㣬$wһ��һ�ƣ�ƽ�л���$n������", 
        "force" : 130, 
        "attack" : 40, 
        "dodge" : -10, 
        "parry" : 5, 
        "damage" : 58, 
        "lvl" : 20,     
        "skill_name" : "������¥", 
        "damage_type" : "����" 
]), 
([      "action" : "$N�鲽����һ�С��ƴ����¡�������һ������ն��$n", 
        "force" : 160, 
        "attack" : 40, 
        "parry" : 25, 
        "dodge" : -5, 
        "damage" : 80, 
        "lvl" : 40,     
        "skill_name" : "�ƴ�����", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ�С��ζ���ɽ����$w���϶��»���һ���󻡣���ֱ����$n",     
        "force" : 190, 
        "attack" : 55, 
        "dodge" : 5, 
        "parry" : 35, 
        "damage" : 105, 
        "lvl" : 60,     
        "skill_name" : "�ζ���ɽ", 
        "damage_type" : "����" 
]), 
([      "action" : "$N�ಽš��һ�С����Ƕ��ǡ����������У�$w����$n���ؿ�",     
        "force" : 220, 
        "attack" : 60, 
        "dodge" : 10, 
        "parry" : 40, 
        "damage" : 95, 
        "lvl" : 80,     
        "skill_name" : "���Ƕ���", 
        "damage_type" : "����" 
]), 
([      "action" : "$N����$w��ʹ��һ�С���Ҷ�׷ס�������ƬƬ��Ӱ����������$n",   
        "force" : 240, 
        "attack" : 70, 
        "dodge" : 15, 
        "parry" : 55, 
        "damage" : 140, 
        "lvl" : 100, 
        "skill_name" : "�¹�����", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ�С����½��ԡ���ֻ�����쵶����˸�����ص�Ӱ��$n��ȫ��ӿȥ ", 
        "force" : 320, 
        "attack" : 70, 
        "dodge" : 20, 
        "parry" : 60, 
        "damage" : 160, 
        "damage" : 130, 
        "lvl" : 120, 
        "skill_name" : "���½���", 
        "damage_type" : "����" 
]), 
}); 
 
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }       
         
int valid_learn(object me) 
{ 
        if (me->query("max_neili") < 1000) 

                return notify_fail("�������������\n"); 
        if (me->query_skill("hunyuan-yiqi", 1) < 80) 

                return notify_fail("��Ļ�Ԫһ���ڹ����̫ǳ��\n"); 
        if (me->query_skill("blade", 1) < 80) 

                return notify_fail("��Ļ����������̫ǳ��\n"); 
        if (me->query("int") < 24) 
                return notify_fail("����������Բ��㡣\n"); 
        return 1; 
} 
 
string query_skill_name(int level) 
{ 
        int     i; 
        for(i = sizeof(action)-1; i     >= 0; i--) 
        if(level >= action[i]["lvl"]) 
                return action[i]["skill_name"]; 
} 
 
mapping query_action(object me, object weapon) 
{ 
        int     i, level; 
        level   = (int) me->query_skill("hongye-daofa",1); 
        for(i = sizeof(action); i >     0; i--) 
        if(level > action[i-1]["lvl"]) 
                return action[NewRandom(i, 20, level/5)];       
} 
 
int practice_skill(object me) 
{ 
        object weapon; 
        
        if (!objectp(weapon     = me->query_temp("weapon")) 
                || (string)weapon->query("skill_type") != "blade") 
                return notify_fail("��ʹ�õ��������ԡ�\n"); 
        if ((int)me->query("qi") < 50) 
                return notify_fail("���������������Ҷ������\n"); 
        if ((int)me->query("neili")     < 80) 
                return notify_fail("���������������Ҷ������\n"); 
        me->receive_damage("qi", 25); 
        me->add("neili", -40); 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"hongye-daofa/" + action; 
} 

