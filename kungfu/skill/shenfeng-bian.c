
//ȡ��������ʦ<��ţͼ��> 
#include <ansi.h> 
         
inherit SKILL; 
 
string *body_name = ({  
"������","��첲","����","ͷ��","����","����","С��","��Ž���","������","�Ҹ첲","����","�ҽŽ���",});       
 
mapping *action = ({ 
([ "action": "$N˫�ֺ�ʲ��������ע, һʽ��δ����������$w�������ԣ���ֱ�Ĵ���$n��$l", 
        "skill_name"    : "δ��", 
        "damage_type":  "����", 
]), 
([ "action": "$N���绬��������$wһ����һʽ����������Ѹ���ޱȵطִ��������࣬$n��ʱ����֧穣������ֽ�", 
        "skill_name"    : "����", 
        "damage_type":  "����" 
]), 
([ "action": "$N������ע��$w�����ʹ��һʽ�����ơ���$w��ز���裬ֱ�������ƿ�һ�����$n", 
        "skill_name"    : "����", 
        "damage_type":  "����" 
]),  
([ "action": "$Nһ����Х������$wһ�С����ס������������Ӱ����ǵص���$n�������Ƶ�����֮��", 
        "skill_name"    : "����", 
        "damage_type":  "����" 
]), 
([ "action": "$N������������$w��һʽ��ѱ�������ӳ�������ת������$n��ȥ ", 
        "skill_name"    : "ѱ��", 
        "damage_type":  "����" 
]), 
([ "action": "$N������շ������ִ����ӳ�$w��һʽ���ް�����һ����ɽ�����ı޷�ֱ����$n", 
        "skill_name"    : "�ް�", 
        "damage_type":  "����" 
]), 
([ "action": "$N��¶΢Ц��ǰһ��������$w���ʹ��һʽ�����ˡ�������ƽ������������˿������", 
        "skill_name"    : "����", 
        "damage_type":  "����" 
]), 
([ "action": "$N��ǰ������˫����ס$w������ʹ��һʽ�������������Ƴ���, һ�ɾ����ƿն���", 
        "skill_name"    : "����", 
        "damage_type":  "����" 
]), 
([ "action": "$N��������$w��һʽ�����ա�����������, ��������", 
        "skill_name" : "����", 
        "damage_type":  "����" 
]), 
([ "action": "$N�����������裬����$wͻȻ�ӳ���ʹ��һʽ��˫����������������������,���ƾ���", 
        "skill_name"    : "˫��", 
        "damage_type":  "����" 
]), 
}); 
         
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); } 
         
int valid_learn(object me) 
{ 
       object weapon; 
 
        if( (int)me->query("max_neili") < 800 ) 
               return notify_fail("����������㣬û�а취��ϰ�޷�, ����Щ���������ɡ�\n"); 
        if(me->query("int") < 28 ) 
               return notify_fail("����������Բ��㡣\n");       
        if ( !objectp(weapon = me->query_temp("weapon"))        
                ||( string)weapon->query("skill_type") != "whip" ) 
               return notify_fail("���������һ�����Ӳ������޷���\n"); 
       return 1; 
 
} 
string query_skill_name(int level) 
{
        int i; 
        for(i = sizeof(action)-1; i >= 0; i--) 
                return action[i]["skill_name"]; 
} 
         
