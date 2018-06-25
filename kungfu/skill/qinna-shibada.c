
//����ʮ�˴� 
 
inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([  "action" : "$N��һ��������΢��������һ����һ�С����°��졹����צ��ȭֱͱ$n��$l", 
        "force" : 170, 
        "dodge" : 0, 
        "parry" : 10, 
        "lvl" : 0, 
        "skill_name" : "���°���", 
        "damage_type" : "����" 
]), 
([  "action" : "$N��������һЦ����ȭ�������ϣ������������ƣ�һ�С��������졹���������$n", 
        "force" : 200, 
        "dodge" :-5, 
       "parry" : 5, 
        "lvl" : 15, 
        "skill_name" : "��������", 
        "damage_type" : "����" 
]), 
([  "action" : "$N��$nһ����ȣ�ʹһ�С����羭�졹����ȭ�������ҽ�ͬʱ�����$l", 
        "force" : 230, 
        "dodge" : 0, 
       "parry" : 10, 
        "lvl" : 30, 
        "skill_name" : "���羭��", 
        "damage_type" : "����" 
]), 
([      "action" : "$N�ƺ�һ����˫ȭ���Ϸֿ���һ�ǡ��ٻ����졹��ȭ�����ߣ�����ͬʱ����$n��$l", 
        "force" : 260, 
        "dodge" : 0, 
       "parry" : 0, 
        "lvl" : 45, 
        "skill_name" : "�ٻ�����", 
        "damage_type" : "����" 
]), 
([  "action" : "$Nʩ����������졹��������մ����ֱ��$n��$l", 
        "force" : 290, 
        "dodge" : 0, 
        "parry" : 5, 
        "lvl" : 60, 
        "skill_name" : "һ������", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ����Х��˫ȭ���������һ�С�ʯ���쾪����ȭ���ܲ�$n��ǰ������", 
        "force" : 310, 
        "dodge" : 10, 
       "parry" : 10, 
        "lvl" : 70, 
        "skill_name" : "ʯ���쾪", 
        "damage_type" : "����" 
]), 
([      "action" : "$Nŭ��һ������շ���һʽ��������ѡ���˫ȭ�Ӹ����£����봷��$n", 
        "force" : 350, 
        "dodge" : 20, 
       "parry" : -10, 
        "lvl" : 80, 
        "skill_name" : "�������", 
        "damage_type" : "����" 
]), 
([  "action"    : "$N�����Ц������������۷��裬һ�С��޷����졹���������ã���������$n��ȥ", 
        "force" : 380, 
        "dodge" : -5, 
       "parry" : -10, 
        "lvl" : 90, 
        "skill_name" : "�޷�����", 
        "damage_type" : "����" 
]) 
}); 
int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; } 
int valid_combine(string combo) { return combo=="luohan-quan"; } 
 
         
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("��������ʮ�˴򡹱�����֡�\n"); 
    /*    if ((int)me->query_skill("hunyuan-yiqi", 1) < 100)      
                return notify_fail("��Ļ�Ԫһ���ȼ��������޷�ѧ������ʮ�˴򡹡�\n");*/
        if ((int)me->query("max_neili") < 1000) 
                return notify_fail("�������̫�����޷���������ʮ�˴򡹡�\n"); 
        
        if ((int)me->query_skill("unarmed",1) < 100) 
                return notify_fail("��Ļ���ȭ��̫�����޷���������ʮ�˴򡹡�\n");
        
      /*  if ((int)me->query_skill("hunyuan-yiqi", 1)< 100)
                return notify_fail("�����һ����Ԫ��̫�����޷���������ʮ�˴򡹡�\n");  */
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
        if (( (int)me->query_skill("unarmed", 1) >= 120 ) 
                &&  ( (int)me->query_skill("qinna-shibada", 1) >= 120 ) 
                && ( (int)me->query_skill("cuff",1) >= 120 ) 
                && ( (int)me->query_skill("luohan-quan", 1) >= 120 ) 
                && ( (int)me->query("neili") >= 500 ) 
                &&  (me->query_skill_prepared("cuff") == "luohan-quan") 
                && (me->query_skill_mapped("unarmed") == "qinna-shibada")       
                && random(10) > 8       ) 
        {       
                return ([ 
                        "action": "$N������ʽͻȻ�ӿ죬һ�С�����˫������������$n����һȭ���漴˫����������", 
                                "parry":(int)me->query_skill("parry")/8,        
                        "dodge":(int)me->query_skill("dodge") / 20      + (int)me->query_skill("unarmed") / 15,   
                        "force": (int)me->query_skill("cuff") + (int)me->query_skill("unarmed"), 
                        "damage_type": "����" 
                        ]); 
        } 
         
        level   = (int) me->query_skill("qinna-shibada",1);     
                for(i = sizeof(action); i > 0; i--) 
                        if(level > action[i-1]["lvl"]) 
                                return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
        if ((int)me->query("neili") < 50)
                return notify_fail("�������̫���ˡ�\n");
                if ((int)me->query("qi") < 50)
                return notify_fail("�������������������ʮ�˴򡹡�\n");
                me->add("neili", -35);
                me->add("qi", -40);
                return 1; 
} 

