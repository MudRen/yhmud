         
#include <ansi.h> 
         
inherit SKILL; 
         
mapping *action = ({ 
([      "action" : "$N�����鰴������ʹһ�С�һ�����졹����$n��$l��ȥ", 
        "attack" : 30, 
        "force"  : 70, 
        "dodge"  : 42, 
        "parry"  : 99, 
        "damage" : 22, 
        "skill_name" : "һ������", 
        "lvl" : 0, 
        "damage_type" : "����" 
]), 
([      "action" : "$N�������������ʹһ�С�������ȸ������$n��$lϮȥ", 
        "attack" : 40, 
        "force" : 85, 
        "dodge" : 81, 
        "parry" : 102, 
        "damage" : 42, 
        "skill_name" : "������ȸ", 
        "lvl" : 30, 
        "damage_type" : "����" 
]), 
([      "action" : "$Nʹһ�С�ֱ��ȭ�������ֻس�����ȭ��$n��$lֱ����ȥ", 
        "attack" : 50, 
        "force" : 100, 
        "dodge" : 88, 
        "parry" : 105, 
        "damage" : 44, 
        "skill_name" : "ֱ��ȭ", 
        "lvl" : 140, 
        "damage_type" : "����" 
]), 
([      "action" : "$N���طֿ������������£�һ�С�˫����������$n��$l�����Ŵ�ȥ", 
        "attack" : 30, 
        "force" : 125, 
        "dodge" : 86, 
        "parry" : 119, 
        "damage" : 45, 
        "skill_name" : "˫����", 
        "lvl" : 160, 
        "damage_type" : "����" 
]), 
([      "action" : "$N��������ǰ���£��ұ�΢����ʹһ�С���ħʽ������$n��$l��ȥ", 
        "attack" : 56, 
        "force" : 150, 
        "dodge" : 94, 
        "parry" : 115, 
        "damage" : 52, 
        "skill_name" : "��ħʽ", 
        "lvl" : 180, 
        "damage_type" : "����" 
]), 
([      "action" : "$N˫�ֻ��գ�һʽ�������֡�����$n��$l��ȥ", 
        "attack" : 54, 
        "force" : 185, 
        "dodge" : 102, 
        "parry" : 122, 
        "damage" : 83, 
        "skill_name" : "������", 
        "lvl" : 200, 
        "damage_type" : "����" 
]), 
([      "action" : "$N��������ڳ���������ֱ���ұ�΢����ʹһ�С���ħȭ������$n��$l�����Ŵ�ȥ", 
        "attack" : 70, 
        "force" : 215, 
        "dodge" : 132, 
        "damage" : 82, 
        "skill_name" : "��ħȭ", 
        "lvl" : 220, 
        "damage_type" : "����" 
]), 
([      "action" : "$N˫���쿪���С����ʽ������$n�������¶�������������Ӱ֮��", 
        "attack" : 81, 
        "force" : 260, 
        "dodge" : 154, 
        "parry" : 145, 
        "damage" : 92, 
        "skill_name" : "���ʽ", 
        "lvl" : 230, 
        "damage_type" : "����" 
]), 
([      "action" : "$N˫����ȭ�������͵���ǰ�Ƴ���һ�С���ħʽ����ֱ��$n���Ѷ�ȥ", 
        "attack" : 90, 
        "force" : 285, 
        "dodge" : 166, 
        "parry" : 175, 
        "damage" : 100, 
        "skill_name" : "��ħʽ", 
        "lvl" : 240, 
]), 
([      "action" : "$N������𣬰����˫ȭ����������һ�С�������ħ����һ�ɾ���ֱ��$n", 
        "attack" : 120, 
        "force" : 340, 
        "dodge" : 178, 
        "parry" : 185, 
        "damage" : 120, 
        "skill_name" : "������ħ", 
        "lvl" : 250, 
        "damage_type" : "����" 
]), 
}); 
 
int valid_enable(string usage) { return usage == "unarmed" || usage == "parry";        } 
 
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("�����ķ�ħ��������֡�\n"); 
 
        if (me->query("str") < 30) 
                return notify_fail("������������㣬�޷��������ķ�ħ����\n"); 

        if ((int)me->query_skill("force") < 280) 
                return notify_fail("����ڹ���򲻹����޷�ѧ���ķ�ħ����\n"); 
 
        if ((int)me->query("max_neili") < 1800) 
                return notify_fail("�������̫�����޷������ķ�ħ����\n"); 
         
        if ((int)me->query_skill("ruying-suixingtui", 1) < 160) 
                return notify_fail("�����Ӱ�����Ȼ�򲻹����޷�ѧ���ķ�ħ����\n"); 
        if ((int)me->query_skill("unarmed", 1) < 120) 
                return notify_fail("��Ļ���ȭ�Ż�򲻹����޷�ѧ���ķ�ħ����\n"); 
 
        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jiasha-fumogong", 1)) 
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷�������������ķ�ħ����\n"); 
 
        if ((int)me->query_skill("ruying-suixingtui", 1) < (int)me->query_skill("jiasha-fumogong", 1)) 
                return notify_fail("�����Ӱ������ˮƽ���ޣ��޷�������������ķ�ħ����\n"); 
 
        return 1; 
} 
 
string query_skill_name(int level) 
{ 
        int i; 
        for (i = sizeof(action)-1; i >= 0; i--) 
                if (level >= action[i]["lvl"]) 
                        return action[i]["skill_name"]; 
} 
 
mapping query_action(object me, object weapon) 
{ 
        int i, level; 
        level = (int) me->query_skill("jiasha-fumogong", 1); 
        for (i = sizeof(action); i > 0; i--) 
                if (level > action[i - 1]["lvl"]) 
                        return action[NewRandom(i, 5, level / 5)]; 
} 
 
varargs mixed hit_ob(object me, object victim, int damage_bonus)  
{ 
        int lvl;  
 
        lvl = me->query_skill("jiasha-fumogong", 1);  
 
        if (damage_bonus < 150  
            || lvl < 180  
            || me->query("neili") < 300  
            || me->query_temp("weapon")  
            || me->query_temp("secondary_weapon")  
            || me->query_skill_mapped("force") != "yijinjing"  
            || me->query_skill_prepared("unarmed") != "jiasha-fumogong")  
                return 0;  
        {  
                me->add("neili", -30);  
                victim->receive_wound("qi", (damage_bonus - 100) / 4, me);  
                return HIY "$N" HIY "�����ʹߣ�ͻȻ��һ�ɻ���ޱȵĵ�����"  
                       HIY "͸����룬ֻ��$nһ���ƺߣ�\n" NOR;  
        } 
} 
         
int practice_skill(object me) 
{ 
        if ((int)me->query("qi") < 70) 
                return notify_fail("�������̫���ˡ�\n"); 
 
        if ((int)me->query("neili") < 70) 
                return notify_fail("����������������ķ�ħ����\n"); 
 
        me->receive_damage("qi", 65); 
        me->add("neili", -59); 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"jiasha-fumogong/" + action; 
} 

 