mapping query_action(object me, object weapon) 
{ 
        int i, level,a,b,c,d,e,f,j; 
        string msg; 
        level   = (int) me->query_skill("shenfeng-bian",1); 
 
        a = me->query("neili"); 
        // ע�⣬ȡ��������ʱҪע��ĳЩ�ķ�����������ʱ���ԡ�    
        b = me->query_str(); 
        c = me->query_dex(); 
        d = me->query_con(); 
        e = me->query_skill("whip", 1); 
        f = me->query_skill("hunyuan-yiqi",1); 
         
        if (me->query("neili") > me->query("max_neili")) 
        a = me->query("max_neili")+(me->query("neili") - me->query("max_neili"))/10; 
        if ( a > 3000) a = 3000;         
        if ( a < 800) a = 800;
        j = (random(e + f)/4 + 1) * (random(b/10)+1)+10; 
        if ( j > 200 ) j = 200; 
 
        weapon =me->query_temp("weapon"); 
        if(me->query_temp("chb")){ 
          switch(me->query_temp("chb")){ 
             case 3: msg = MAG"����$N���γ�ǰһ�壬 ����"+ weapon->name()+MAG"����$n��С��" NOR; break;    
             case 2: msg =HIY"������$N����������"+ weapon->name()+ "��"+ weapon->name()+HIY"���йٱʰ����$n��ǰ��" NOR;break; 
             case 1: msg = HIW"���$N���ϸ߸�һԾ�����˷�����"+ weapon->name()+HIW "����$n���𹥻�" NOR; break; 
             default: msg = HIW"���$N���ϸ߸�һԾ�����˷�����"+ weapon->name()+HIW"����$n���𹥻�" NOR; break; 
          } 
          me->add_temp("chb", -1); 
              return ([ 
                "action":msg, 
                "damage":random(e + f/2)/ 2 * random(b/10)+10,  
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"], 
                "dodge": random(c)+random(me->query_skill("dodge", 1)/10)-random(40), 
                "force": random(a/20) + (level), 
                "parry": d-random(40)+random(me->query_skill("parry", 1)/5), 
                "skill_name" : action[NewRandom(i, 20, level/5)]["skill_name"],        
              ]);
              } 
        for(i = sizeof(action); i > 0; i--) { 
              return ([ 
                "action":action[NewRandom(i, 20, level/5)]["action"], 
                "damage": j,  
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"], 
                "dodge": random(c)+random(me->query_skill("dodge", 1)/10)-random(40), 
                "force": random(a/20) + (level), 
                "parry": d-random(40)+random(me->query_skill("parry", 1)/5), 
                "skill_name" : action[NewRandom(i, 20, level/5)]["skill_name"],        
              ]); 
        } 
} 
 
int practice_skill(object me) 
{ 
       object weapon; 
 
        if (!objectp(weapon = me->query_temp("weapon")) 
               || (string)weapon->query("skill_type") != "whip") 
                return notify_fail("��ʹ�õ��������ԡ�\n"); 
        if ((int)me->query_skill("hunyuan-yiqi",1) < 100)       
                return notify_fail("�����һ������,�޷��������ޡ�\n");        
        
        if ((int)me->query("qi") < 50) 
                return notify_fail("����������������޷���\n"); 
                 
        if ((int)me->query("neili") < 50) 
                return notify_fail("����������������޷���\n"); 
                 
        me->receive_damage("qi", 35); 
        me->add("neili", -20); 
        return 1; 
} 
         
mixed hit_ob(object me, object victim, int damage_bonus, int factor) 
{ 
        object weap,weap1; 
        string name; 
        int i; 
        name = body_name[random(sizeof(body_name))]; 
        i = me->query_skill("whip")/60+1; 
        weap = victim->query_temp("weapon"); 
        weap1 = me->query_temp("weapon"); 
        if( random(me->query_skill("shenfeng-bian", 1)) > 60 
                && (me->query("neili") > 100)){ 
        if ( victim->query_temp("weapon")){ 
        if (random(5) > 2){ 
               message_vision(HIY "ֻ��$N���ٻ���" + weap1->name() + HIY"��ת����������СȦ�ӣ�������֮����ס�Է���" + weap->name() +"��\n" NOR, me );           
               victim->start_busy(1); 
               if (random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/3 ){         
                 message_vision(HIY "$N�����ֱ�����һק��" + weap->name() 
                                + HIY"ȴ�޷���"+weap1->name()+HIY"�Ĳ������ѿ����鼱֮��ֻ�÷��������еı��С�\n" NOR, victim ); 
                 weap->move(environment(me)); 
                 victim->reset_action(); 
               } 
               else { 
                 message_vision(HIY "$N�����ɾ���" + weap->name() 
                                + HIY"˳�ŷ��������ת���£��⿪��"+weap1->name()+HIY"�Ĳ��ơ�\n" NOR, victim ); 
                 victim->add("neili",-50); 
               } 
               me->add("neili", -30); 
             } 
           } 
           else { 
             if ((random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/3 ) 
              && (!random(4))) { 
               victim->start_busy(random(i)+ 1); 
               me->add("neili",-80); 
               victim->receive_damage("qi", me->query_skill("kurong-changong",1)/2+damage_bonus/2); 
//             victim->receive_wound("qi", me->query_skill("kurong-changong",1)/4+damage_bonus/4);   
//             if (!victim->query_condition("no_perform")) 
//               victim->apply_condition("no_perform",i*random(2+random(2))); 
               message_vision(HIY "ֻ��$N�ı�ʽ�鶯�쳣," + weap1->name() + HIY"ת����������СȦ�ӣ�������֮����ס�˶Է���" + name +"��\n" NOR,     me); 
               message_vision(HIR "$N����һ��,�ƺ����˵��ˡ�\n" NOR, victim );     
             } 
           }              
           return 1; 
        } 
} 
 
string perform_action_file(string action) 
{ 
        return __DIR__"shenfeng-bian/" + action;        
} 

