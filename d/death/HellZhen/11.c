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
        set("age", 40);
        set("str", 30);
        set("int", 20);
        set("per", 15);
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
        set_skill("mizong-neigong", 600);
        set_skill("unarmed", 600);
        set_skill("longxiang-gong", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("hammer", 600);
        set_skill("riyue-lun", 600);
        set_skill("staff", 600);
        set_skill("xiangmo-chu", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("dagger", 600);
        set_skill("finger", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("parry", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("sanscrit", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "longxiang-gong");
        map_skill("unarmed", "longxiang-gong");
        map_skill("hammer", "riyue-lun");
        map_skill("dagger", "poxu-daxuefa");
        map_skill("sword", "mingwang-jian");
        map_skill("finger", "poxu-daxuefa");
        map_skill("hand", "dashou-yin");
        map_skill("cuff", "yujiamu-quan");

        prepare_skill("unarmed", "longxiang-gong");
        
        set("hellzhen", 0);
        setup();
        
        set_temp("apply/damage", 200); 
        set_temp("apply/unarmed_damage", 200); 
        set_temp("apply/armor", 400); 
                
        carry_object("/clone/cloth/cloth")->wear();
        // carry_object("/clone/weapon/hammer")->wield();
}

void invocation(object target)
{
        int ap, dp, shd, damage;
        string msg;
        object me = this_object();


        msg = HIY "$N" HIY "��ת�����������ʮ����"
              "������˫ȭЯ�š�" HIR "ʮ��ʮ��" HIY "��֮����$n" HIY "����"
              "\n������ȭ����������������ﳾ����\n" NOR;
              
        ap = me->query_skill("unarmed") * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("force") + target->query_skill("martial-cognize", 1);
        
        if (ap + random(ap) > dp)
        {
                if (target->query_temp("shield"))
                {
                        shd = target->query_temp("apply/armor");

                        target->add_temp("apply/armor", -shd);
                        target->delete_temp("shield");

                        msg += HIW "$N" HIW "���ӿ������Ȼ���������ˣ���ʱ��$n"
                               HIW "�Ļ��������ݻٵõ�Ȼ�޴棡\n" NOR;
                }

                damage = ap + random(ap);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                               HIR "$n" HIR "�������ܣ��ٱ�$N" HIR
                                               "˫ȭ�������У������������룬��"
                                               "������������\n" NOR);

                me->add("neili", -800);  
        }else
        {
                me->add("neili", -500);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        
        message_combatd(msg, me, target);                      
        destruct(me);
}

