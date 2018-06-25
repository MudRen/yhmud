#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define DUO "��" HIC "�桤�������Ծ�" NOR "��"

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        //if (playerp(me) && ! me->query("can_perform/yinlong-bian/zhu"))
                //return notify_fail("��ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DUO "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹���ʹ����" DUO "��\n");

        if (me->query_skill("jiuyin-shengong", 1) < 220)
                return notify_fail("��ľ����񹦹���̫ǳ��ʹ����" DUO "��\n");

        if (me->query("neili") < 400)
                return notify_fail("��������������޷�ʹ��" DUO "��\n");

        if (me->query_skill_mapped("whip") != "jiuyin-shengong")
                return notify_fail("��û�м���������Ϊ�޷���ʹ����" DUO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "�����һЦ������" + weapon->name() +
              HIW "����һ��������Ȼ����$n" HIW "�����Ǿ����澭�е�"
             "���С�" HIC "�桤�������Ծ�" HIW "����\n" NOR;

        ap = me->query_skill("whip") + me->query_skill("force") + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("force") + target->query_skill("parry") + target->query_skill("martial-cognize", 1);

        if (ap * 11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                me->add("neili", -300);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "���$n" HIR "һ���ҽУ�δ�ܿ���$N"
                                           HIR "����ͼ������һ��Ӳ�����ؿڣ���Ѫ��"
                                           "����Ƥ��������\n" NOR);
                message_combatd(msg, me, target);
                
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����һԾ���𣬶�ܿ���"
                       CYN "$P" CYN "�Ĺ�����\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}
