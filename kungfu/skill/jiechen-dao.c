
#include <ansi.h> 
inherit SHAOLIN_SKILL; 
         
mapping *action = ({ 
([      "action" : "$N��Ϣת�����˾��ڵ�����ȫ��ǽ�һ���죬����һʽ��ʾ��������$n��������$nȫ�������ڳ��ȵĵ�����", 
        "skill_name" : "ʾ����", 
        "force" : 300, 
        "lvl" : 0, 
        "dodge" : 15, 
        "damage_type" : "����", 
]), 
([      "action" : "$N�����Ц��һ�С�ʼ�ľ��������浶�ھ����ڼ�������ӿ����$P˫���籦���ʮ����ǰ������$n����һ��", 
        "skill_name" : "ʼ�ľ�", 
        "force" : 350, 
        "lvl" : 20, 
        "dodge" : 10,  
        "damage_type" : "����", 
]), 
([      "action" : "$N��������ִ򿪣����С��ֱ������Ի��浶���Ϲ����۳�һ�������ʢ���Ļ��������ת��������$n����", 
        "skill_name" : "�ֱ���", 
        "force" : 400, 
        "lvl" : 50, 
        "dodge" : 5, 
        "weapon" : "��������", 
        "damage_type" : "����", 
]), 
([      "action" : "$N�������࣬������Բ��ʹ�������ȵĵ�����ۣ����С��Ʒ�ִ������һֻ�޴�ķ�ӥ�������$n��ץ����", 
        "skill_name" : "�Ʒ�ִ", 
        "force" : 340, 
        "lvl" : 70, 
        "dodge" : 1, 
        "damage_type" : "����", 
]), 
([      "action" : "$N����һ������Ȼʹ����ħ���ϵġ�����Բ����������쫷��Χ��$P������������$nһ��������$P��������", 
        "skill_name" : "����Բ", 
        "force" : 450, 
        "lvl" : 120, 
        "dodge" : -10, 
        "damage_type" : "����", 
]), 
([      "action" : "$N�����ħ�澭���ֵ�������������$n����������֮�£����絶�и����ġ����泣�������ƺ�Ҫ��$p��������", 
        "skill_name" : "���泣", 
        "force" : 380, 
        "lvl" : 140, 
        "dodge" : -5,  
        "weapon" : "���ε���", 
        "damage_type" : "����", 
]), 
([      "action" : "$N�ֱ��࣬�����������֡����淨�������ӳ�������е������᲻ɢ�����������Ƶ�����ȴ��ɽ�������ӿ��$n", 
        "skill_name" : "���淨", 
        "force" : 450, 
        "lvl" : 160, 
        "dodge" : -15,  
        "damage_type" : "����", 
]), 
([      "action" : "$N���е�����һʽ�������š���������ת������ȫ�������޷��Զ���$P����΢�㣬����һ����ն��$n$",    
        "skill_name" : "������", 
        "force" : 500, 
        "lvl" : 180, 
        "dodge" : 5,  
        "weapon" : "��������", 
        "damage_type" : "����", 
]), 
}); 
          
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }      
 
int valid_learn(object me) 
{ 
        if ((int)me->query("max_neili") < 1500)  

                return notify_fail("�����������Ϊ������������ϰ�䳾����\n"); 
        if ((int)me->query("con") < 24) 
                return notify_fail("��ĸ���̫�ͣ����ܼ����䳾����\n"); 
        if ((int)me->query_skill("hunyuan-yiqi", 1) < 80) 

                return notify_fail("��Ļ�Ԫһ���ڹ���Ϊ̫ǳ��\n"); 
        if ((int)me->query_skill("blade",1) < 100) 
                return notify_fail("��Ļ�������̫ǳ������ѧ�䳾����\n"); 
 
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
        level = (int) me->query_skill("jiechen-dao",1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
         
int practice_skill(object me) 
{ 
        object weapon; 
 
      if (! objectp(weapon = me->query_temp("weapon")) || 
          (string)weapon->query("skill_type") != "blade")  
                return notify_fail("�����Ұѵ���˵�ɣ�\n"); 
 
        if ((int)me->query("qi") < 70 || (int)me->query("neili") < 50) 
                return notify_fail("������������������˽䳾����\n"); 
        me->add("qi", -60);     
        me->add("neili",-35); 
        return 1; 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"jiechen-dao/" + action; 
} 
/* 
mixed hit_ob(object me, object victim, int damage_bonus, int factor) 
{ 
        if(  me->query("blade", 1) == me->query_skill("force", 1) 
                && me->query_skill_mapped("blade") =="jiechen-dao") 
                me->set_temp("xiuluo", 1);      
} 
*/
