#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZONG "��" HIM "���ݺ�" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/liumai-shenjian/zong"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" ZONG "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 260)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" ZONG "��\n");

        if (me->query_skill("force") < 480)
                return notify_fail("����ڹ���򲻹�������ʩչ" ZONG "��\n");

        if (me->query("max_neili") < 8500)
                return notify_fail("���������Ϊ����,�޷�ʩչ" ZONG "��\n");

        if (me->query("neili") < 1000)
                return notify_fail("������������������޷�ʩչ" ZONG "��\n");

        if (me->query_temp("weapon"))
                return notify_fail("������ǿ��ֲ���ʩչ" ZONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIM "$N" HIM "һ����Х��ʮָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻������ʱ�����籼�������޾������������Ȼ����$n" HIM 
              "��\n" NOR;
/*
        ap = me->query_skill("finger") + me->query_skill("force");
        dp = target->query_skill("parry") + target->query_skill("force");
        me->start_busy(3);

        if ((int)target->query_skill("jingluo-xue", 1) >= 300 
            && target->query_skill("dodge", 1) >= 300
            && random (10) == 1 )
        {
                me->add("neili", -600);
                me->start_busy(4);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else
        if (ap * 3 / 4 + random(ap) > dp)
        { 
                damage = ap * 3 / 2 + random(ap);
                me->add("neili", -800);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
        } else
        {
                me->add("neili", -400);
                me->start_busy(4);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
*/


  damage = (int)me->query_skill("finger",1)/2 + (int)me->query_skill("liumai-shenjian",1);
      

       // ��һ��
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("parry",1) + target->query_skill("jingluo-xue", 1);

	    msg += HIM "$N" HIM "˫��Ĵָͬʱ����������������죬��"+ HIY "���̽�"+ HIM "������ʯ���쾪�����������\n" NOR ; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(30),
                                           HIR "$n" HIR "�����ֵ���ȴ�����мܵ�ס����$N"
                                           HIR "��һָ������Ѫ������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }

        // �ڶ���
        ap = me->query_skill("liumai-shenjian",1) + me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("parry",1)+ target->query_skill("jingluo-xue", 1);

	    msg += HIY "����" HIY "$N" HIY "Ĵָһ����ʳָ�漴����������������죬��" HIR "������" HIY "������̳���\n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(30),
                                           HIR "$n" HIR "��ͼ�ֵ���ֻ�����һ����"
                                           HIR "���ν�����������룬͸�������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }

        //// ������
        ap = me->query_skill("liumai-shenjian",1)+me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIG "ֻ��" HIG "$N" HIG "������ָһ������" HIC "�г彣" HIG "����ǰ�̳��������ĵ�����Ȼ���죬���ν���ֱָ$n�� \n"NOR; 
       
        if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(40),
                                           HIR "$n" HIR "һ㶣�ֻ��������һ����"
                                           HIR "�ѱ�����������Ѫ�ɽ���\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "ʹ��������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }

        //// ������
        ap = me->query_skill("liumai-shenjian",1)+me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("dodge",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIC "$N" HIC "����ָ����һ�ӣ���������һ����׾�͹��ӵġ�" MAG "�س彣" HIC "��������" HIC"$n" HIC"ֱ�������\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(40),
                                           HIR "$n" HIR "������������������ڴ��Ѫ������"
                                           HIR "��Ѫ��ӿ������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�������������ڽ�$N"
                       CYN "��һָ�ܿ���˿������\n" NOR;
        }
      

        //// ������
        ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIB "����$N" HIB "����Сָһ�죬һ���������ٳ�Ѩ�м��������һ�ɡ�" HIW "����" HIB "����ʱ����$n��\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(60),
                                           HIR "$n" HIR "�����ֵ���ֻ����һ��͸������"
                                           "Ϯ��������һ�����裬�������̱�ÿտյ�����\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�����ֵ���Ӳ����������$N"
                       CYN "��һָ��\n" NOR;
        }
		//// ������
		ap = me->query_skill("liumai-shenjian",1)+ me->query_skill("jingluo-xue", 1);
        dp = target->query_skill("force",1)+target->query_skill("jingluo-xue", 1);

	    msg += HIW "���"HIW "$N" HIW"����Сָһ�ӣ�һ�С�" HIG "�ٳ彣" HIW "�����̴��ƿմ̳�������񻨴̻�һ�㡣\n"NOR; 
       
		 if (ap * 3 / 4 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, random(damage), random(60),
                                           HIR "$n" HIR "��Ȼ�����ֿ�����ƾ������Ϯ"
                                           "ֻ����һ��������....\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "�����ֵ������ڽ�����$N"
                       CYN "��һָ�������Ǳ�������\n" NOR;
        }

		message_combatd(msg, me, target);
	    me->add("neili", -800);
        me->start_busy(3 + random(4));

        return 1;
}


