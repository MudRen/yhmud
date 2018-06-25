#include <ansi.h>
#include <combat.h>

#define FENG "��" HIR "������Ѩ" NOR "��"

inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object target, anqi;
        int skill, count, ap, dp;
		
		//anqi = me->query_temp("handing");
		skill = me->query_skill("jinshe-zhui", 1);
		
		if (! objectp(anqi = me->query_temp("handing"))
           || (string)anqi->query("skill_type") != "throwing")
		{
			count = 0;
		}	else
		{
			count = anqi->query("weapon_prop/damage");
		}
				
		if (me->query_temp("jinshe/feng"))
		return notify_fail("����ù�������Ѩ��û�����žͳ��С�\n");

		if (! target) target = offensive_target(me);
		if (! target ||	! me->is_fighting(target))
		return notify_fail("������Ѩֻ����ս����ʹ�á�\n");

		if (me->query_skill("force") < 150)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" FENG "��\n");

        if (skill < 100)
                return notify_fail("��Ľ���׶����Ϊ���ޣ�����ʩչ" FENG "��\n");

        if (me->query("neili") < 500)
                return notify_fail("�����ڵ��������㣬����ʩչ" FENG "��\n");

        if (me->query_skill_mapped("throwing") != "jinshe-zhui")
                return notify_fail("��û�м�������׶��������ʩչ" FENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "����һԾ��������$n" HIR "��ǰ������$n" HIR "ҪѨ��\n" NOR;

        ap = me->query_skill("throwing");
        dp = target->query_skill("force");
		
        if (ap / 2 + random(ap) > dp)
        {
			
			msg += HIR "$p" HIR "΢΢һ�㣬�ѱ�$N" HIR 
				"����ҪѨ����ʱ̱������������̱����\n" NOR;
				me->add("neili", -200);
                me->start_busy(1);
				me->set_temp("jinshe/feng", 1);
				me->start_call_out((: call_other, __FILE__, "feng_end", me :), 5);
			
				switch (random(6))
				{
					case 0:
							target->add_temp("apply/damage", -skill / 6);
							break;
					
					case 1:
							target->add_temp("apply/dodge", -skill / 4);
							break;
					
					case 2:
							target->add_temp("apply/parry", -skill / 4);
							break;
					
					case 3:
							target->add_temp("apply/force", -skill / 4);
							break;
					
					case 4:
							target->add_temp("apply/armor", -skill / 4);
							break;
					
					default:
							target->add_temp("apply/defense", -skill / 4);
							break;	
				}
				
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ�������һһ��⣬û¶���������\n" NOR;
                me->add("neili", -50);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
		
        return 1;
}

void feng_end(object me)
{
        me->delete_temp("jinshe/feng");
}
