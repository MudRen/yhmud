inherit SHAOLIN_SKILL;  
 
mapping *action = ({  
([      "action" : "$N��һ��������΢��������һ����һ�С����°��졹��һ��ֱ��$n��$l",     
        "force" : 110,  
        "dodge" : 10,  
        "parry" : 10,  
        "attack": 30,  
        "damage": 40,  
        "lvl" : 10,  
        "skill_name" : "���°���",  
        "damage_type" : "����"  
]),  
([      "action" : "$N��������һЦ�������������ϣ�����ƽƽ������һ�С��������졹���������$n",     
        "force" : 130,  
        "dodge" : 20,  
        "parry" : 30,  
        "attack": 30,  
        "damage": 50,  
        "lvl" : 30,  
        "skill_name" : "��������",  
        "damage_type" : "����"  
]),  
([      "action" : "$N��$nһ����ȣ�ʹһ�С����羭�졹�����ƻ������漴���Ƹ��ϣ�������������$n��$l",  
        "force" : 140,  
        "dodge" : 27,  
        "parry" : 43,  
        "attack": 40,  
        "damage": 60,  
        "lvl" : 60,  
        "skill_name" : "���羭��",  
        "damage_type" : "����"  
]), 
([      "action" : "$N�ƺ�һ����˫�����Ϸֿ���һ�ǡ��ٻ����졹���ƻ����ߣ�����ͬʱ����$n��$l",     
        "force" : 160,  
        "dodge" : 37,  
        "parry" : 33,  
        "attack": 54,  
        "damage": 78,  
        "lvl" : 80,  
        "skill_name" : "�ٻ�����",  
        "damage_type" : "����"  
]),  
([      "action" : "$Nʩ����һ�����졹��һ�����һ������������Ʒ�ֱ��$n��$l",  
        "force" : 180,  
        "dodge" : 42,  
        "parry" : 23,  
        "attack": 64,  
        "damage": 89,  
        "lvl" : 110,  
        "skill_name" : "һ������",  
        "damage_type" : "����"  
]),  
([      "action" : "$Nһ����Х��˫�ƽ��������һ�С�ʯ���쾪�����Ʒ��ܲ�$n��ǰ������",     
        "force" : 190,  
        "dodge" : 46,  
        "parry" : 33,  
        "attack": 54,  
        "damage": 93,  
        "lvl" : 140,  
        "skill_name" : "ʯ���쾪",  
        "damage_type" : "����"  
]),  
([      "action" : "$Nŭ��һ������շ���һʽ��������ѡ���˫�ƾӸ����£���������$n",     
        "force" : 200,  
        "dodge" : 43,  
        "parry" : 43,  
        "attack": 55,  
        "damage": 103,  
        "lvl" : 170,  
        "skill_name" : "�������",  
        "damage_type" : "����"  
]),  
([      "action" : "$N�����Ц������������۷��裬һ�С��޷����졹���Ʒ���������������$n",      
        "force" : 210,  
        "dodge" : 33,  
        "parry" : 53,  
        "attack": 58,  
        "damage": 105,  
        "lvl" : 190,  
        "skill_name" : "�޷�����",  
        "damage_type" : "����"  
])  
});  
int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }  
 
int valid_learn(object me)  
{ 
//      object weapon; 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))  
                return notify_fail("������ʯ�ơ�������֡�\n");  
        if (me->query_skill("sanhua-zhang", 1) < 80 && me->query_skill("banruo-zhang", 1) < 80) 
                return notify_fail("��ñ����Ⱦ�ͨɢ���ơ��������е�һ�ֲ��ܼ���ѧϰ������Ʒ���\n");  
 
        if ((int)me->query_skill("force", 1) < 80)  
                return notify_fail("��Ļ����ڹ���򲻹������޷���ϰ��ʯ�ơ�\n");  
         
        if ((int)me->query("max_neili") < 800)  
                return notify_fail("�������̫�����޷�������ʯ�ơ�\n");  
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
 
        level   = (int) me->query_skill("woshi-zhang",1);  
        for(i = sizeof(action); i > 0; i--)  
                if(level > action[i-1]["lvl"])  
                        return action[NewRandom(i, 20, level/5)];  
} 
         
int practice_skill(object me)  
{ 
        if ((int)me->query("qi") < 60)  
                return notify_fail("�������̫�û��������ϰ��ʯ�ơ�\n");  
        if ((int)me->query("neili") < 70)  
                return notify_fail("�������̫��޷�������ϰ��ʯ�ơ�\n");  
        me->add("qi", -55);  
        me->add("neili", -50);  
        return 1;  
} 
 
string perform_action_file(string action)  
{ 
        return __DIR__"woshi-zhang/" + action;  
} 
