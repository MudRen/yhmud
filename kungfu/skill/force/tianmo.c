// ��ħ�����
//��buff�£�����yun heal�����ܳ����쵤���޷����������

#include <ansi.h>
#define TIANMO "��" RED "��ħ�����" NOR "��"

inherit F_CLEAN_UP;

int exert(object me, object target)
{
	int shen, shen_lvl;
	int skill, count;
	int i;
	string *skills;
		
	shen = me->query("shen");
	shen_lvl = to_int(pow(to_float(-shen), 1.0 / 3));
	skill = me->query_skill("force", 1);
	count = (shen_lvl + skill) / 4;
	skills = keys(me->query_skill_map());
	
	if (me->query_temp("tianmo"))
		return notify_fail("���Ѿ����˹����ˡ�\n");
	
	if (me->query("str") < 30 && me->query("con") < 30)
		return notify_fail("������ʲ��ʺ�ʹ��" TIANMO "��\n");
	
	if ((int)me->query("neili") < 8000)
		return notify_fail("�����������!");

	if (me->query("shen") > -10000000)
		return notify_fail("�㻹û����ħ���޷�ʹ��" TIANMO "��\n");
	
	if ((int)me->query_skill("martial-cognize", 1) < 300 ||
		(int)me->query_skill("force", 1) < 300)
		return notify_fail("������л�����,�޷�ʹ��" TIANMO "��\n");

	me->set("neili", 0);
	me->receive_damage("qi", skill + shen_lvl + random(1000));
	me->receive_wound("qi", skill + shen_lvl + random(1000));
	me->receive_damage("jing", skill + shen_lvl + random(1000));
	me->receive_wound("jing", skill + shen_lvl + random(1000));

	message_combatd(RED "$N��ش��һ�������һ����Ѫ��"
                        "�������������� " TIANMO "��\n" NOR, me);

	me->add_temp("apply/str", me->query("str"));
	me->add_temp("apply/int", me->query("int"));
	me->add_temp("apply/con", me->query("con"));
	me->add_temp("apply/dex", me->query("dex"));
	//me->add_temp("apply/dodge", me->query("dex"));
	//me->add_temp("apply/parry", me->query("dex"));
	//me->add_temp("apply/force", me->query("con"));
	me->add_temp("apply/attack", count);
	me->add_temp("apply/damage", me->query("str") * 3);
	me->add_temp("apply/unarmed_damage", me->query("str") * 3);
	
	for (i = 0; i < sizeof(skills); i++)
    {
			me->add_temp("apply/" + skills[i], count / 2);
	}
	
	me->set_temp("tianmo", 1);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}
