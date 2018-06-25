//luohan-jian �޺����� 
 
#include <ansi.h> 
inherit SHAOLIN_SKILL; 
 
mapping *action = ({ 
([      "action" : "$N�ս�����$wһ�С���ȥ���硹����$n��$l", 
        "force" : 70, 
        "dodge" : 50, 
        "damage" : 40, 
        "lvl"    : 0, 
        "skill_name" : "��ȥ����",  
        "damage_type" : "����" 
]), 
([      "action" : "$Nһ�С������޹⡹������$w���´̳���ֱ��$n��ȥ", 
        "force" : 90, 
        "dodge" : 20, 
        "damage" : 40, 
        "lvl"    : 20, 
        "skill_name" : "�����޹�", 
        "damage_type" : "����" 
]), 
([      "action" : "$N��ǰ����һ��������$wʹ�����������ֱ��$n�ĺ�", 
        "force" : 100, 
        "dodge" : 80, 
        "damage" : 50, 
        "lvl"    : 40, 
        "skill_name" : "�������", 
        "damage_type" : "����" 
]), 
([      "action" : "$N���һ����ʹ�����ľ���ˮ������$wֱ��$n��Ҫ��", 
        "force" : 90, 
        "dodge" : 60, 
        "damage" : 80, 
        "lvl"    : 60, 
        "skill_name" : "�ľ���ˮ", 
        "damage_type" : "����" 
]), 
([      "action" : "ֻ��$N�������е�$w��ʹ����������ա������ֱ��$n", 
        "force" : 90, 
        "dodge" : 70, 
        "damage" : 110, 
        "lvl"    : 80, 
        "skill_name" : "�������", 
        "damage_type" : "����" 
]), 
([      "action" : "$N�������е�$w��ʹ��������Ҷ�䡹��������ֱ��$n", 
        "force" : 120, 
        "dodge" : 60, 
        "damage" : 120, 
        "lvl"    : 100, 
        "skill_name" : "����Ҷ��",  
        "damage_type" : "����" 
]), 
([      "action" : "$Nʹ��������������������$w�������һ����˸����������$n", 
        "force" : 200, 
        "dodge" : 80, 
        "damage" : 140, 
        "lvl"    : 120, 
        "skill_name" : "��������", 
        "damage_type" : "����" 
]), 
([      "action" : "$N����ʹ������֮���塸��Ӱ���١�������$w�����һ������ǵصĴ���$n", 
        "force" : 200, 
        "dodge" : 90, 
        "damage" : 160, 
        "lvl"    : 150, 
        "skill_name" : "����Ӱ���١�", 
        "damage_type" : "����" 
]), 
([      "action" : HIY"$Nʹ���޺�����֮���վ�����������ˮ������$w"HIY"��������һ�����$n "HIY, 
        "force" : 280, 
        "dodge" : 100, 
        "damage" : 180, 
        "lvl"    : 220, 
        "skill_name" : "HIY��������һ��"NOR, 
        "damage_type" : "����" 
]), 
}); 
         
int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }  
 
int valid_learn(object me)  
 
{ 
        if ((int)me->query_skill("fumo-jian", 1) < 80 && (int)me->query_skill("qingliang-jian", 1) < 80)  
                return notify_fail("��ñ����Ⱦ�ͨ��ħ�����������е�һ�ֲ��ܼ���ѧϰ����Ľ�����\n");  
        if ((int)me->query("max_neili") < 650)  
                return notify_fail("�������������\n");  
         
        if ((int)me->query_skill("hunyuan-yiqi",1) < 120)  
                return notify_fail("����ڹ����̫ǳ��\n");  
        
        if (me->query("int") < 22)  
                return notify_fail("����������Բ�����\n"); 
         
        if ((int)me->query_skill("sword",1) < 100) 

                return notify_fail("��Ļ�������������\n");                          
         
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("luohan-jian", 1)) 
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������޺�������\n");  
        return 1;  
}  
string query_skill_name(int level)  
{ 
        int i;  
 
        for(i = sizeof(action) - 1; i >= 0; i--)  
                if(level >= action[i]["lvl"])  
                        return action[i]["skill_name"];  
} 
 
mapping query_action(object me, object weapon)  
{ 
        int i, level;  
 
        level = (int) me->query_skill("luohan-jian", 1);  
        for(i = sizeof(action); i > 0; i--)  
                if(level > action[i-1]["lvl"])  
                        return action[NewRandom(i, 20, level/5)];  
} 
         
int practice_skill(object me)  
{  
        object weapon;  
        if (! objectp(weapon = me->query_temp("weapon")) ||  
            (string)weapon->query("skill_type") != "sword")  
                return notify_fail("������аѽ����ܹ���ϰ�޺�����\n");  
         
        if ((int)me->query("qi") < 70)  
                return notify_fail("��������������޺�����\n");  
 
        if ((int)me->query("neili") < 70)  
                return notify_fail("��������������޺�����\n");  
         
        me->receive_damage("qi", 65);  
        me->add("neili", -62);  
        return 1;  
} 
         
string perform_action_file(string action)  
{  
        return __DIR__"luohan-jian/" + action;  
} 

