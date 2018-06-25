//longxing-jian.c 
inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action" : "$Nʹһ�С��������Ρ�����$wһ�ᣬ����$n��$l", 
        "damage" : 40, 
        "parry": 40, 
        "force": 150, 
        "damage_type" : "����", 
        "skill_name" : "��������" 
]), 
([      "action": "$Nʹ�����������졹������΢��,����$wٿ����$n��$l��ȥ", 
        "damage" : 50, 
        "dodge": 80, 
        "parry": 10, 
        "force": 250, 
        "damage_type": "����", 
        "skill_name" : "��������" 
]), 
([      "action": "$N����΢�������㷴�ߣ�����ת��ʹһ�С��������ѡ�������$w�Ѵ���$n$l", 
        "damage" : 60, 
        "dodge": 80, 
        "parry": 20, 
        "force": 250, 
        "damage_type": "����", 
        "skill_name" : "��������" 
]), 
([      "action" : "$Nʹһʽ���������֡�����������һ��,$w�ӹ����ʺ�,����$n�������", 
        "damage" : 170, 
        "force" : 450, 
        "dodge" : 90, 
        "lvl" : 100, 
        "damage_type" : "����", 
        "skill_name" : "��������" 
]), 
([      "action": "$N�����ڵ���һ���,ʹһ�С������ڿա�,��$n�������,����$wֱ��$n", 
        "damage" : 180, 
        "dodge": 80, 
        "parry": 70, 
        "force": 350, 
        "damage_type": "����", 
        "skill_name" : "�����ڿ�" 
]), 
([      "action": "$N˫��һ����������ݣ�һ�С����ɷ��衹����ץ��$n�ҽ����ף�����$wֱ��$nС��",   
        "dodge": 80, 
        "damage" : 80, 
        "parry": -10, 
        "force": 400, 
        "damage_type": "����", 
        "skill_name" : "���ɷ���" 
]), 
([      "action": "$NͻȻһ���������һ�С����ཱུ������˫��һ�֣����ڼ�ͷ��˫��ֱ��$n", 
        "dodge": 90, 
        "damage" : 90, 
        "parry": 30, 
        "force": 400, 
        "damage_type": "����", 
        "skill_name" : "���ཱུ��" 
]), 
}); 
 
int valid_enable(string usage) { return usage=="sword"|| usage=="staff"|| usage=="parry"; } 
 
int valid_learn(object me) 
{ 
        if (me->query("str") < 24) 
                return notify_fail("������������㡣\n"); 
 
        if (me->query("int") < 30) 
                return notify_fail("���������Բ��㡣\n"); 
 
        if ((int)me->query("max_neili") < 2000) 
                return notify_fail("���������Ϊ�����������������ν�����\n"); 
 
        if ((int)me->query_skill("hunyuan-yiqi",1) < 200) 
                return notify_fail("����ڹ����̫ǳ�������������ν�����\n"); 
         
        if ((int)me->query_skill("sword", 1) < 200) 
                return notify_fail("��Ľ����������㣬�����������ν�����\n"); 
 
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("longxing-jian", 1)) 
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�������������ν�����\n"); 
         
        return 1; 
} 
         
mapping query_action(object me, object weapon) 
{ 
        return action[random(sizeof(action))]; 
} 
 
string query_skill_name(int level) 
{ 
        int i; 
        for (i = sizeof(action) - 1; i >= 0; i--) 
                if (level >= action[i]["lvl"]) 
                        return action[i]["skill_name"]; 
} 
         
int practice_skill(object me) 
{ 
        if ((int)me->query("qi") < 50) 
                return notify_fail("�������̫���ˡ�\n"); 
        if ((int)me->query("neili") < 50) 
                return notify_fail("����������������ν�����\n"); 
        me->add("qi", -30); 
        me->add("neili", -40); 
        return 1; 
} 
         
string perform_action_file(string action) 
{ 
        return __DIR__"longxing-jian/" + action; 
} 
         
         

