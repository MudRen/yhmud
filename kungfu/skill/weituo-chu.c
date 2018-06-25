inherit SKILL; 
   
mapping *action = ({ 
([      "action":"$NԾ�ڰ�գ�һ�С��ɺ�չ������ɽ��������$w�ѻ���������Ӱ����$n�ۻ����ң���֪���룬��������", 
        "force" : 150, 
         "dodge" : 10, 
         "parry" : 10, 
        "damage": 20, 
         "lvl" : 20, 
         "skill_name" : "�ɺ�չ������ɽ", 
         "damage_type":"����" 
]), 
([ 
 
"action":"$Nͦ$w��$n��$W��ס��˳��һ�С������λ����ɹ�����$w�������ҷɿ������������ߣ���$nѹ������", 
         "force" : 180, 
         "dodge" : 10, 
         "parry" : 15, 
        "damage": 100, 
         "lvl" : 40, 
         "skill_name" : "�����λ����ɹ�", 
         "damage_type":"����" 
]), 
([      "action":"$Nһ�С���¹̤�����ɲݡ�����ϥ��������$w����$n���̣�ȴδ���������ϣ��͵�һ�ᣬ��$n���ظ����ȥ", 
        "force" : 220,  
        "dodge" : 15, 
        "parry" : 20, 
        "damage": 40, 
        "lvl" : 60, 
        "skill_name" :  "��¹̤�����ɲ�", 
        "damage_type":"����" 
]), 
([      "action":"$NͻȻ�����ڵأ�$n��㵼䣬һ�С�����ԾˮǱ��ء�������$n�����´ܹ���������ͷ��$w����ɨ��$n��$l", 
        "force" : 200, 
        "dodge" : 20, 
        "parry" : 25, 
        "damage": 60, 
        "lvl" : 80, 
        "skill_name" :  "����ԾˮǱ���", 
        "damage_type":"����" 
]), 
([      "action":"$Nһ�С���Գ�׹�����������������磬����$n�ɿ챼�ܣ�����$wһ�п���һ�У�ɲ�Ǽ���$n�����ʮ����", 
        "force" : 280,  
        "dodge" : 30, 
        "parry" : 30, 
        "damage": 80, 
        "lvl" : 100, 
        "skill_name" :  "��Գ�׹�������", 
        "damage_type":"����" 
]), 
([      "action":"$N��̤����ǰ������˫�ۣ�����$w�󿪴��أ�����������һ�С���ӥ����ɨǬ����ɨ��$n������", 
        "force" : 220, 
        "dodge" : 30, 
        "parry" : 40, 
        "damage": 100, 
        "lvl" : 120, 
        "skill_name" :  "��ӥ����ɨǬ��", 
        "damage_type":"����" 
]), 
([      "action":"$N���һ����һ�С�������ˮ�����桹��$w���ַɳ������ž�������$n��ǰ�ģ��漴����$n����������ְ�$w��������", 
        "force" : 230,  
        "dodge" : 20, 
        "parry" : 30, 
        "damage": 80, 
        "lvl" : 130, 
        "skill_name" :  "������ˮ������", 
        "damage_type":"����" 
]), 
([      "action":"$N˫ĿԲ��������Ĭ�����ԣ�һ�С�������ƺ���������$w����ǧ����������ֻ�����$n�ĵ�ͷ����", 
        "force" : 300,  
        "dodge" : 20, 
        "parry" : 30, 
        "damage": 100, 
        "lvl" : 150, 
        "skill_name" :  "������ƺ�����", 
         "damage_type":"����" 
]), 
}); 
  
int valid_enable(string usage)  { return  (usage == "staff") || (usage =="parry"); } 
          
int valid_learn(object  me) 
{
        mapping fam = me->query("family"); 
        if (fam["family_name"]  != "������" )
                return  notify_fail("Τ����ֻ�ܴ�������ѧ����\n"); 
        if ((int)me->query("max_neili") < 1500) 
                return  notify_fail("�������������\n"); 
        return  1; 
} 
  
string perform_action_file(string action) 
{ 
        return __DIR__"weituo-chu/" + action; 
} 
string query_skill_name(int level) 
{ 
        int i;  
        for(i = sizeof(action)-1; i >=  0; i--) 
                if(level >= action[i]["lvl"]) 
                        return  action[i]["skill_name"]; 
} 

mapping query_action(object me, object  weapon) 
{ 
        int i, level; 
        level = (int) me->query_skill("weituo-chu",1); 
        for(i = sizeof(action); i > 0;  i--) 
                if(level > action[i-1]["lvl"])  
                return  action[NewRandom(i, 20, level/5)]; 
} 
  
int practice_skill(object me) 
{ 
        object  weapon; 
        if (!objectp(weapon = me->query_temp("weapon")) 
                || (string)weapon->query("skill_type") != "staff") 
                return  notify_fail("��ʹ�õ��������ԡ�\n"); 
        if ((int)me->query("jingli") <  70) 
                return  notify_fail("�������������Τ���ơ�\n"); 
        if ((int)me->query("neili") < 70) 
                return  notify_fail("�������������Τ���ơ�\n"); 
        me->receive_damage("jing", 60);             
        if((int)me->query_skill("weituo-chu",1)> 200)
        {       
                me->add("neili",-20); 
        } 
        return  1; 
} 

