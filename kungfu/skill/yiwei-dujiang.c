// yiwei-dujiang.c һέ�ɽ� 
// modified by karma 2004 
      
inherit SHAOLIN_SKILL; 
   
string *dodge_msg = ({ 
        "$nһʽ��һέ�ɽ�����ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n", 
         "$nһʽ�������Ӳ�����˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n", 
        "$nһʽ��������ˮ����˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n", 
        "$n����ƮƮ��ʹ��һ�С�������ת�����ܹ���$N�Ĺ�����\n", 
        "$nʹ��������岨����������ˮ�滬��һ�㣬���λ��˿�ȥ��\n", 
        "$nһ�������ضɺ�����Ծ�����ߣ������$N��һ�С�\n", 
}); 
     
int valid_enable(string usage) 
{ 
        return usage == "dodge" || usage == "move"; 
} 
  
int valid_learn(object me) 
{ 
        if (me->query("dex") < 24)  
                return notify_fail("�����������㣡\n");  
        if (me->query("int") < 26)  
                return notify_fail("���������Բ��㣡\n");  
        return 1; 
} 
         
string query_dodge_msg(string limb) 
{ 
        return dodge_msg[random(sizeof(dodge_msg))]; 
} 
         
int practice_skill(object me) 
{ 
        if((int)me->query("qi") < 50 ) 
                return notify_fail("�������̫���ˣ�������һέ�ɽ���\n"); 
        me->receive_damage("qi", 40); 
        return 1; 
} 
string perform_action_file(string action)  
{         
        return __DIR__"yiwei-dujiang/" + action;  
}  

