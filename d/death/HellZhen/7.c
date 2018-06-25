// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit NPC;

#include <ansi.h>
#include <combat.h>
#include "ghost.h" 

void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))];
        name += last_words[random(sizeof(last_words))];
        
        set_name(name, ({ "ghost"}) );
        set("gender", "����" );        
        set("age",40);
        set("str", 30);
        set("int", 20);
        set("per", 27);
        set("attitude", "killer");
        set("combat_exp", 640000000+random(600000000));
        set("level", 99);
        set("max_qi", 12000000);
        set("max_jing", 1200000);
        set("neili", 8000000);
        set("max_neili", 8000000);
        set("jingli", 8000000);
        set("max_jingli", 8000000);
        
        set_skill("force", 600);
        set_skill("huntian-qigong", 600);
        set_skill("yijin-duangu", 600);
        set_skill("blade", 600);
        set_skill("liuhe-dao", 600);
        set_skill("staff", 600);
        set_skill("dagou-bang", 600);
        set_skill("dodge", 600);
        set_skill("xiaoyaoyou", 600);
        set_skill("hand", 600);        
        set_skill("strike", 600);
        set_skill("xianglong-zhang", 600);
        set_skill("parry", 600);
        set_skill("checking", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("strike", "xianglong-zhang");
        map_skill("parry", "xianglong-zhang");
        map_skill("blade", "liuhe-dao");
        map_skill("staff", "dagou-bang");

        prepare_skill("strike", "xianglong-zhang");
   
        set("hellzhen", 0);
        setup();

        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 
                
        carry_object("/clone/cloth/cloth")->wear();
}

void invocation(object target)
{
        object me = this_object();
        int damage;
        string msg;
        int ap, dp;


        // ��һ��
        ap = me->query_skill("strike") * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("dodge") + target->query_skill("martial-cognize", 1);

        message_sort(HIW "\n��Ȼ��$N" HIW "���μ���������һ�������ֺ���һ�ƣ���"
                     "��$n" HIW "��ȥ�����ǽ���ʮ���ơ�" NOR + HIY "�����л�" NOR
                     + HIW "��һ�У���������֮��˵���㵽������ɽ����֮����$n" HIW
                     "��ӿ��ȥ������ʯ���쾪�������ޱȡ�\n" NOR, me, target);
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                          HIR "$p" HIR "һ�㣬ֻ��$P" HIR "����"
                                          "һ�����ѻ����Լ���ǰ����������������"
                                          "�����С�\n:����@?");

                message_vision(msg, me, target);

        } else
        {
                msg = HIC "$p" HIC "����˫�ۣ�����Ӧ�ԣ��������࣬$P"
                      HIC "��������ţ�뺣������жȥ��\n" NOR;
                message_vision(msg, me, target);
        }

        // �ڶ���
        ap = me->query_skill("strike") * 3 / 2 + me->query("str") * 5 +
             me->query("level") * 20;
        dp = target->query_skill("parry") + target->query("dex") * 5 +
             target->query("level") * 20;

        message_sort(HIW "\n$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "������֮��"
                     "��������ǰ�ƣ������������ϲ�������һ�С�" NOR + HIY "������"
                     "��" NOR + HIW "����������������ŭ����ӿ���Ʋ��ɵ�����ʱ$n"
                     HIW "�����Ϣ���ͣ����㲻�ȡ�\n" NOR, me, target);
        if (ap / 2 + random(ap) > dp)
        {
                damage = ap * 2 / 3 + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "ֻ��$p" HIR "һ���Һ�����$P" HIR
                                           "һ�ƻ�����ǰ�������꿦�ꡱ���˼�����"
                                           "�ǡ�\n:����@?");

                message_vision(msg, me, target);
        } else
        {
                msg = HIC "$p" HIC "����˫�ۣ�����Ӧ�ԣ��������࣬$P"
                      HIC "��������ţ�뺣������жȥ��\n" NOR;
                message_vision(msg, me, target);
        }

        // ������
        ap = me->query_skill("strike") * 3 + me->query("str") * 5 +
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("force") + target->query("con") * 5 +
             target->query_skill("martial-cognize", 1);

        message_sort(HIW "\n������$N" HIW "һ�����ȣ�����бб�ӳ���ǰ������δ��"
                     "�����������ֵ�����Ȼ�ֹ���һ�С�" NOR + HIY "�����л�" NOR
                     + HIW "�����Ƽз��ƣ��������񣬱���һ��������ǽ����ǰ�����"
                     "ȥ��$n" HIW "ֻ����Ѫ��ӿ����Ϣ���ǡ�\n" NOR, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "���$p" HIR "����������$P" HIR
                                           "���ƾ���ʱ���ض��������ۡ������һ��"
                                           "����Ѫ��\n:����@?");

                message_vision(msg, me, target);
                me->start_busy(3 + random(4));
                me->add("neili", -400 - random(600));
        } else
        {
                msg = HIC "$p" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ��ѳ�$P" HIC "����֮�⡣\n" NOR;
                message_vision(msg, me, target);
                me->start_busy(3 + random(4));
                me->add("neili", -400 - random(600));
        }
        message_combatd(msg, me, target);
        destruct(me);
}
