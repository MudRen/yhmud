// huoyan-dao.c ���浶
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$Nʹ��һ�С���ľȡ�𡹣�����ת��˫����ǰƽƽ����$n",
        "skill_name" : "��ľȡ��",
        "force" : 90,
        "attack": 25,
        "dodge" : 15,
        "parry" : 25,
        "lvl"   : 0,
        "damage": 40,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�ף�ڻ��桹�������絶��бб����$n��$l",
        "skill_name" : "ף�ڻ���",
        "force" : 130,
        "attack": 47,
        "dodge" : 25,
        "parry" : 31,
        "lvl"   : 30,
        "damage": 55,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�����ޱߡ���˫��һ�ģ�һ�����������й���$n��$l",
        "skill_name" : "����ޱ�",
        "force" : 180,
        "attack": 61,
        "dodge" : 25,
        "parry" : 40,
        "lvl"   : 60,
        "damage": 65,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С������ֻء���˫�ֺ�ʮ����ͷ����$n",
        "skill_name" : "�����ֻ�",
        "force" : 240,
        "attack": 75,
        "dodge" : 20,
        "parry" : 47,
        "lvl"   : 90,
        "damage": 70,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�˫�����桹��˫��һ�������������湥��$n��$l",
        "skill_name" : "˫������",
        "force" : 300,
        "attack": 80,
        "dodge" : 30,
        "parry" : 56,
        "lvl"   : 120,
        "damage": 80,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С���ɽ�𺣡���˫������б�ģ���ʱ��ǧ������������˷�����$n",
        "skill_name" : "��ɽ��",
        "force" : 350,
        "attack": 91,
        "dodge" : 35,
        "parry" : 62,
        "lvl"   : 140,
        "damage": 85,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С��׷��ȡ�����ۻ��գ�����������ֱ��$n��$l",
        "skill_name" : "�׷���",
        "force" : 370,
        "attack": 102,
        "dodge" : 37,
        "parry" : 78,
        "lvl"   : 160,
        "damage": 90,
        "damage_type" : "����",
]),
([      "action": "$Nʹ��һ�С�������������˫��΢��������ǰ�죬һ���ھ�����ɽ�����㹥��$n",
        "skill_name" : "��������",
        "force" : 400,
        "attack": 110,
        "dodge" : 45,
        "parry" : 84,
        "lvl"   : 180,
        "damage": 109,
        "damage_type" : "����",
]),
([      "action": " "RED" ���浶֮���� "NOR"",
        "force"  : (int)this_player()->query_skill("force", 1)/3 + random((int)this_player()->query_skill("force")),
        "attack" : (int)this_player()->query_skill("strike", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "dodge"  : (int)this_player()->query_skill("dodge", 1)/6 + random((int)this_player()->query_skill("force", 1)/3),
        "parry"  : (int)this_player()->query_skill("parry", 1)/6 + random((int)this_player()->query_skill("parry", 1)/3),
        "damage" : (int)this_player()->query_skill("force", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "lvl"    : 200,
        "skill_name" : "����",
        "damage_type": "����"
]),
});


int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "dashou-yin" ||
	       combo == "yujiamu-quan";
}

int valid_learn(object me)
{
	int skill;
	skill = me->query_skill("huoyan-dao", 1);
	
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����浶������֡�\n");

	if ((int)me->query("con") < 32)
        return notify_fail("���������������������������浶��\n");
	
	if ((int)me->query("shen") > - skill * 1000)
		return notify_fail("���ɱ���������������������Ļ��浶��\n");
	
	if ((int)me->query("max_neili") < 1200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��\n");

    if (me->query_skill("strike", 1) < me->query_skill("huoyan-dao", 1))
        return notify_fail("��Ļ����Ʒ�������ޣ��޷���������Ļ��浶����\n");

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
        level = (int) me->query_skill("huoyan-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
//	object weapon;
	int cost;
	cost = me->query_skill("huoyan-dao", 1) / 5 + 60;

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����浶������֡�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������������������˻��浶��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������˻��浶��\n");

	me->receive_damage("qi", 55);
    me->add("neili", -cost);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, lvl2, damage;
		//object cloth;
		//string msg;

        lvl = me->query_skill("huoyan-dao", 1);
		lvl2 = victim->query_skill("force") / 2;

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (lvl + damage_bonus / 10 > lvl2 + victim->query_con())
        {
				/*if (objectp(cloth = victim->query_temp("armor/cloth"))
					&& cloth->query("consistence") > 0)
					{
						cloth->add("consistence", -10);
						msg = HIR "ֻ��$n���ϵ�" + cloth->name() + "ͻȻ����������\n" NOR;
						message_combatd(msg, me, victim);
					}
						
				if (cloth->query("consistence") < 0)
					cloth->set("consistence", 0);
				*/
				if (me->query("shen") < - lvl * lvl * lvl)
					damage = damage_bonus + random(lvl);
				else
					damage = damage_bonus;
                victim->receive_wound("qi", (damage - 80) / 3, me);

                return random(2) ? HIR "ֻ��$n" HIR "ǰ�ء����꡹һ�����죬������"
                                   "�߹Ƕ��۵�������\n" NOR:

                                   HIR "$n" HIR "һ���ҽУ���ǰ���������꡹������"
                                   "�죬������Ѫ���硣\n" NOR;
        }
}

string perform_action_file(string action)
{
	return __DIR__"huoyan-dao/" + action;
}