#include <ansi.h>
#include <combat.h>

#define JU "��" HIR "��Ѫ����צ" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, lvl, i;
        string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/yintuoluo-zhua/chixue"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JU "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong")) 
                return notify_fail("������û�м��������ڹ�Ϊ�ڹ�������ʩչ" JU "��\n"); 
                
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(JU "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("yintuoluo-zhua", 1) < 200)
                return notify_fail("��������צ������죬����ʩչ" JU "��\n");

        if (me->query_skill_mapped("claw") != "yintuoluo-zhua")
                return notify_fail("��û�м���������צ������ʩչ" JU "��\n");

        if (me->query_skill_prepared("claw") != "yintuoluo-zhua")
                return notify_fail("��û��׼��������צ������ʩչ" JU "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" JU "��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" JU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = me->query_skill("claw") + me->query_skill("force") + me->query_str() + me->query_dex();
        dp = target->query_skill("parry") + target->query_skill("force")+ target->query_str() + target->query_dex();
        lvl = (int)me->query_skill("yintuoluo-zhua", 1);
        msg = HIW "\n$N" HIW "��ת����������˫�ֺ���צ�У�ʩ�����С�" HIR "��"
              "Ѫ����צ" HIW "����Ѹ���ޱȵ�ץ��$n" HIW "��\n" NOR;

        if (ap * 3 / 4 + random(ap) > dp)
        {

                if ( me->query("max_neili") > target->query("max_neili") * 2 && me->query("neili") > 500 )
                {
                msg += HIR "$n" HIR "ȫ��һ�������㲻�ȣ���$N"
                       HIR "��һצץ�õ����ڵ��ϡ�\n" NOR;

                me->add("neili", -500);
                me->start_busy(3);

              //  message_combatd(msg, me, target);

                target->set("eff_qi", 0);
                target->set("eff_jing", 0);
               // target->unconcious(me);               
                } else
                {
                damage = ap + random(ap);               
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                           HIR "����$N" HIR "˫צ������$n" HIR "�����ܲ������ؿڱ�$N" HIR
                                           "ץ��ʮ��Ѫ�ۡ�\n" NOR);

                me->start_busy(3);
                //target->start_busy(lvl/30);
                me->add("neili", -400);
              }
        } else
        {
                msg += CYN "$n" CYN "�����мܣ�����$N" CYN "���л��⡣\n" NOR;

                me->start_busy(4);
                me->add("neili", -100);
        }
        message_sort(msg, me, target);
        me->add_temp("apply/attack", lvl/2); 
        me->add_temp("apply/damage", lvl/2);
        for (i = 0; i < 4; i++) 
        { 
                if (! me->is_fighting(target)) 
                break; 
                if (random(8) < 2 && ! target->is_busy()) 
                target->start_busy(1); 
        
                COMBAT_D->do_attack(me, target, 0, 0); 
        } 
        me->add_temp("apply/attack", -lvl/2); 
        me->add_temp("apply/damage", -lvl/2);
        return 1;
}

