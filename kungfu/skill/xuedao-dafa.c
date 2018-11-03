// Ѫ���� xuedao-dafa.c
// Editd By Vin On 1/9/2001

#include <ansi.h>
inherit FORCE;

int valid_force(string force)
{
        return force == "longxiang-gong" ||
               force == "xiaowuxiang" ||
               force == "mizong-neigong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xuedao-dafa", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N�߾�����$w��ʹ��һ�С�ĥ��˱Ѫ����һ��б��$n��$l",
        "force"  : 210,
        "attack" : 20,
        "dodge"  : 30,
        "parry"  : 25,
        "lvl"    : 0,
        "damage" : 100,
        "skill_name"  : "ĥ��˱Ѫ",
        "damage_type" : "����",
]),
([      "action" : "$N�͵�һ����ʹһ�С���Ѫ���ء�������$w����$n�Ĵ���",
        "force"  : 240,
        "attack" : 25,
        "dodge"  : 45,
        "parry"  : 35,
        "lvl"    : 140,
        "damage" : 120,
        "skill_name"  : "��Ѫ����",
        "damage_type" : "����",
]),
([      "action" : "$N���һ�㣬ʹ����Ѫ��ãã�����������϶���ֱ��$n��$l",
        "force"  : 280,
        "attack" : 40,
        "dodge"  : 52,
        "parry"  : 40,
        "lvl"    : 160,
        "damage" : 130,
        "skill_name"  : "Ѫ��ãã",
        "damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С�Ż����Ѫ������$w��������һ��ѹ��$n",
        "force"  : 320,
        "attack" : 45,
        "dodge"  : 58,
        "parry"  : 42,
        "lvl"    : 180,
        "damage" : 140,
        "skill_name"  : "Ż����Ѫ",
        "damage_type" : "����",
]),
([      "action" : "$N�ͺ�һ����ʹ����Ѫ�����ˡ�����$wֱ��$n��$l",
        "force"  : 340,
        "attack" : 50,
        "dodge"  : 65,
        "parry"  : 45,
        "lvl"    : 200,
        "damage" : 150,
        "skill_name"  : "Ѫ������",
        "damage_type" : "����",
]),
([      "action" : "$Nʹ����Ѫ���߰ߡ�������б�̣���Ȼ����һ����ն$n������",
        "force"  : 360,
        "attack" : 55,
        "dodge"  : 70,
        "parry"  : 60,
        "lvl"    : 220,
        "damage" : 160,
        "skill_name"  : "Ѫ���߰�",
        "damage_type" : "����",
]),
([      "action" : "$Nʹһʽ����Ѫ��Ѫ�����ӵ�ֱָ$n���ؿ�",
        "force"  : 390,
        "attack" : 60,
        "dodge"  : 80,
        "parry"  : 55,
        "lvl"    : 240,
        "damage" : 170,
        "skill_name"  : "��Ѫ��Ѫ",
        "damage_type" : "����",
]),
([      "action" : "$N������㣬ʹ��һ�С�Ѫ�����桹��ת���$w����$n������",
        "force"  : 420,
        "attack" : 70,
        "dodge"  : 90,
        "parry"  : 60,
        "lvl"    : 260,
        "damage" : 185,
        "skill_name"  : "Ѫ������",
        "damage_type" : "����",
]),
([      "action": " "RED" Ѫ��֮���� "NOR"",
        "force"  : (int)this_player()->query_skill("force", 1)/2 + random((int)this_player()->query_skill("force", 1)),
        "attack" : (int)this_player()->query_skill("blade", 1)/4 + random((int)this_player()->query_skill("blade", 1)/2),
        "dodge"  : (int)this_player()->query_skill("dodge", 1)/6 + random((int)this_player()->query_skill("force", 1)/3),
        "parry"  : (int)this_player()->query_skill("parry", 1)/6 + random((int)this_player()->query_skill("parry", 1)/3),
        "damage" : (int)this_player()->query_skill("force", 1)/4 + random((int)this_player()->query_skill("blade", 1)/2),
        "lvl"    : 300,
        "skill_name" : "����",
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{ 
        int lvl;
        lvl = (int)this_player()->query_skill("xuedao-dafa", 1);

        if (lvl >= 120)
                return usage == "force" || usage == "blade" || usage == "parry";
        else
                return usage == "force";
       
}

int valid_learn(object me)
{
        if (me->query("character") == "��������" ||
           me->query("character") == "������")
                return notify_fail("�����а�������Ѫ����а��̫�أ��������죬Ī"
                                   "����ר���������˵ģ�\n");

        if ((int)me->query("str") < 28)
                return notify_fail("�����������������޷�����Ѫ���󷨡�\n");

        if ((int)me->query("dex") < 26)
                return notify_fail("��������̫��޷�����Ѫ���󷨡�\n");

        if ( me->query("gender") == "����" && me->query("xuedao-dafa", 1) > 29)
                return notify_fail("���޸����ԣ����������������������Ѫ���󷨡�\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("��Ļ����ڹ�����㣬����ѧѪ���󷨡�\n");

        if ((int)me->query("max_neili", 1) < 1600)
                return notify_fail("���������Ϊ���㣬����ѧѪ���󷨡�\n");

        if (me->query_skill("force", 1) < me->query_skill("xuedao-dafa", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ���������Ѫ���󷨡�\n");

        if (me->query_skill("xuedao-dafa", 1) > 120 &&
           me->query_skill("blade", 1) < me->query_skill("xuedao-dafa", 1))
                return notify_fail("��Ļ�������ˮƽ���������Զ���������Ѫ���󷨡�\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuedao-dafa", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 50, level)];
}

int practice_skill(object me)
{
        return notify_fail("Ѫ����ֻ����ѧ(learn)�������������ȡ�\n");
}

mixed hit_ob(object me, object victim)
{
        int skill, att, dam;
		int qi, eff_qi, max_qi;
		
		qi = me->query("qi");
		eff_qi = me->query("eff_qi");
		max_qi = me->query("max_qi");
		skill = me->query_skill("xuedao-dafa", 1);
		att = random(skill * (max_qi - qi) / max_qi) + 20;
		dam = random(skill * (max_qi - eff_qi) / max_qi) + 10;
		
		if (random(3) == 1 && (att > 20 || dam > 10))
		{
				me->add_temp("apply/attack", att);
				me->add_temp("apply/damage", dam);
				COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?10:30);
				message_vision(HIR "Ѫ����-->"HIW "�����·�-->"RED "��ս���£�\n" NOR, me);
				me->add_temp("apply/attack", -att);
				me->add_temp("apply/damage", -dam);
				return;
		}
}

/*
mixed hit_ob(object me, object victim)
{
        int time;
        time = me->query_temp("combat_time");

        if(time > 10 && random(5) && ! me->query_temp("action_flag"))
	 {
		message_vision(RED "Ѫ���󷨣���ս���£����ް���֮�ࡣ\n" NOR, me);
		me->set_temp("action_flag", 1);
	 	me->add_temp("apply/attack", time * 10);
		me->add_temp("apply/parry", time * 10);
	 	me->add_temp("apply/damage", time * 3);
	 	COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2)?10:30);
	 	me->add_temp("apply/attack", -time * 10);
		me->add_temp("apply/parry", -time * 10);
	 	me->add_temp("apply/damage", -time * 3);
	 	me->delete_temp("action_flag");
	 	return;
	 }
}
*/
int difficult_level()
{
        return 400;
}

string perform_action_file(string action)
{
        return __DIR__"xuedao-dafa/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"xuedao-dafa/exert/" + action;
}
