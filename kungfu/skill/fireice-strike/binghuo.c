// binghuo.c ���溮����--
// looo/2001/6/23
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
           || !me->is_fighting(target) || !living(target) )
                return notify_fail("����������졹ֻ����ս����ʹ�á�\n");

        if( objectp( me->query_temp("weapon")) )
                return notify_fail("ֻ�п��ֲ���ʩչ����������졹��\n");

        if( (int)me->query_skill("fireice-strike", 1) < 150 )
                return notify_fail("������溮���ƹ��򻹲�����죬����ʹ�á���������졹��\n");

        if(me->query_skill("yunv-xinjing", 1) < 120)
                return notify_fail("�������ڵ���Ů�ľ���ʹ��������������졹��\n");

        if ( me->query_skill_mapped("strike") != "fireice-strike" )
                return notify_fail("�������޷�ʹ�á���������졹���й�����\n");

        if( (int)me->query("max_neili") < 800 )
                return notify_fail("���������Ϊ̫��������ʹ�á���������졹��\n");

        if( (int)me->query("neili") < 800 )
                return notify_fail("�������������\n");

        if ("jiuyang-shengong" == target->query_skill_mapped("force"))
        {
                msg = HIR"$N" HIR"������������͸��⣬һ�ɳ���������" HIR"$n" HIR"ӭ��������\n" NOR;
                if (living(target))
                       dp = target->query_skill("force",1) / 4;
                else   dp = 0;
                if (random(me->query_skill("force",1)) > dp)
                {
                       me->add("neili", -100);
                       msg += HIY "$nһ��֮�£����˾����������ֿ�������ɫת�˼�ת����Ȼ����\n"NOR;
                }  else
                {
                       me->start_busy(3);
                       me->add("neili", -200);
                       msg += HIW"$p" HIW"���һ�����������ã������˾���������\n"
                              HIR"$N" HIR"��������������Ѫ�����ڣ�����������\n"NOR;
                }
        }  else
        {
                msg = HIR "\n$N" HIR "������������͸��⣬һ�ɳ�������ֱϮ" HIR "$n" HIR "�ؿڣ�\n"NOR;
                if (living(target))
                       dp = target->query_skill("parry") / 3;
                else   dp = 0;
                if (random(me->query_skill("parry")) > dp)
                {
                       me->start_busy(1);
                       target->start_busy(1);
                       me->add("neili", -300);
                       damage = (int)me->query_skill("fireice-strike", 1);
                       damage = random(damage) + 300;
                       msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                              HIR"$n"HIR"��ʱ�����ؿ��类���գ�һ���������Լ̻�!!\n"NOR);

                       if(me->query_skill("fireice-strike", 1) > 150)
                              call_out("perform2", 0, me, target);
                }   else
                {
                       me->start_busy(3);
                       me->add("neili", -100);
                       msg += HIW"����$pһ�����Ʒ���ԶԶ�Ķ��˿�ȥ��\n"NOR;
                }
        }
        message_vision(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
        string msg;
        int damage;
        if (!me || !target || environment(me) != environment(target)) return 0;
        if(!living(target))
          return notify_fail("�����Ѿ�������ս���ˡ�\n");

        if( (int)me->query("neili", 1) < 600 )
                return notify_fail("���Ҫ�ٳ��ڶ��ƣ�ȴ�����Լ������������ˣ�\n");

        msg = HIB "\n����" HIB "$N" HIB "�ӳ����֣����ľ��ǰ���������������Ƕ���" HIB "$n" HIB "�Ĺ�ȥ!\n"NOR;
        if (random(me->query_skill("dodge")) > target->query_skill("dodge") / 2)
              {

                me->start_busy(1);

                me->add("neili", -300);
                damage = (int)me->query_skill("fireice-strike", 1);
                damage = random(damage)+300;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                HIW  "���һ�ƻ��У�" HIW "$n" HIW "ֻ����ȫ������ͨ�����ⶳ�ᣬ��ɫһ�±�ף�\n"NOR);


                }
        else {
           me->start_busy(3);
           me->add("neili", -100);
           msg += HIY "\n$p" HIY "�ۿ��������ˣ�����������˳�����˿�ȥ��\n" NOR;
           }
        message_vision(msg, me, target);
        return 1;
}

