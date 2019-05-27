inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action" : "$Nʹ��һ�С������֡���˫�ƺ�ʮ��ֱֱײ��$n��ǰ��", 
        "skill_name" : "������", 
        "force" : 120, 
        "attack": 70, 
        "dodge" : 20, 
        "lvl" : 0, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С������֡�������Ծ��˫���繴��ץ��$n��$l", 
        "skill_name" : "������", 
        "force" : 170, 
        "attack": 80, 
        "dodge" : 20, 
        "lvl" : 25, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С���ĸ�֡���������ָ��ֱȡ$n��$l", 
        "skill_name" : "��ĸ��", 
        "force" : 220, 
        "attack": 60, 
        "dodge" : 20, 
        "lvl" : 50, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С����������֡���ŭ��һ����һ�Ƶ�ͷ����$n��$l", 
        "skill_name" : "����������", 
        "force" : 250, 
        "attack": 80, 
        "dodge" : 30, 
        "lvl" : 80, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С��ȱ��֡����ͳ���ǰ�����������㹥��$n", 
        "skill_name" : "�ȱ���", 
        "force" : 360, 
        "attack": 80, 
        "dodge" : 30, 
        "lvl" : 100, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С���ȴ��֡�����������˫������ɨ��$n��$l", 
        "skill_name" : "��ȴ���", 
        "force" : 550, 
        "dodge" : 70, 
        "lvl" : 180, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С�����֡��������Ծ��˫��ǰ�������ץ��$n���ʺ�", 
        "skill_name" : "�����", 
        "force" : 500, 
        "attack": 120, 
        "dodge" : 80, 
        "lvl" : 140, 
        "damage_type" : "����", 
]), 
([      "action" : "$Nʹ��һ�С������ǻ��֡�����ʱ��������������г���������Ӱ��" 
                   "��$n��$l", 
        "skill_name" : "�����ǻ���", 
        "force" : 500, 
        "attack": 120, 
        "dodge" : 100, 
        "lvl" : 160, 
        "damage_type" : "����", 
]), 
}); 
         
int valid_enable(string usage) { return usage == "hand" || usage == "parry"; } 
         
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("����ȴ��ֱ�����֡�\n"); 
 
        if ((int)me->query("max_neili") < 3500) 
                return notify_fail("�������������\n"); 
 
        if ((int)me->query_skill("force") < 250) 
                return notify_fail("����ڹ����̫ǳ��\n"); 
        
        if ((int)me->query("dex") < 26 || (int)me->query("con") < 26) 
                return notify_fail("������첻�㣬�޷�����ȴ��֡�\n"); 
         
        if ((int)me->query_skill("buddhism", 1) < 200) 
                return notify_fail("��������ķ���֪ʶ�˽�̫�٣��޷�����ȴ��֡�\n"); 
 
        if ((int)me->query_skill("buddhism", 1) < (int)me->query_skill("dacidabei-shou",1) && 
            (int)me->query_skill("buddhism", 1) < 300) 
                return notify_fail("���������ķ�֪ʶ��֪ʶ���ޣ����Խ�һ�������ȴ��֡�\n");        
 
        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("dashou-yin",1)) 
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������Ĵ�ȴ��֡�\n"); 
 
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
                  level   = (int) me->query_skill("dashou-yin",1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
 
int practice_skill(object me) 
{ 
//      object weapon; 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("������ȴ��֡�������֡�\n"); 

        if ((int)me->query("qi") < 100) 
                return notify_fail("������������������˴�ȴ��֡�\n"); 
 
        if ((int)me->query("neili") < 100) 
                return notify_fail("������������������˴�ȴ��֡�\n"); 
 
        me->receive_damage("qi", 60); 
        me->add("neili", -70); 
        return 1; 
} 
         
string perform_action_file(string action) 
{ 
        return __DIR__"dacidabei-shou/" + action; 
} 
