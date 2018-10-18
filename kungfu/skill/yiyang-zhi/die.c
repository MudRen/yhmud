#include <ansi.h>
#include <combat.h>

#define DIE "��" HIR "��������" NOR "��"

inherit F_SSERVER;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ",
"�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ", "����Ѩ", "����Ѩ", "���Ѩ",
"�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", }); 

int perform(object me, object target)
{
        int damage;
        string msg, wp;
        object weapon;
        int ap, dp;
		
		float improve;
		int lvl, m, n;
		string martial;
		string *ks;
		martial = "finger";

        if (userp(me) && ! me->query("can_perform/yiyang-zhi/die"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DIE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(DIE "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("yiyang-zhi", 1) < 200)
                return notify_fail("��һ��ָ��������죬����ʩչ" DIE "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" DIE "��\n");

        if (me->query_skill_mapped("finger") != "yiyang-zhi")
                return notify_fail("��û�м���һ��ָ��������ʩչ" DIE "��\n");

        if (me->query_skill_prepared("finger") != "yiyang-zhi")
                return notify_fail("��û��׼��һ��ָ��������ʩչ" DIE "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" DIE "��\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ���㣬����ʩչ" DIE "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����ڵ���������������ʩչ" DIE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        lvl = to_int(pow(to_float(me->query("combat_exp") * 10), 1.0 / 3));
		lvl = lvl * 4 / 5;
		ks = keys(me->query_skills(martial));
		improve = 0;
		n = 0;
		//������5�����ܵļӳ�
		for (m = 0; m < sizeof(ks); m++)
		{
			if (SKILL_D(ks[m])->valid_enable(martial))
			{
				n += 1;
				improve += (int)me->query_skill(ks[m], 1);
				if (n > 4 )
					break;
			}
		}
		
		improve = improve * 5 / 100 / lvl;

        ap = me->query_skill("finger");
        dp = target->query_skill("parry");
		
		ap += ap * improve;
		damage = ap + random(ap);
		
		msg = HIW "ͻȻ��";

        if (objectp(weapon = target->query_temp("weapon")))
        {
                wp = weapon->name();
                msg += "$N" HIW "��ָһ�����$n" HIW "����" + wp + NOR + HIW
                       "�������ϡ�" HIY "���" HIW "������" HIY "����" HIW "��"
                       "����" HIY "����" HIW "����Ѩ��\n" NOR;

                ap = me->query_skill("finger");
                dp = target->query_skill("force");
				ap += ap * improve;

                if (ap / 3 + random(ap) > dp)
                {
                        msg += HIR "��ʱ��$n" HIR "ֻ��������һ�飬����" + wp +
                               HIR "��Ҳ�óֲ�ס�����ֵ��ڵ��ϡ�\n\n" HIW "��"
                               "����";
                        me->add("neili", -80);
                        weapon->move(environment(target));
                } else
                {
                        msg += CYN "����$n" CYN "������" + wp + NOR + CYN "ת"
                               "�����֣����ڻ�������һ�С�\n\n" HIW "������";
                        me->add("neili", -50);
                }
        }

        msg += "$N" HIW "������ָ��һʽ��" HIR "��������" HIW "���������ʱһ��"
               "����������ֱϮ$n" HIW "�ؿڣ�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

		target->add_temp("yiyang-zhi/die", 1);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        ap = me->query_skill("finger");
        dp = target->query_skill("dodge");
		ap += ap * improve;

        msg += "\n" HIW "����$N" HIW "̤ǰһ�������������ŷ�������һָ����$n" HIW
               "��ȥ��ָ���ݺᣬ��Ȼ���죡\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

		target->add_temp("yiyang-zhi/die", 1);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        ap = me->query_skill("finger");
        dp = target->query_skill("force");
		ap += ap * improve;

        msg += "\n" HIW "���$N" HIW "һ���ͺȣ���ָ���͡���һ�����������ָ��ͬ"
               "ʱ����$n" HIW "ȫ�����ҪѨ��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

		target->add_temp("yiyang-zhi/die", 1);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }

        if (target->query_temp("yiyang-zhi/die", 1) == 3
           && target->query("neili"))
        {
                msg += HIY "\n$n" HIY "��$N" HIY "��ָ���У�ȫ��������"
                       "ɢ������ƺӾ��̣�������ʱ��к������\n\n" NOR;
		target->set("neili", 0);
        }
        //me->start_busy(4 + random(4));
        me->start_busy(3 + random(3));
        me->add("neili", -400);
		target->delete_temp("yiyang-zhi/die");
        message_combatd(msg, me, target);

        if (! target->query("neili"))
                tell_object(target, HIC "��ֻ�������ھ��ƿտ���Ҳ��һʱ"
                                    "˵���������ܡ�\n" NOR);

        return 1;
}
