// lingkong

#include <ansi.h>

inherit F_SSERVER;

#define LING "��" HIW "���ָѨ" NOR "��" 

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        //if (userp(me) && ! me->query("can_perform/qufannao-zhi/lingkong"))   
        //        return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");   

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(LING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ��" LING "��\n");           

        if( (int)me->query_skill("qufannao-zhi", 1) < 100 )
                return notify_fail("���ȥ����ָ������죬����ʹ��" LING "��\n");

        if( (int)me->query_skill("hunyuan-yiqi", 1) < 100 )
                return notify_fail("�����������Ԫ�������ߣ������������߶�ָ���˵С�\n");

        if( (int)me->query("neili", 1) < 300 )
                return notify_fail("����������̫��������ʹ��" LING "��\n");

        msg = CYN "$NĬ��𾭣�ֻ����ָ΢��������ָ��������$n��������ָ������$n��\n"NOR;

        ap = me->query_skill("force", 1) + me->query_skill("finger", 1) + 
             me->query_skill("qufannao-zhi", 1) + me->query("neili", 1) / 50;
        dp = target->query_skill("force", 1) + target->query_skill("dodge", 1) +
             target->query_skill("parry", 1);
        if (random(ap) + random(ap / 3) > dp )
        {
                me->start_busy(3);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("qufannao-zhi", 1);
                
                damage = damage / 2 + random(damage);
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage / 6);
                me->add("neili", -damage / 6);
                
                if( damage < 100 )
                        msg += HIY "$n�ܵ�$N��ָ��͸�����ƺ�һ��������ȥ����ƣ����\n" NOR;
                
                else if( damage < 300 )
                        msg += HIY "$n��$N��ָ��������ֻ�������з��ƣ�ֻ��ú���Ϣ��Ϣ��\n" NOR;
        
                else if( damage < 500 )
                        msg += RED "$n��$N��ָ��һ�������������죬��ʶ��ʼģ��������\n" NOR;
                else
                        msg += HIR "$n��$N��ָ��һ����ǰһ�ڣ����㵹���ۿ���Ҫ���������ˣ�\n" NOR;
                
        }
        else 
        {
                me->start_busy(4);
                msg += CYN "����$p������$P����ͼ����û���ϵ���\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}

