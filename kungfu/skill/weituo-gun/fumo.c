// fumo.c Τ�ӷ�ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int damage;
  //if (userp(me) && ! me->query("can_perform/weituo-gun/fumo"))
  //              return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ��Τ�ӷ�ħ����\n");
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail("��Τ�ӷ�ħ��ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("weituo-gun", 1) < 140)
		return notify_fail("���Τ�ӹ�����Ϊ������Ŀǰ����ʹ��Τ�ӷ�ħ��\n");

	if (me->query("neili") < 800)
		return notify_fail("�����������������ʹ��Τ�ӷ�ħ��\n");

        if (me->query_skill_mapped("club") != "weituo-gun")
                return notify_fail("��û�м���Τ�ӹ���������ʹ��Τ�ӷ�ħ��\n");

        if (me->query("shen") < 10000)
                return notify_fail("���������㣬�������Τ�ӷ�ħ�ľ��衣\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "��ɫ��ͣ�����һ�ɴ���֮�⣬���е�" + weapon->name() +
              HIY "������������Գ����Τ������\n������䣬����ס$n" + HIY "��\n" NOR;

        if (target->is_bad())
        {
                ap = me->query("shen") / 1000;
                if (ap > 100) ap = (ap - 100) / 4 + 100;
                if (ap > 200) ap = (ap - 200) / 4 + 200;
                if (ap > 300) ap = (ap - 300) / 4 + 300;
                if (ap > 400) ap = 400;
                msg += HIR "$n" HIR "ƽ�������٣����˴���˾������в�����Ȼ��\n" NOR;
        } else
                ap = 0;
        ap += me->query_skill("club"); 
        dp = target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap / 2);
                me->add("neili", -300);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "���ֻ��$p" HIR "һ���ҽУ���$P"
                                           "һ���Ӵ���Ҫ��������һ�����̣����Ƕ�����Ѫ����\n" NOR);

        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "ǿ������û�б�$P"
                       CYN "���Ի�Ӳ�����ļ�ס��$P" CYN "��һ�У�\n"NOR;
        }
	message_combatd(msg, me, target);

	return 1;
}
