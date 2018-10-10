
#include <ansi.h>
#include <combat.h>

#define LONG "��" HIC "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int neili, hit_point, time;
		
		float improve;
		int lvls, m, n;
		string martial;
		string *ks;
		martial = "sword";

        if (userp(me) && ! me->query("can_perform/poyang-jian/long"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" LONG "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" LONG "��\n");

        if (me->query_skill("poyang-jian", 1) < 180)
                return notify_fail("���������⽣��Ϊ����������ʩչ" LONG "��\n");

        if ((int)me->query_skill("dodge") < 200)
                return notify_fail("����Ṧ��򲻹�������ʩչ" LONG "��\n"); 

        if ((int)me->query("max_neili") < 2700)
                return notify_fail("���������Ϊ���㣬����ʩչ" LONG "��\n");

        if (me->query("neili") < 350)
                return notify_fail("�����������������ʩչ" LONG "��\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("��û�м���������⽣������ʩչ" LONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
			
		lvls = to_int(pow(to_float(me->query("combat_exp") * 10), 1.0 / 3));
		lvls = lvls * 4 / 5;
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
		
		improve = improve * 5 / 100 / lvls;
        
        if (! me->query("real_perform/poyang-jian/long"))
        {
                msg = HIY "\nֻ��$N" HIY "����" + weapon->name() + HIY
                      "��ɨ������ʩ�����С�" HIC "��������" HIY "����"
                      "�����ݺᣬ����һ���������Ѷ���������$n\n" HIY "��" NOR;
               
                neili = 220;
                hit_point = 55;
                time = 2 + random(2);
        }

        else
        {
                msg = HIW "\n����$N" HIW "����" + weapon->name() + HIW 
                      "�԰���к��������������ֱ������һ������һ�㣬��"
                      "��������⽣�ľ��衸" HIY "��������" HIW "����һ"
                      "��������$N" HIW "ʹ�������ߣ�����������Ȼ������$n\n" 
                      HIW "��" NOR;

                neili = 300;
                hit_point = 80;
                time = 3 + random(4);
        }
        message_sort(msg, me, target);

        ap = me->query_skill("sword");

        dp = target->query_skill("parry");
		
		ap += ap * improve;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                me->add("neili", -neili);
                me->start_busy(time);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, hit_point,
                                           HIR "$n" HIR "�������������ͣ� �赲��"
                                           "���� ��ʱ��" + weapon->name() + HIR 
                                           "���ˣ��಻���ԡ�\n" NOR);
        } else
        {
                me->add("neili", -150);
                me->start_busy(1 + random(2));
                msg = CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                      CYN "$N" CYN "�������͵�һ�С�\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}
