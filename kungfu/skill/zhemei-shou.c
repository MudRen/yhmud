#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$Nһ�С���÷��Թ����˫�ֺ�ӣ�ץ��$n",
        "force" : 80,
        "attack": 25,
        "dodge" : 20,
        "parry" : 25,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "��÷��Թ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С��ƻ���Գ������ԾȻ����ץ��$n��ͷ��",
        "force" : 100,
        "attack": 28,
        "dodge" : 20,
        "parry" : 27,
        "damage": 20,
        "lvl"   : 30,
        "skill_name" : "�ƻ���Գ�",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С���ɽһ�����ı̡���˫�ַ׷ɣ�$nֻ���ۻ�����",
        "force" : 120,
        "attack": 32,
        "dodge" : 30,
        "parry" : 28,
        "damage": 30,
        "lvl"   : 60,
        "skill_name" : "��ɽһ�����ı�",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С�÷��ѩ�串��ƻ����˫�ֺϻ���$nֻ���޴��ɱ�",
        "force" : 150,
        "attack": 33,
        "dodge" : 30,
        "parry" : 33,
        "damage": 35,
        "lvl"   : 80,
        "skill_name" : "÷��ѩ�串��ƻ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С�������÷��ѩ�ҡ���˫��ƮȻץ��$n",
        "force" : 180,
        "attack": 36,
        "dodge" : 30,
        "parry" : 37,
        "damage": 45,
        "lvl"   : 100,
        "skill_name" : "������÷��ѩ��",
        "damage_type" : "����"
]),

([      "action": "$N˫��ƽ�٣�һ�С�����������ŪӰ������$n",
        "force" : 210,
        "attack": 42,
        "dodge" : 35,
        "parry" : 45,
        "damage": 40,
        "lvl"   : 120,
        "skill_name" : "����������ŪӰ",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С���������ֱ���ۡ�������$n���ƺ�$n��ȫ��������",
        "force" : 240,
        "attack": 47,
        "dodge" : 30,
        "parry" : 41,
        "damage": 45,
        "lvl"   : 140,
        "skill_name" : "��������ֱ����",
        "damage_type" : "����"
]),

([      "action": "$N������Σ�����һ�ǡ�����δ�϶��Ⱦ�������$n��ͷ��",
        "force" : 280,
        "attack": 46,
        "dodge" : 30,
        "parry" : 47,
        "damage": 50,
        "lvl"   : 160,
        "skill_name" : "����δ�϶��Ⱦ�",
        "damage_type" : "����"
]),
([      "action": "$Nʩ��������Ц�졹�����ֺ�ɨ$n��$l�����ֹ���$n���ؿ�",
        "force" : 330,
        "attack": 58,
        "dodge" : 10,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 170,
        "skill_name" : "����Ц��",
        "damage_type" : "����"
]),
([      "action": "$Nʩ������ʯ��١�������һ������$n",
        "force" : 370,
        "attack": 62,
        "dodge" : 20,
        "parry" : 52,
        "damage": 80,
        "lvl"   : 180,
        "skill_name" : "��ʯ���",
        "damage_type" : "����"
]),
([      "action": " "RED" ��÷֮���� "NOR"",
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

int valid_enable(string usage) { return usage=="parry"|| usage=="hand"; }

int valid_combine(string combo) { return combo=="liuyang-zhang"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ң��÷�ֱ�����֡�\n");

        if (me->query("dex") < 30)
                return notify_fail("�����������㣬�޷�ѧϰ���ɵ���ң��÷�֡�\n");

        if ((int)me->query("max_neili") < 900)
                return notify_fail("�������̫�����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("��Ļ����ַ���򲻹����޷�����ң��÷�֡�\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("zhemei-shou", 1))
                return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷������������ң��÷�֡�\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("zhemei-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 90)
                return notify_fail("�������̫���ˡ�\n");

        if ((int)me->query("neili") < 80)
                return notify_fail("���������������ң��÷�֡�\n");

        me->receive_damage("qi", 85);
        me->add("neili", -72);
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
				message_vision(HIY "\n��ң��÷��,���಻����\n" NOR, me, target);
				n = 1;
				if (random(ly) > 100) n += 1;
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
        return __DIR__"zhemei-shou/" + action;
}
