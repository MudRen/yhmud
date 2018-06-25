//    /kungfu/skill/suixing-tui.c ��Ӱ������ 
  
#include <ansi.h> 
inherit SHAOLIN_SKILL; 
   
mapping *action = ({ 
([      "action" : "$N������ǰ����Ȼ������ȣ�һʽ������ִ�ԡ���ֱ��$n��ͷ��", 
        "force" : 200, 
        "dodge" : 0, 
        "parry" : 5, 
        "lvl" : 0, 
        "skill_name" : "����ִ��", 
        "damage_type" : "����" 
]), 
([      "action" : "$N����һ����˫���أ�һʽ�����ǰ��¡����ڿ��������߽ţ�ֱ��$n��ͷ���ء���", 
        "force" : 250, 
        "dodge" : 10, 
        "parry" : -10, 
        "lvl" : 40, 
        "skill_name" : "���ǰ���", 
        "damage_type" : "����" 
]), 
([      "action" : "$N����ǰ�㣬��Ż�Բ������ʹ��һʽ������ޱߡ���ɨ��$n������", 
        "force" : 300, 
        "dodge" : -10, 
        "parry" : 5, 
        "lvl" : 80, 
        "skill_name" : "����ޱ�", 
        "damage_type" : "����" 
]), 
([      "action" : "$N����ٿ�ص������������ȣ�����$n��ͷ�����ز����ɲ�������һʽ��ת���ֻء�", 
        "force" : 350, 
        "dodge" : 10, 
        "parry" : 0, 
        "lvl" : 120, 
        "skill_name" : "ת���ֻ�", 
        "damage_type" : "����" 
]), 
([      "action" : "$N������������������η�ת��ɨ��һ�С����켫�֡�������$n��$l", 
        "force" : 400, 
        "dodge" : -10, 
        "parry" : 0, 
        "lvl" : 150, 
        "skill_name" : "���켫��", 
        "damage_type" : "����" 
]),                                                    
([      "action" : "$NԾ���ڰ�գ�˫������������磬һʽ������ȱ���Ѹ�����׵ؾ���$n", 
        "force" : 450, 
        "dodge" : 5, 
        "parry" : -10, 
        "lvl" : 180, 
        "skill_name" : "����ȱ�", 
        "damage_type" : "����" 
]), 
}); 
         
int valid_enable(string usage) { return usage=="unarmed" || usage=="parry" || usage=="dodge"; }    
         
int valid_learn(object me) 
{ 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
                return notify_fail("ѧ��Ӱ������ʱ���ﲻ����������\n"); 
        if (me->query_skill("hunyuan-yiqi",1) < 150) 
                return notify_fail("����ڹ���򲻹����޷�ѧ��Ӱ�����ȡ�\n"); 
        if ((int)me->query("str") < 26 ||(int)me->query("dex") < 24) 
                return notify_fail("����������Բ��㣬�޷�ѧϰ��Ӱ�����ȡ���\n");  
        if ((int)me->query("max_neili") < 600) 
                return notify_fail("�������̫�����޷�ѧϰ��Ӱ�����ȡ�\n"); 
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
        string msg; 
        level   = (int) me->query_skill("ruying-suixingtui",1); 
         
        if (me->query_temp("sl_rysxt")){ 
                switch(me->query_temp("sl_rysxt")){ 
                        case 5: msg = HIY"$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ��"NOR;       break; 
                        case 4: msg = HIY"������$N���ȹ��أ�������һŤ�������ȵ�һ�С�Ӱ���־���������������$n"NOR; break; 
                        case 3: msg = HIY"ֻ��$N�ҽž���δ���������һת������˳��ɨ��һ�С��桹�־�����Ӱ����"NOR; break; 
                        case 2: msg = HIY"�����$N��δ�󳷣��Ѿ������Ρ��־����ھ�ֱ͸�ż⣬��$n�ظ�����������ʮ��"NOR; break; 
                        case 1: msg = HIR"��ʱ$N˫��չ��������һ��ǿ�ҵ����磬˫����ʱ�벢������Ӱ���Ρ�һ�����ں���$n����֮��"NOR; break; 
                        default: msg = HIY"$N��ȻԾ�����һ��һ������ʱ֮���߳�һ�С��硹�־��Ĵ����ȣ�ֱϮ$nǰ��"NOR; break;        
                }     
                me->add_temp("sl_rysxt", -1);                   
                return([       
                        "action": msg,         
                        "force" : 400+random(100), 
                        "dodge" : random(30)-15, 
                        "damage_type" : me->query_temp("sl_rysxt")?"����":"����", 
                ]); 
        } 
                     
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
         
int practice_skill(object me) 
{ 
        if ((int)me->query("qi") < 80) 
                return notify_fail("�������̫���ˡ�\n"); 
        if ((int)me->query("neili") < 20) 
                return notify_fail("���������������Ӱ�����ȡ�\n"); 
        me->add("qi", -60); 
        me->add("neili", -10); 
        return 1; 
} 
         
string perform_action_file(string action) 
{ 
         return __DIR__"ruying-suixingtui/" + action; 
} 

