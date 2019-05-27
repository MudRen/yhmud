// �ռ����У������ơ���
#include <ansi.h>
#include <combat.h>

#define LANG "��" HIR "��ڤ˫��" NOR "��"

inherit F_SSERVER;

string final1(object me, object target, int lvl);
string final2(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl/*, p*/;
		
		float improve;
		int lvls, m, n;
		string martial;
		string *ks;
		martial = "strike";

        if (userp(me) && ! me->query("can_perform/xuanming-zhang/xing"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LANG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(LANG "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 220)
                return notify_fail("�����ڤ�񹦻�򲻹����޷�ʩչ" LANG "��\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 220)
                return notify_fail("�����ڤ���Ʋ����������޷�ʩչ" LANG "��\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("���������Ϊ���㣬�޷�ʩչ" LANG "��\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("��û�м�����ڤ��Ϊ�ڹ����޷�ʩչ" LANG "��\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("��û��׼����ڤ���ƣ��޷�ʩչ" LANG "��\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("��������������޷�ʩչ" LANG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "Ĭ����ڤ�񹦣�չ�����С�" HIR "��ڤ˫��" HIW "������Ȼ������"
              "��ǰ��˫��������Ʒ������ޱȣ���δ������������˲Ϣ��˫��������$n" HIW "��\n"NOR;  

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
		
		improve = improve * 3 / 100 / lvls;
			  
        lvl = me->query_skill("xuanming-zhang", 1);

        ap = me->query_skill("strike") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("force");
		
		ap += ap * improve;

        me->start_busy(4);

        // ��һ��

        msg += HIM "\n$N" HIM "��������һת��������ǰ����Ȼ��ֱϮ$n" HIM "���š�\n" NOR;
        if (ap * 3 / 5 + random(ap) > dp)
        { 
                damage = ap / 2 + random(ap);
                me->add("neili", -200);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                          (: final1, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "����$N" HIY "������ӿ����æ����Ծ����\n" NOR;
                me->add("neili", -100);
        }
        message_sort(msg, me, target);
         
        // �ڶ���
        msg = HIM "\n$N" HIM "����һ���������ƽ����������絽�Ƶ���������$n" HIM "�ؿڡ�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap * 3 / 5 + random(ap);
                me->add("neili", -300);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                          (: final2, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "����$N" HIY "������ӿ����æ����Ծ����\n" NOR;
                me->add("neili", -150);
        }
        message_sort(msg, me, target);

        return 1;
}

string final1(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 3,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "�������㣬ȴ��$N" HIR "ͻȻ�Ƶ�$p" HIR "���$n" HIR "����һ"
                   "�����������ƣ��پ�������һ�ɺ������𣬾�������������\n" NOR;

}

string final2(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 3,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "����$N" HIR "�����ѹ���������������ͻȻ���ؿ�һ�𣬲�������"
               "�п࣬�ٸ��ؿڴ�һ�ɺ������𣬾�������������\n" NOR;

}