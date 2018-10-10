// SKILL liuyang-zhang.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action" : "$Nһ�С������۽𡹣����Ƶ�������֮�ϣ�����$n",
	"force" : 100,
        "attack": 2,
	"dodge" : 30,
        "parry" : 1,
	"damage": 5,
	"lvl"   : 0,
	"skill_name" : "�����۽�",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С������ƶ���������ɫ���أ�˫����ƮƮ������$n",
	"force" : 130,
        "attack": 8,
	"dodge" : 25,
        "parry" : 3,
	"damage": 30,
	"lvl"   : 20,
	"skill_name" : "�����ƶ���",
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С���б��·��ϼ������˫�ƻû�һƬ��Ӱ����$n�������ڡ�",
	"force" : 160,
        "attack": 12,
	"dodge" : 43,
        "parry" : 4,
	"damage": 35,
	"lvl"   : 30,
	"skill_name" : "��б��·��ϼ��",
	"damage_type" : "����"
]),

([	"action" : "$Nһ�С���������������$n��$l��������",
	"force" : 210,
        "attack": 15,
	"dodge" : 55,
        "parry" : 8,
	"damage": 50,
	"lvl"   : 40,
	"skill_name" : "��������",
        "damage_type" : "����"
]),
([	"action" : "$Nһ�С�����һ���ͽ��ѡ���ֻ��һƬ��Ӱ����$n",
	"force" : 250,
        "attack": 22,
	"dodge" : 52,
        "parry" : 0,
	"damage": 30,
	"lvl"   : 60,
	"skill_name" : "����һ���ͽ���",
	"damage_type" : "����"
]),

([	"action" : "$N˫��ƽ�ӣ�һ�С���ϼ���������$n",
	"force" : 300,
        "attack": 23,
	"dodge" : 65,
        "parry" : 11,
	"damage": 50,
	"lvl"   : 80,
	"skill_name" : "��ϼ������",
        "damage_type" : "����"
]),
([	"action" : "$Nһ�С����ղγ��֡���ֻ��һƬ��Ӱ����$n",
	"force" : 310,
        "attack": 28,
	"dodge" : 63,
        "parry" : 5,
	"damage": 80,
	"lvl"   : 100,
	"skill_name" : "���ղγ���",
	"damage_type" : "����"
]),

([	"action" : "$N������Σ�����һ�ǡ���ϼ��Ѧᡡ�����$n��ͷ��",
	"force" : 330,
        "attack": 25,
	"dodge" : 77,
	"damage": 90,
        "parry" : 12,
	"lvl"   : 120,
	"skill_name" : "��ϼ��Ѧ�",
        "damage_type" : "����"
]),
([	"action" : "$Nʩ��������������������ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
	"force" : 360,
        "attack": 31,
	"dodge" : 80,
        "parry" : 15,
	"damage": 100,
	"lvl"   : 140,
	"skill_name" : "���������",
        "damage_type" : "����"
]),
([	"action" : "$Nʩ���������������˫��ͬʱ����$n��$l",
	"force" : 400,
        "attack": 32,
	"dodge" : 81,
        "parry" : 10,
	"damage": 130,
	"lvl"   : 160,
	"skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action": " "RED" ����֮���� "NOR"",
        "force"  : (int)this_player()->query_skill("force", 1)/2 + random((int)this_player()->query_skill("force", 1)),
        "attack" : (int)this_player()->query_skill("strike", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "dodge"  : (int)this_player()->query_skill("dodge", 1)/6 + random((int)this_player()->query_skill("force", 1)/3),
        "parry"  : (int)this_player()->query_skill("parry", 1)/6 + random((int)this_player()->query_skill("parry", 1)/3),
        "damage" : (int)this_player()->query_skill("force", 1)/4 + random((int)this_player()->query_skill("strike", 1)/2),
        "lvl"    : 200,
        "skill_name" : "����",
        "damage_type": "����"
])
});

int valid_enable(string usage)
{
	return usage == "parry" || usage == "strike" || usage == "throwing";
}

int valid_combine(string combo)
{
	return combo == "zhemei-shou";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ɽ�����Ʊ�����֡�\n");

        if (me->query("str") < 30)
                return notify_fail("�������������㣬�޷�ѧϰ���͵���ɽ�����ơ�\n");

        if ((int)me->query_skill("force") < 130)
                return notify_fail("����ڹ���򲻹����޷�����ɽ�����ơ�\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷�����ɽ�����ơ�\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("��Ļ����Ʒ���򲻹����޷�����ɽ�����ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyang-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷������������ɽ�����ơ�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("liuyang-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 90)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 80)
		return notify_fail("���������������ɽ�����ơ�\n");

	me->receive_damage("qi", 81);
	me->add("neili", -73);
	return 1;
}

mixed hit_ob(object me, object target)
{
        int ly, zm, bm, bh, lb;
		int count_damage, count_attack;
		int i, n;
		ly = me->query_skill("liuyang-zhang", 1);
		zm = me->query_skill("zhemei-shou", 1);
		bm = me->query_skill("beiming-shengong", 1);
		bh = me->query_skill("bahuang-gong", 1);
		lb = me->query_skill("lingbo-weibu", 1);
		count_damage = bm / 10 + bh / 10;
		count_attack = lb / 5;
		
		if (me->query("family/family_name") == "��ң��" || me->query("family/family_name") == "���չ�")
		{
			if (random(2) && me->query("neili") > 200 && ! me->query_temp("is_attacking"))
			{
				message_vision(HIY "\n��ɽ������,¯���࣡\n" NOR, me, target);
				n = 1;
				if (random(zm) > 100) n += 1;
				me->add("neili", -n * 30);
				me->set_temp("is_attacking", 1);
				if (me->query_skill_mapped("force") == "beiming-shengong" ||
					me->query_skill_mapped("force") == "bahuang-gong")
					me->add_temp("apply/damage", count_damage);
				if (me->query_skill_mapped("dodge") == "lingbo-weibu")
					me->add_temp("apply/attack", count_attack);
				for (i = 0; i < n; i++)
				{
					COMBAT_D->do_attack(me, target, 0, 0);
				}
				me->delete_temp("is_attacking");
				if (me->query_skill_mapped("force") == "beiming-shengong" ||
					me->query_skill_mapped("force") == "bahuang-gong")
					me->add_temp("apply/damage", -count_damage);
				if (me->query_skill_mapped("dodge") == "lingbo-weibu")
					me->add_temp("apply/attack", -count_attack);
			
			}
		}
}

string perform_action_file(string action)
{
	return __DIR__"liuyang-zhang/" + action;
}
