//������ȭһ������pfm
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int i, n;
//	object weapon;
	string *msgs = ({ 
			"Ц���߽�һָ�ɣ�",
			"Ҷ��������ɽ��",
			"�����������ͷ��",
			"����̫����������",
			"���¹����忴�أ�",
			"ãã��ˮ�����죡",
			"Ц��Ҷ�俴���ƣ�",
			"���׻�������ˮ��",}); 
	n = 2 + random(me->query_skill("mizong-houquan", 1) / 40);
	if (n > 8) n = 8;
	
	if (me->is_busy())
		return notify_fail("������û�գ���\n");
	
	if ((int)me->query_skill("mizong-houquan", 1) < 200)
		return notify_fail("��ĺ�ȭ�������!\n");
	
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���Ƹ����ۡ�ֻ�ܿ���ʹ�á�\n");		

	if (!target ) target = offensive_target(me);
	
	if (!target || !target->is_character() || !me->is_fighting(target))
		return notify_fail("���Ƹ����ۣ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	if ((int)me->query("neili", 1) < 500)
		return notify_fail("����������̫��������ʹ�á��Ƹ����ۡ���\n");
	
	if (me->query_skill_prepared("unarmed") ||
		me->query_skill_prepared("strike"))
			n -= 3;
		
	msg = HIY  "$Nʹ���������µģ����ٺ�ȭ�ݣ�һ��[�Ƹ�����]����˵�һʽ��\n" NOR;
	message_combatd(msg, me, target);
	
	for (i = 1; i < n; i++)
	{
		me->add_temp("apply/attack", i * 50);
        me->add_temp("apply/unarmed_damage", i * 10);
		msg = msgs[random(sizeof(msgs))];
		msg = HIC "\n��" + chinese_number(i) + "��---" + msg + NOR;
		message_vision(msg, me, target);
		COMBAT_D->do_attack(me, target);
		me->add_temp("apply/attack", -i * 50);
        me->add_temp("apply/unarmed_damage", -i * 10);
		me->add("neili", -50);
	}
	me->start_busy(random(i));
	return 1;
}