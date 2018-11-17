#include <ansi.h>
#include <combat.h>

#define DONG "��" HIG "�󽭶�ȥ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon_t;
        int damage;
        int ap, dp;
        string wp, msg;

        if (userp(me) && ! me->query("can_perform/xuantie-jian/dong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" DONG "��\n");

        if ((int)me->query_skill("force") < 400)
                return notify_fail("����ڹ���򲻹�������ʩչ" DONG "��\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 200)
                return notify_fail("�����������������죬����ʩչ" DONG "��\n");

        if ((int)weapon->query_weight() < 25000
            && ! weapon->is_item_make())
                return notify_fail("�����е�" + wp + "��������������ʩչ" DONG "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����ڵ��������㣬����ʩչ" DONG "��\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("��û�м�����������������ʩչ" DONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�������񣬶�ʱһ��������������ȱŷ������ŵ�"
              "��һ������" + wp + HIW "\n�漴��վ����������Χ��ɳ����"
              "����ʩ��������������" HIG "�󽭶�ȥ" HIW "����\n"NOR;

        me->start_busy(2 + random(2));

        ap = me->query_skill("sword") + me->query_str() * 5;
        dp = target->query_skill("force") + target->query_str() * 5;
		weapon_t = target->query_temp("weapon");
		
		if (weapon_t && random(2) && weapon->query_weight() > 25000 &&
			(!weapon_t->is_item_make() || weapon_t->query("skill_type") != "hammer"))
		{
				msg += HIR "$n" HIR "ֻ����һ�ɴ�������������" + weapon_t->name() +
                       HIR "��Ҳ�óֲ�ס�����ֶ�����\n" NOR;
				me->add("neili", -120);
				weapon_t->move(environment(me));
                weapon_t->set("no_wield", weapon_t->name() + "�Ѿ�����ˣ�û��װ���ˡ�\n");
                weapon_t->set_name("�����" + weapon_t->name());
                weapon_t->set("value", 0);
		}

        if (me->query("character") == "��������" || me->query("character")=="������˫" )
                ap += ap / 5;
        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(1);
                damage = ap + random(ap);
                me->add("neili", -400);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
                                           HIR "���$n" HIR "�����мܣ�ȴ��$N" HIR
                                           "��һ����ķ��𣬿�����Ѫ���²�ֹ��\n" NOR);
        } else
        {
                msg += CYN "����$n" CYN "������$N"
                       CYN "����ͼ����æбԾ�ܿ���\n"NOR;
                me->add("neili", -200);
        }
        message_combatd(msg, me, target);

        return 1;
}


