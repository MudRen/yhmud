#include <ansi.h> 
#include <combat.h> 

inherit F_SSERVER; 

int perform(object me) 
{ 
        string msg; 
        object target; 
        int skill, ap, dp, damage; 

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail("���������ҡ�ֻ����ս���жԶ���ʹ�á�\n"); 

         skill = me->query_skill("jimie-zhua", 1); 
  
         if (skill < 80) 
                return notify_fail("��ļ���צ�ȼ�����������ʹ�á��������ҡ���\n"); 

         if (me->query("neili") < 250) 
                return notify_fail("�������������\n"); 

         if (me->query_skill_mapped("claw") != "jimie-zhua")  
                return notify_fail("��û�м�������צ���޷�ʹ�á��������ҡ���\n"); 

         if (! living(target)) 
                 return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 
         msg = HIY "$N" HIY "�͵�����ǰ����˫צ����·��$n" HIY "ץ����ƽ��" 
               "��һ����ȴ��ʾ����ʵ�Ļ�������\n" NOR; 

         ap = me->query_skill("force") + me->query_skill("claw"); 
         dp = target->query_skill("parry") + target->query_skill("dodge"); 
         if (ap / 2 + random(ap) > dp) 
         { 
                 me->add("neili", -200); 
                 damage = ap / 3 + random(ap / 4); 
                 msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55, 
                                            HIR "�����У�$p" HIR "�����м�$P�⿴��" 
                                            HIR "����һץ�������ץ�˸����У�" 
                                            "����һ����$p���϶���һ���˺ۡ�\n" NOR); 
                 me->start_busy(2); 
         } else 
         { 
                 msg += CYN "����$p" CYN "$P����������" CYN 
                        "��æ�мܣ�˳��Ծ����û�б�$P" 
                        CYN "���֡�\n" NOR; 
                  me->add("neili",-20); 
                  me->start_busy(3); 
          } 
          message_combatd(msg, me, target); 

           return 1; 
}

