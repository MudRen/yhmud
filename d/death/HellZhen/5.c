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
        set("combat_exp", 60000000 + random(30000000));
        set("level", 99);
        set("max_qi", 12000000);
        set("max_jing", 1200000);
        set("neili", 8000000);
        set("max_neili", 8000000);
        set("jingli", 8000000);
        set("max_jingli", 8000000);
        
        set_skill("force", 600);
        set_skill("hunyuan-yiqi", 600);
        set_skill("yijinjing", 600);
        set_skill("blade", 600);
        set_skill("xiuluo-dao", 600);
        set_skill("sword", 600);
        set_skill("damo-jian", 600);
        set_skill("dodge", 600);
        set_skill("shaolin-shenfa", 600);
        set_skill("hand", 600);        
        set_skill("fengyun-shou", 600);
        set_skill("cuff", 600);
        set_skill("jingang-quan", 600);
        set_skill("claw", 600);
        set_skill("longzhua-gong", 600);
        set_skill("parry", 600);
        set_skill("buddhism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "longzhua-gong");
        map_skill("blade", "xiuluo-dao");
        map_skill("sword", "damo-jian");

        prepare_skill("claw", "longzhua-gong");
   
        set("hellzhen", 0);
        setup();

        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 
                
        carry_object("/clone/cloth/cloth")->wear();
}

void invocation(object target)
{
        string msg;
        int skill, ap, dp, damage;
        object me = this_object();

        skill = me->query_skill("longzhua-gong", 1);

        msg = HIY "$N" HIY "���һ������������$n" HIY "��ǰ���漴����ץ��"
              "$p" HIY "��Ҫ����\n" NOR;
 
        ap = me->query_skill("claw") * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -180);
                damage = ap / 3 + random(ap / 5);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                           HIR "$p" HIR "���������ͣ����Զ�ܣ�ֻ��"
                                           "��ǿ���⣬˭֪$P" HIR "���ֺ������۾�"
                                           "һ�㣬����һ����ץ��$p" HIR "��Ҫ������"
                                           "ʱ��Ѫ�ɽ���\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
                       "����ʽ����������ȫȻ������$P"
                       CYN "�Ĺ��ơ�\n" NOR;
                me->add("neili",-60);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        destruct(me);
}
