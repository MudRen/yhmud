#include <ansi.h>
#include <combat.h>

#define ZHEN "��" HIW "�桤������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
//      object weapon;
        int ap, dp, damage, jia;
        int i, count;
        string msg;

        if (userp(me) && ! me->query("can_perform/longxiang-gong/zhen"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(ZHEN "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("longxiang-gong", 1) < 390)
                return notify_fail("��������������Ϊ����������ʩչ" ZHEN "��\n");

        if (me->query("max_neili") < 7000)
                return notify_fail("���������Ϊ���㣬����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("unarmed") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊȭ�ţ�����ʩչ" ZHEN "��\n");

        if (me->query_skill_mapped("force") != "longxiang-gong")
                return notify_fail("��û�м������������Ϊ�ڹ�������ʩչ" ZHEN "��\n");

        if (me->query_skill_prepared("unarmed") != "longxiang-gong")
                return notify_fail("��û��׼��ʹ�����������������ʩչ" ZHEN "��\n");

        if (me->query("neili") < 1000)
                return notify_fail("�����ڵ��������㣬����ʩչ" ZHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ��ŭ������������������������ޣ�ȫ���ʱ�"
              "�ŷ����������ڶ���������$N" HIY "\n�ķ�������ʯ�䣬$N" HIY "˫"
              "ȭ��Я���������֮�Ʊ����������������ﳾ�����������ھ�ѧ��\n\n" NOR;

        msg += HIW
        "        ��      ����           ��        ��           ��    ������������\n"
        "    �����    ��  ��       ��������������������       ��       ��    ��\n"
        "    ��    ��    ��  ��           ��        ��       ����������  ��    ��\n"
        "    �� �� �� ���    ���          ��                 ������  ������ ������\n"
        "  �������             ������������������������  �� �� ��  ����     ��\n"
        "    ��    ��   �����         ��                   �� �� ��  �� ��   ��\n"
        "    �� �� ��    ��  ��        �� ��������������      �� �� �� ��   ����\n"
        "    ��    ��     ���       ��   ��          ��         ��   ��     ��\n"
        "   ��    ��   ���  ���         ��������������         ��  ��  ����������\n\n" NOR;

        msg += HIY "$N" HIY "һ��������������ű�ӿ���˵ڶ���������������������"
               "���಻����������磡ֱ��$N" HIY "\n��ʮ�����������꣬����������"
               "�ŵ�������������ˣ���$n" HIY "��ʱȴ���Ǳ��޿ɱܣ�\n\n" NOR;

        ap = me->query_skill("unarmed") + me->query("con") * 10;
        dp = target->query_skill("parry") + target->query("dex") * 10;

        if (ap * 2 / 3 + random(ap) > dp)
{
        if (me->query("max_neili") / 2 + random(me->query("max_neili") / 2) > target->query("max_neili") * 5/4)
	{
                msg += HIR "$n" HIR "ȫȻ�����赲������$N"
                       HIR "һ�»��÷������صĵ����ڵ��ϡ�\n" NOR;
	        me->add("neili", -100);
          me->start_busy(1);

	        message_combatd(msg, me, target);

                target->unconcious();

        	return 1;
	} else
        {       
        	jia = me->query("jiali");
                damage = ap / 2 + random(jia * 5);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                                   HIR "$n" HIR "�������ܣ��ٱ�$N" HIR 
                                HIR "һ�»��У���������������\n" NOR);
                        msg += HIR "$n" HIR "��$N" HIR "����ƣ�һʱ���������ֵ���������������\n" NOR;
                        count = ap / 10;
        } 
} else
        {
                msg += HIY "$n" HIY "��$N" HIY "����Ѹ��֮�������ѷ�������"
                       "æ��������С�ĵֵ���\n" NOR;
                count = 0;
        }
 
        message_combatd(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -600);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -count);

        return 1;

}