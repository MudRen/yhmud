      
inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action": "$Nȫ��εض��𣬰����һ�����һʽ��ӥ��ʽ����Ѹ�͵�ץ��$n��$l", 
        "force" : 200, 
        "attack": 80, 
        "dodge" : 20, 
        "parry" : 30, 
        "damage": 100, 
        "lvl" : 0, 
        "skills_name" : "ӥ��ʽ", 
        "damage_type" : "����" 
]), 
([      "action": "$N����ֱ����˫��ƽ�죬һʽ����ӥʽ����˫צһǰһ��£��$n��$l", 
        "force" : 220, 
        "attack": 100, 
        "dodge" : 50, 
        "parry" : 50, 
        "damage": 110, 
        "lvl" : 100, 
        "skills_name" : "��ӥʽ", 
        "damage_type" : "����" 
]), 
([      "action": "$Nһʽ������צ����ȫ����б��ƽ�ɣ�����һ����˫צ����$n�ļ�ͷ", 
        "force" : 250, 
        "attack": 150, 
        "dodge" : 60, 
        "parry" : 60, 
        "damage": 180, 
        "lvl" : 120, 
        "skills_name" : "����צ", 
        "damage_type" : "����" 
]), 
([      "action": "$N˫צ�����Ͼ٣�ʹһʽ����깴����һ�����ֱ�Ϯ��$n����Ҹ����", 
        "force" : 280, 
        "attack": 180, 
        "dodge" : 15, 
        "parry" : 35, 
        "damage": 240, 
        "lvl" : 140, 
        "skills_name" : "��깴", 
        "damage_type" : "����" 
]), 
([      "action": "$Nȫ�������ǰ��һʽ����ӥʽ������צͻ�������Ȱ�ץ��$n���ؿ�", 
        "force" : 400, 
        "attack": 180, 
        "dodge" : 60, 
        "parry" : 80, 
        "damage": 260, 
        "lvl" : 150, 
        "skills_name" : "��ӥʽ", 
        "damage_type" : "����" 
]), 
([      "action": "$N���ػ��У�һʽ��Ѫӥצ��������Ϯ�����д�Ѩ�����ַ�ץ$n���ɲ�", 
        "force" : 490, 
        "attack": 160, 
        "dodge" : 60, 
        "parry" : 60, 
        "damage": 260, 
        "lvl" : 180, 
        "skills_name" : "Ѫӥצ", 
        "damage_type" : "����" 
]), 
}); 
 
int valid_enable(string usage) { return usage == "claw" || usage == "parry"; } 
         
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("��������צ������֡�\n"); 
         
        if ((int)me->query_skill("buddhism",1) < 250)        

                return notify_fail("��ķ���Ϊ�������޷�ѧ������צ��\n"); 

        if ((int)me->query_skill("force") < 250)        
                return notify_fail("����ڹ���򲻹����޷�ѧ������צ��\n"); 
        
        if (me->query("dex") < 30 || me->query("str") < 30 || me->query("int") < 30 ) 
                return notify_fail("������첻�����޷�ѧ������צ��\n"); 
 
        if ((int)me->query("max_neili") < 2500) 
                return notify_fail("�������̫�����޷���������צ��\n"); 
 
        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yintuoluo-zhua", 1)) 
                return notify_fail("��Ļ���צ�����ˮƽ���ޣ��޷����������������צ��\n");        
         
        return 1; 
} 
 
string query_skill_name(int level) 
{ 
        int i; 
        for(i = sizeof(action)-1; i >= 0; i--) 
                if (level >= action[i]["lvl"]) 
                        return action[i]["skill_name"]; 
} 
         
mapping query_action(object me, object weapon) 
{ 
        int i, level; 
        level = (int) me->query_skill("yintuoluo-zhua",1); 
 
        for(i = sizeof(action); i > 0; i--) 
                if (level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
 
int practice_skill(object me) 
{ 
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("����������ϰ��\n"); 
 
        if ((int)me->query("qi") < 70) 
                return notify_fail("�������̫���ˡ�\n"); 
 
        if ((int)me->query("neili") < 70) 
                return notify_fail("�����������������צ��\n"); 
 
        me->receive_damage("qi", 60); 
        me->add("neili", -60); 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"yintuoluo-zhua/" + action; 
} 
         
         

