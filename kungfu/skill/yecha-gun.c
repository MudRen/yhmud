#include <ansi.h>  
inherit SHAOLIN_SKILL;  
 
mapping *action = ({  
([      "action": "$N�������࣬���ž��ǽ�����ʽ������$wһ����������ͷ�����س���$n����",    
        "dodge" : 30,  
        "attack": 33,  
        "force" : 89,  
        "damage": 34,  
        "parry" : 35,  
        "lvl" : 0,  
        "damage_type": "����"  
]), 
([      "action": "$N�㡢��������ɨ��������������Ƽ�Ϊ����������һ�Ź�Ӱ��������$n",  
        "dodge" : 35,  
        "attack": 33,  
        "force" : 116,  
        "damage": 52,  
        "parry" : 44,  
        "lvl" : 30,  
        "damage_type": "����"  
]), 
([      "action": "$N������Ц���������������$w������ֱϮ����������$n$l",  
        "dodge" : 48,  
        "attack": 48,  
        "force" : 136,  
        "damage": 78,  
        "parry" : 40,  
        "lvl" : 60,  
        "damage_type": "����"  
]), 
([      "action": "$N���һ��������$w�߸߾��𣬹��ŷ�����ͷ����������$n��$l",  
        "dodge" : 40,  
        "attack": 58,  
        "force" : 200,  
        "damage": 100,  
        "parry" : 22,  
        "lvl" : 90,  
        "damage_type": "����"  
]),  
([      "action": "$N������ǰ������$w��Ȼ�ӽ���ɲ�Ǽ����ʮ������Ӱ��������裬�������ƹ���$n��$l",  
        "dodge" : 36,  
        "attack": 66,  
        "force" : 234,  
        "damage": 101,  
        "parry" : 31,  
        "lvl" : 120,  
        "damage_type": "����"  
]), 
([      "action": "$N����Ծ������$wת���糵��һ�㣬һ��������ֱ��$n����",  
        "dodge" : 35,  
        "attack": 80,  
        "force" : 273,  
        "damage": 104,  
        "parry" : 35,  
        "lvl" : 150,  
        "damage_type": "����"  
]),  
});  
 
int valid_enable(string usage)  
{ 
        return usage == "parry" || usage == "club";  
} 
 
int valid_learn(object me)  
{ 
        object weapon;  
         
        if (! objectp(weapon = me->query_temp("weapon")) ||  
            (string)weapon->query("skill_type") != "club")  
                return notify_fail("���������һ�����Ӳ�����ҹ�������\n");  
 
        if ((int)me->query("max_neili") < 500)  
                return notify_fail("����������㣬��������ҹ�������\n");  
        
        if (me->query("dex") < 22)      
                return notify_fail("����������Բ��㣬��������ҹ�������\n");  
              
        if ((int)me->query_skill("force") < 100)  
                return notify_fail("����ڹ����̫ǳ����������ҹ�������\n");  
         
        if ((int)me->query_skill("club", 1) < 100)  
                return notify_fail("��Ļ����������̫ǳ����������ҹ�������\n");  
 
        if ((int)me->query_skill("club", 1) < (int)me->query_skill("yecha-gun",       1))  
                return notify_fail("��Ļ�������ˮƽ�������޷����������ҹ�������\n");  
        return 1;  
} 
 
string query_skill_name(int level)  
{  
        int i;  
        for (i = sizeof(action) - 1; i >= 0; i--)  
                if (level >= action[i]["lvl"])  
                        return action[i]["skill_name"];  
} 
mapping query_action(object me, object weapon)  
{ 
        int i, level;  
        level = (int) me->query_skill("yecha-gun",1);  
        for (i = sizeof(action); i > 0; i--)  
                if (level > action[i-1]["lvl"])  
                        return action[NewRandom(i, 20, level / 5)];  
} 
 
int practice_skill(object me)  
{ 
        object weapon;  
 
        if (! objectp(weapon = me->query_temp("weapon"))  
                || (string)weapon->query("skill_type") != "club")  
               return notify_fail("��ʹ�õ��������ԡ�\n");  
 
        if ((int)me->query("qi") < 70)  
               return notify_fail("�������������\n");  
 
        if ((int)me->query("neili") < 60)  
               return notify_fail("�������������\n");  
 
        me->receive_damage("qi", 55);  
        me->add("neili", -45);  
        return 1;  
}  
         
string perform_action_file(string action)  
{  
        return __DIR__"yecha-gun/" + action;  
} 

