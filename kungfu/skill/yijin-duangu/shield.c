// shield.c С����������
/*
yijin-duangu
dafumo-quan
cuixin-zhang
jiuyin-baiguzhao
shexing-lifan
yinlong-bian
*/

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int skill;
	int lvlf, lvlp, lvlc, lvlz, lvld, lvlb;

	lvlf = me->query_skill("yijin-duangu", 1);
	lvlp = me->query_skill("dafumo-quan", 1);
	lvlc = me->query_skill("cuixin-zhang", 1);
	lvlz = me->query_skill("jiuyin-baiguzhao", 1);
	lvld = me->query_skill("shexing-lifan", 1);
	lvlb = me->query_skill("yinlong-bian", 1);
	skill = (lvlf + lvlp + lvlc + lvlz + lvld + lvlb) / 6;
	
	if (target != me)
		return notify_fail("��ֻ�����׽�͹��������Լ��ķ�������\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if (lvlf < 200 || lvlp < 200 || lvlc < 200 || lvlz < 200 || lvld < 200 || lvlb < 200)
		return notify_fail("���С��������Ϊ������\n");
	
	if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao" ||
		me->query_skill_prepared("strike") != "cuixin-zhang" ||
		me->query_skill_mapped("whip") != "yinlong-bian" ||
		me->query_skill_mapped("unarmed") != "dafumo-quan" ||
		me->query_skill_mapped("dodge") != "shexing-lifan")
		return notify_fail("�㻹û��׼����С�����񹦣��޷������Լ��ķ�������\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "˫��ƽ�ٹ���������С����"
                        "��������ʱȫ������������֮�У�\n" NOR, me);

	me->add_temp("apply/armor", skill / 4);
	me->add_temp("apply/force", skill / 4);
	me->add_temp("apply/dodge", skill / 4);
	me->add_temp("apply/parry", skill / 4);
	me->add_temp("apply/strike", skill / 4);
	me->add_temp("apply/claw", skill / 4);
	me->add_temp("apply/whip", skill / 4);
	me->add_temp("apply/damage", skill / 12);
	me->add_temp("apply/unarmed_damage", skill / 12);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 4 :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("shield"))
        {
        	me->add_temp("apply/armor", -amount);
			me->add_temp("apply/force", -amount);
			me->add_temp("apply/dodge", -amount);
			me->add_temp("apply/parry", -amount);
			me->add_temp("apply/strike", -amount);
			me->add_temp("apply/claw", -amount);
			me->add_temp("apply/whip", -amount);
			me->add_temp("apply/damage", -amount / 3);
			me->add_temp("apply/unarmed_damage", -amount / 3);
			me->delete_temp("shield");
        	tell_object(me, "���С��������������ϣ��������ջص��\n");
        }
}
