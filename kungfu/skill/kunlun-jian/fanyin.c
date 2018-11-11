#include <ansi.h>
#include <combat.h>

#define FANYIN "��" MAG "��������" NOR "��"

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, jing_wound;

        if (userp(me) && ! me->query("can_perform/kunlun-jian/fanyin"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(FANYIN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" FANYIN "��\n");

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return notify_fail("��ĵ��ټ������Ҳ�������, ����ʩչ" FANYIN "��\n");

        if (me->query_skill("kunlun-jian", 1) < 120)
                return notify_fail("������ؽ����ȼ�����, ����ʩչ" FANYIN "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ���Ϊ����������ʩչ" FANYIN "��\n");

        if (me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ��ǳ������ʩչ" FANYIN "��\n");

        if (me->query("neili") < 300)
                return notify_fail("�����������������ʩչ" FANYIN "��\n");

        if (me->query_skill_mapped("sword") != "kunlun-jian")
                return notify_fail("��û�м������ؽ���������ʩչ" FANYIN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = MAG "$N" MAG "΢΢һЦ�����ֺ��ս�����������"
              "ָ��׼" + weapon->name() + NOR + MAG "����"
              "���ᵯ��������΢��������������\n��ʱ����һ"
              "��������������\n" NOR;

        ap = me->query_skill("sword") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");
		skill = me->query_skill("tanqin-jifa") + me->query_skill("chuixiao-jifa");
		ap += skill;
		dp += target->query_skill("tanqin-jifa") / 2 + target->query_skill("chuixiao-jifa") / 2;
        if (dp < 1) dp = 1;
        if (random(ap) > dp / 2)
        {
                me->add("neili", -200);
                jing_wound = ap / 2 + random(ap / 2) + random(skill);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK,
                       jing_wound, 80, MAG "$n" MAG "��ʱֻ��������"
                       "����������һ��̽�˫����ɲ�Ǽ�ͷ��Ŀѣ��ȫ��"
                       "��ʹ��\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                me->add("neili", -50);
                msg += CYN "����$n" CYN "��æ���ľ�������������˿"
                       "������$N" CYN "�����ĸ��š�\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}

