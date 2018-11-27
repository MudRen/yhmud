// sanda.c 三板斧
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
		object weapon;	
		string msg;
		int ap, dp;
		int damage, count;
		int zhuan;
		
		zhuan = me->query("reborn/count");
		
		if (! target) target = offensive_target(me);
		
		if (! me->is_fighting())
			return notify_fail("「三板斧」只能在战斗中使用。\n");
			
		if (! objectp(weapon = me->query_temp("weapon")) ||
				(string)weapon->query("skill_type") != "hammer")
			return notify_fail("你使用的武器不对。\n");
			
		if (me->query_skill_mapped("hammer") != "leiting-fu")
            return notify_fail("你没有激发雷霆斧法，不能使用「三板斧」。\n");

		if ((int)me->query_str() < 40)
			return notify_fail("你现在的臂力不够，目前不能使用「三板斧」！\n");

		if ((int)me->query_skill("force") < 200)
			return notify_fail("你的内功火候不够，难以施展「三板斧」！\n");

		if ((int)me->query_skill("hammer", 1) < 180)
			return notify_fail("你的棍法修为不够，不会使用「三板斧」！\n");

		if ((int)me->query("neili") < 500)
			return notify_fail("你的真气不足！\n");
		
		if (! living(target))
			return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

		ap = me->query_skill("hammer");
        dp = target->query_skill("force");
		damage = me->query_skill("leiting-fu", 1);
		damage += random(damage);
		
		// 第一斧劈脑袋
		ap += me->query("str") * 4;
		damage += (me->query_str() - zhuan * 20) * 4;
		count = me->query_str() - zhuan * 10;
		
        msg = "\n" HIW "$N" HIW "喝道：劈脑袋！\n" NOR;
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "一楞，只见$P" HIR "身形"
                                           "一闪，已晃至自己跟前，躲闪不及，被这"
                                           "招击个正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷静非凡，丝毫不为这奇幻的招数"
                       "所动，凝神抵挡，不漏半点破绽！\n" NOR;
        }

        // 第二斧鬼剔牙
        ap += me->query("dex") * 6;
        dp = target->query_skill("parry");
		damage += (me->query_dex() - zhuan * 20) * 6;
		count += me->query("dex") - zhuan * 10;
        msg += "\n" YEL "$N" YEL "喝道：鬼剔牙！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "一楞，只见$P" HIR "身形"
                                           "一闪，已晃至自己跟前，躲闪不及，被这"
                                           "招击个正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷静非凡，丝毫不为这奇幻的招数"
                       "所动，凝神抵挡，不漏半点破绽！\n" NOR;
        }

        // 第三斧掏耳朵
        ap += me->query("con") * 8;
        dp = target->query_skill("dodge");
		damage += (me->query_con() - zhuan * 20) * 8;
		count += me->query("con") - zhuan * 10;
        msg += "\n" HIM "$N" HIM "喝道：掏耳朵！\n" NOR;
        if (ap * 1 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, count,
                                           HIR "$p" HIR "一楞，只见$P" HIR "身形"
                                           "一闪，已晃至自己跟前，躲闪不及，被这"
                                           "招击个正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷静非凡，丝毫不为这奇幻的招数"
                       "所动，凝神抵挡，不漏半点破绽！\n" NOR;
        }

        me->start_busy(2 + random(3));
        me->add("neili", -200 - random(100));
        message_combatd(msg, me, target);
        return 1;
}
