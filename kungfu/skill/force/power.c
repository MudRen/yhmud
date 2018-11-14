// power.c
// �����ڹ��˹�Ч����������ѧ����

#include <ansi.h>

inherit F_CLEAN_UP;

mapping valid_types = ([
		"force":        "�ڹ�",
        "unarmed":      "ȭ��",
        "sword":        "����",
        "blade":        "����",
        "staff":        "�ȷ�",
        "hammer":       "����",
        "club" :        "����",
        "throwing":     "����",
        "parry":        "�м�",
        "dodge":        "�Ṧ",
        "magic":        "����",
        "whip":         "�޷�",
        "dagger":       "�̱�",
        "finger":       "ָ��",
        "hand":         "�ַ�",
        "cuff":         "ȭ��",
        "claw":         "צ��",
        "strike":       "�Ʒ�",
        "medical":      "ҽ��",
        "poison":       "����",
        "cooking":      "����",
        "chuixiao-jifa" : "����",
        "guzheng-jifa"  : "����",
        "tanqin-jifa"   : "����",
]);

int exert(object me, object target)
{
	int skill;
	mapping map;
	string *skills;
	string sk;
	int i, lev;
	sk = "force";
	lev = me->query_skill("force");
	
	skill = me->query_skill("martial-cognize", 1);
	skills = keys(valid_types);
	map = me->query_skill_map();

	if (target != me)
		return notify_fail("��ֻ�������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("power"))
		return notify_fail("���Ѿ����˹����ˡ�\n");
	
	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���Ϊ����,�޷������Լ��Ĺ�����\n");

	if (skill < 120)
		return notify_fail("�����ѧ��������,�޷������Լ��Ĺ�����\n");
	
	for (i = 0; i < sizeof(skills); i++)
    {
            if (undefinedp(map[skills[i]]))
                    continue;

            if (! me->query_skill(skills[i]))
                    continue;
				
			if (lev < me->query_skill(skills[i]))
			{
				sk = skills[i];
				lev = me->query_skill(skills[i]);
			}
	}

	me->set("neili", 0);
	
	message_combatd(HIY "$N" HIY "������Ц������������������"
                        "�½���Ȼ�����ƺ�Ҫ�˷��ȥ��ƮƮ���ɣ�\n" NOR, me);

	me->add_temp("apply/" + sk, skill / 5);
	
	me->set_temp("power", 1);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}
