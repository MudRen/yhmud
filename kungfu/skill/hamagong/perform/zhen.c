#include <ansi.h>
#include <combat.h>

#define ZHEN "��" HIW "������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage, poison, hamagong_effect;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��󡹦" ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("hamagong", 1);
		poison = me->query_skill("poison", 1);

        if (skill < 240)
                return notify_fail("��ĸ�󡹦��Ϊ�����������ʹ��" ZHEN "��\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("���������Ϊ��������޷�ʩչ" ZHEN "��\n");

        if (me->query("neili") < 800)
                return notify_fail("��������������޷�����" ZHEN "��\n");

        if (me->query_skill("strike") < 200)
                return notify_fail("����Ʒ�������죬�޷�ʩչ" ZHEN "��\n");

        if( me->query_temp("weapon") )
                return notify_fail("�������ֲ���ʹ��" ZHEN "��\n");

        if (me->query_skill_prepared("strike") != "hamagong" ||
            me->query_skill_mapped("strike") != "hamagong")
                return notify_fail("������Ƚ���󡹦�������Ʒ�֮�У���������" ZHEN "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIB "$N���Ӷ��£�����ƽ�ƶ�����ʹ������$N��ƽ�����ġ������졹���У��Ʒ�ֱ��$n��ȥ��\n" NOR;
        message_combatd(msg, me, target);

        ap = me->query_skill("force");
        dp = (target->query_skill("force") + target->query_skill("parry") + target->query_skill("dodge") + target->query_skill("yiyang-zhi") ) / 3;

		damage = ap;
		
		if(skill > 500)
			damage += poison;
		else
			damage += poison * skill / 500;

		if(me->query_temp("reverse"))
		        hamagong_effect = (int)(skill / 20);
		else
			    hamagong_effect = (int)(skill / 30);

        if (ap * 2 / 3 + random(ap) > dp)
        {
			    damage += random(damage / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50 + random(hamagong_effect),
                                           HIR "$n" HIR "����$N��ʹ����˹�����ʽ����æ���Ƶֵ���"
                                               "���$N��󡹦�ھ�����Ϯ�룬$nȫ���ʱ�е�һ��˺�Ѱ��ʹ�ࡣ\n" NOR);
        }else
        {
                msg = HIY "����$n����һ��΢�����������ȴ�ѱ��Ƶú�����������֪�����æԾ�����ߡ�\n" NOR;
        }
        message_combatd(msg, me, target);

        msg = HIB "$N���ƾ���δ��������Ҳ�����Ƴ������������" ZHEN "�Ʒ���ɽ������ӿ��$n��\n"NOR;
        message_combatd(msg, me, target);
	   
        if (ap * 3 / 5 + random(ap) > dp)
        {
			    damage += random(damage / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(hamagong_effect),
                                           HIR "$n" HIR "ֻ�����У������ޱȣ�����Ī�⣬"
                                               "����һ����ȴ��Ȼ�����һ������͸�Ƕ�����\n" NOR);
        }else
        {
                msg = HIY "$n��Ϣδ�����־�һ�ɾ��������������æԾ�����ߣ��Ǳ��رܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        msg = HIB "$N˫��һ�ţ�˫���ಢ��ǰ�����Ƴ���$n��ͬ��ǰ��Բ����ȫ��" ZHEN "��������֮�£�\n"NOR;
        message_combatd(msg, me, target);

         if (ap * 11 / 20 + random(ap) > dp)
        {
			    damage += random(damage);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(hamagong_effect),
                                           HIR "$n" HIR "ȫȻ�����赲������$N" HIY "˫�ƻ��÷������صĵ����ڵ��ϡ�\n" NOR);
        }else
        {
                msg = HIY "$n�þ�ȫ����������һ��һ����ҡҡ������վ��������������㿪����������һ����\n" NOR;
        }
        message_combatd(msg, me, target);

        me->start_busy(3 + random(4));
        me->add("neili", -400 - random(400));

        return 1;
}

