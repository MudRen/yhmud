// qingliang-jian.c  �������� 
         
inherit SHAOLIN_SKILL; 
mapping *action = ({ 
([      "action" : "$N�ٽ�������������������һʽ�������ů����$w��$n��$l�����ȥ��", 
        "force" : 120, 
        "dodge" : 20, 
        "damage" : 35, 
        "lvl" : 0, 
        "damage_type" : "����" 
]), 
([      "action" : "ͻȻ�佣��һ�£���������һ���׺磬$Nʹ��һʽ��������ˮ�����������ӣ�$wֱ��$n��$l", 
        "force" : 140, 
        "dodge" : 15, 
        "damage" : 50, 
        "lvl" : 10, 
        "damage_type" : "����" 
]), 
([      "action" : "$N��������һ�֣�����$w�����ӳ�һ�С��������𡹣�����ɭȻ����$n��$l��ȥ", 
        "force" : 200, 
        "dodge" : 15, 
        "damage" : 60, 
        "lvl" : 20, 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ���ӿ��м������£���ʽ����ƽƽ���棬������һ���죬ʵ��ʯ���쾪�����ƣ�һ�С��������$w���ش���$n��$l", 
        "force" : 240, 
        "dodge" : 10, 
        "damage" : 70, 
        "lvl" : 30, 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ��$w�԰���к��������������ֱ����һ������һ�㣬һʽ����ˮ���硹���ڽ�ز�������ۻ��ն��$n��$l", 
        "force" : 270, 
        "dodge" : 10, 
        "damage" : 80, 
        "lvl" : 40, 
        "damage_type" : "����" 
]), 
([      "action" : "$N��������һʽ������ء���$w��Ȼһ��������ǧ�������۶�������������$n��$l", 
        "force" : 280, 
        "dodge" : 5, 
        "damage" : 90, 
        "lvl" : 50, 
        "damage_type" : "����" 
]), 
([      "action" : "$N��תһʽ�����両�ࡹ��ٲȻ��ǹ��ꪣ���ɳǧ�$w������������$n���������ؽ���֮��", 
        "force" : 300, 
        "dodge" : 5, 
        "damage" : 110, 
        "lvl" : 60, 
        "damage_type" : "����" 
]), 
([      "action" : "$N�������£�һ�С����Ӱ������$w��Ȼ��תֱ�ϣ�������$n������Ҫ������Χס", 
        "force" : 380, 
        "dodge" : -5, 
        "damage" : 135, 
        "lvl" : 70, 
        "damage_type" : "����" 
]), 
}); 
                 
int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); } 
 
int valid_learn(object me) 
{ 
        if ((int)me->query("max_neili") <       500)  
                return notify_fail("�������������\n"); 
        if ( (int)me->query_skill("shaolin-xinfa", 1) < 50) 
                return notify_fail("��������ķ����̫ǳ��\n"); 
        if ((int)me->query_skill("sword", 1) < 50) 
                return notify_fail("��Ļ������������ǳ��\n"); 
        return 1; 
} 
 
mapping query_action(object me, object weapon) 
{ 
        int i, level; 
        level   = (int) me->query_skill("qingliang-jian",1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)];        
} 
         
int practice_skill(object me) 
{ 
        object weapon; 
 
        if (!objectp(weapon = me->query_temp("weapon")) 
                || (string)weapon->query("skill_type") != "sword") 
                return notify_fail("��ʹ�õ��������ԡ�\n"); 
        if ((int)me->query("qi") < 50) 
                return notify_fail("�����������������������\n"); 
        me->receive_damage("qi", 35); 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"qingliang-jian/" + action; 
} 

