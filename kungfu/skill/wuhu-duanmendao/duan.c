#include <ansi.h>
#include <combat.h>

#define DUAN "��" HIW "���־�" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon, ob;
	string msg/*, string1*/;
	int lev;
 
        if (userp(me) && ! me->query("can_perform/wuhu-duanmendao/duan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
		return notify_fail(DUAN "ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԣ�����ʩչ" DUAN "��\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����ڵ��������㣬����ʩչ" DUAN "��\n");

	if ((int)me->query_skill("wuhu-duanmendao", 1) < 50)
		return notify_fail("����廢���ŵ��������ң�����ʩչ" DUAN "��\n");

        if (me->query_skill_mapped("blade") != "wuhu-duanmendao")
		return notify_fail("��û�м����廢���ŵ�������ʩչ" DUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "��Ȼ���أ�ʹ���廢���ŵ����ϡ��־�����ʱһƬ�׹�"
              "��ǰֱ����ȥ��\n" NOR;
	message_combatd(msg, me);

	me->clean_up_enemy();
	ob = me->select_opponent();
	lev = me->query_skill("wuhu-duanmendao", 1);

	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	if (random(2) == 1)
		{
			me->add_temp("apply/attack", lev/2); 
			me->add_temp("apply/damage", lev/2);
			message_combatd(HIW  "$N�������������ĵ���\n" NOR, me, target); 
			COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
			me->add_temp("apply/attack", -lev/2); 
			me->add_temp("apply/damage", -lev/2);
			
			if (random(2) == 1)
			{
				me->add_temp("apply/attack", lev); 
				me->add_temp("apply/damage", lev);
				message_combatd(RED  "$N�������������嵶��\n" NOR, me, target); 
				COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
				me->add_temp("apply/attack", -lev); 
				me->add_temp("apply/damage", -lev);
			}
			
		}
	

	me->add("neili", -100);
	me->start_busy(1 + random(3));
	return 1;
}