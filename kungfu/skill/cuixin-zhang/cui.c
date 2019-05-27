#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define CUI "��" HIW "��������" NOR "��"
string final(object me, object target, int count);
void cuixin_end(object me, object target, int count);

int perform(object me)
{
        string msg;
        object /*weapon,*/ target;
        int ap, dp;
        int damage, lvl, count; 

        if (playerp(me) && ! me->query("can_perform/cuixin-zhang/cui"))
                return notify_fail("��ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(CUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʹ�ã�\n");
 
        lvl = me->query_skill("cuixin-zhang", 1);

        if (lvl < 120)
                return notify_fail("��Ĵ����ƻ��������죬�޷�ʩչ" CUI "\n");

        if (me->query_skill("force") < 120)
                return notify_fail("����ڹ����̫�ͣ��޷�ʹ��" CUI "��\n");

        if (me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ��" CUI "��\n");
 
        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
		   
		if (target->query_temp("cuixin"))
                return notify_fail("�Է��Ѿ��мܻ�ɢ���ŵ������ɡ�\n");

        msg = HIR "$N" HIR "�������ƣ�����һ����Х��ɲ�Ǽ�˫�ƽ���һ��"
                  "���������ġ����������ھ�ֱ��$n" HIR "��\n"NOR;

        
		ap = me->query_skill("strike") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");
		count = lvl / 8;

        if (dp < 1) dp = 1;

        if ( ap * 11 / 20 + random(ap) > dp)
        {
                msg += HIR "ֻ��$n" HIR "�ҽ�һ����ֻ������������Ŀ���������̱����\n" NOR;
                target->affect_by("cuixin_zhang",
                        ([ "level" : me->query("jiali") + random(me->query("jiali")),
                           "id"    : me->query("id"),
                           "duration" : lvl / 50 + random(lvl / 20) ]));

				damage = ap / 2 + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, random(15) + 40,
                                          (: final, me, target, count :));
				
				me->add("neili", -260);
                me->start_busy(2);
        }
        else
        {
				
				msg += HIY "$p��$P������ӿ���������ĵĶ㿪����������һ����\n" NOR;
				me->add("neili", -120);
				me->start_busy(3);
        }
        message_combatd(msg, me, target);
		
		

        return 1;
}

string final(object me, object target, int count)
{
        target->set_temp("cuixin", 1);
		target->add_temp("apply/parry", -count);
        call_out("cuixin_end", 5 + random(count / 5), me, target, count);
}

void cuixin_end(object me, object target, int count)
{
        if (target && target->query_temp("cuixin"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "�������������𽥻ָ���֪����\n" NOR, target);
						tell_object(target, HIY "��е������ҵ���������ƽ����������\n" NOR);
                }
				target->delete_temp("cuixin");
				target->add_temp("apply/parry", count);
		}
	return;
}