         
#include <ansi.h> 
#include <combat.h> 
 
//inherit F_DBASE; 
inherit F_SSERVER; 
 
int perform(object me, object target) 
{ 
        object weapon; 
        int skill, lvl, ap, dp, i; 
        string msg; 
        int damage, hurt, tm; 
         
        //if ( !userp(me) && !me->query("can_perform/liuhe-bian/lianhuan")) 
        //        return notify_fail("�����õ��⹦��û���������!\n"); 
                 
        if ( !target ) target = offensive_target(me); 
         
        if ( !target 
                ||   !target->is_character() 
                ||   !me->is_fighting(target) ) 
                return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n"); 
         
        if ( me->query_temp("lianhuan") ) 
                return notify_fail("��ո�ʹ�ù�������������������δƽ����\n");        
 
        weapon = me->query_temp("weapon"); 
 
        if (! objectp(weapon = me->query_temp("weapon"))  
                || (string)weapon->query("skill_type") != "whip"  
                || me->query_skill_mapped("whip") != "liuhe-bian" )  
                return notify_fail("�������ޱޣ�����ܹ�ʩչ��������\n");        
         
        if ( me->query_skill("force") < 270 ) 
                return notify_fail("����ڹ����δ�����޷���ϱ޷�ʩչ��������\n"); 
 
        if ( me->query_skill("whip", 1) < 180 ) 
                return notify_fail("��޷���Ϊ���㣬������ʹ����������\n"); 
         
        if ( me->query_skill("liuhe-bian", 1) < 180 ) 
                return notify_fail("�����ϱ޷���Ϊ���㣬������ʹ����������\n");        
 
        if ( me->query("neili") <= 300 ) 
              return notify_fail("��������������޷�ʩչ��\n");        
                 
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 
        if ( me->query_skill("dodge", 1) < 180 ) 
                return notify_fail("���Ṧ��Ϊ���㣬�޷����ٹ�����\n"); 
 
        skill = me->query_skill("force", 1) + me->query_skill("liuhe-bian", 1) + 
                me->query_skill("dodge", 1); 
        lvl = me->query_skill("liuhe-bian", 1); 
        lvl = lvl / 3; 
         
        ap = skill + random(skill); 
 
        dp = target->query_skill("parry", 1) + target->query_skill("dodge", 1);     
         
        msg = HIR "\n$N���һ���������������з𾭣�����" +  
                       weapon->name() + "����������������" 
                       "���������\n\n" NOR; 
        if (random(ap) > dp) 
        {     
             i = 6; 
             me->set_temp("lianhuan", 1); 
             me->add_temp("apply/damage", lvl); 
                 
             tm = 5 + random(5); 
         
             me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), tm); 
             me->add("neili", -300); 
             me->start_busy(2);        
             hurt = skill / 3; 
              
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIY "\n����ϡ���$N�趯����" + weapon->name() +  
                    HIY "˲Ϣ����$n�Ķ�ͷ��ž��һ�����죬��ʱһ��Ѫӡ��\n" NOR); 
              
             i = 5; 
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIW "\n���غϡ���$Nһ����ɨ����$n�����̣�$nδ�ܿ�����ͼ��һ���Һ���"  
                    + weapon->name() + HIW "�޶���û��С�Ȱ��"  
                            "����ʱ����������\n" NOR); 
              
             i = 4; 
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIR "\n���˺ϡ���$N��" + weapon->name() + HIR"��Ϊһ�弱����$n��"  
                    "$n���ֲ����������Ѫ��ֹ��\n" NOR); 
             i = 3; 
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIG "\n����ϡ���$N����" + weapon->name() + HIG "��������һ��" 
                    "��׷��$n��ȥ��\n" NOR); 
             i = 2; 
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIC "\n����ϡ���$NͻȻ�������ң�������Ӳ��Ȼ��ɱ��ȴ��ʤһ�"  
                    + weapon->name() + HIC "��������Ĺ�â��$n������������������ɫ��\n"    NOR); 
         
                i = 1; 
             damage = hurt / i; 
             msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,  
                    HIB "\n�����ϡ���$N���и߳���ţ�����" + weapon->name() +  
                    HIB "������������Ӱ���أ�$n��Ҳ֧�ֲ�ס�����ϱ�����һ������ڡ�\n" NOR); 
              
         } else 
         { 
             msg += CYN "$n" CYN "���Ų�æ���Կ��죬��$N" 
                    CYN "����ʽ��ȫ��ȥ��\n" NOR; 
             me->add("neili", -200); 
             me->start_busy(2 + random(3));  
         } 
        message_combatd(msg, me, target);  
        return 1; 
} 
 
void remove_effect(object me, int amount) 
{ 
        int lvl; 
        lvl = (int)me->query_skill("liuhe-bian", 1); 
        lvl = lvl / 3; 
        me->delete_temp("lianhuan"); 
 
        if ( me->is_fighting() ) { 
                message_vision(HIR "\n$N�������ջص����������Ҳ������������\n\n" NOR, me);    
        } 
        else { 
                tell_object(me, HIR "\n����ڹ�������ϣ������������ջص��\n\n" NOR); 
        } 
        me->add_temp("apply/damage", -lvl); 
 
} 

