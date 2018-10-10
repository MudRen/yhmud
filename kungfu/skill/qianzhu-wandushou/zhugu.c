#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int lvl, poison;
        int damage;
		
		float improve;
		int lvls, m, n;
		string martial;
		string *ks;
		martial = "hand";

	if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/qianzhu-wandushou/zhugu"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ������ˣ�\n");

	if (! target || ! target->is_character())
		return notify_fail("��Ҫ��˭ʩչ��ƾ���\n");

	if (target->query("not_living"))
		return notify_fail("��������ǲ��ǻ��ˡ�\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ��������ʩչ��ƾ���\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 130)
                return notify_fail("���ǧ��������Ϊ���������ڻ��޷�ʩչ��ƾ���\n");

        if (me->query_skill_mapped("hand") != "qianzhu-wandushou")
                return notify_fail("��û�м���ǧ�����֣��޷�ʩչ��ƾ���\n");

        if (me->query("neili") < 400)
                return notify_fail("������������������޷�ʩչ��ƾ���\n");

        msg = HIB "$N" HIB "ʩ����ƾ���ֻ��һ�ƺ�����"
              "ָ��͸����ֻһ����û����$n" HIB "��ü�ģ�\n" NOR;
		
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
		
		if (me->query("family/family_name") == "�嶾��")
			improve += 0.1;

        lvl = me->query_skill("hand");
		poison = me->query_skill("poison");
		
		poison = (int)poison / 15;	  
		lvl += lvl * improve;
		
        if (lvl / 2 + random(lvl) > target->query_skill("force"))
        {
                damage = lvl + random(lvl / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50 + poison,
                                           HIR "$p" HIR "ֻ����һ����ɽ�ľ���˳ָ����"
                                           "��������ֻ����ȫ������ܣ����ۡ���һ��"
                                           "�³�һ�ں�Ѫ��\n" NOR);
                target->affect_by("qianzhu_wandushou",
                                  ([ "level" : lvl * 2 / 3 + random(poison),
                                     "id"    : me->query("id"),
                                     "duration" : lvl / 40 + random(lvl / 18) ]));
                me->add("neili", -200);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�����������������ڹ�"
                       "��������һָ�Ķ�����\n" NOR;
                me->start_busy(4);
                me->add("neili", -80);
        }
        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}
