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
        set_skill("xiantian-gong", 600);
        set_skill("quanzhen-xinfa", 600);
        set_skill("finger", 600);
        set_skill("zhongnan-zhi", 600);
        set_skill("sword", 600);
        set_skill("quanzhen-jian", 600);
        set_skill("dodge", 600);
        set_skill("jinyan-gong", 600);
        set_skill("unarmed", 600);        
        set_skill("parry", 600);
        set_skill("taoism", 600);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("finger", "zhongnan-zhi");
        map_skill("unarmed", "xiantian-gong");
        map_skill("parry", "xiantian-gong");
        map_skill("sword", "quanzhen-jian");

        prepare_skill("unarmed", "xiantian-gong");
   
        set("hellzhen", 0);
        setup();

        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 
                
        carry_object("/clone/cloth/cloth")->wear();
}

void invocation(object target)
{
        object weapon, cloth;
        int ap, dp, damage, wp, cl;
        string msg;
        object me = this_object();


        msg = HIW "ֻ��$N" HIW "˫Ŀ�������䣬˫�ƶ�Ȼһ�񣬽����ڻ����"
              "���������ƹ��Ƴ�����ʱ��Х\n�����������쾢��������������"
              "���˰�ӿ��$n" HIW "��\n" NOR;

        ap = me->query_skill("unarmed") * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("force") + target->query_skill("martial-cognize", 1);

        if (ap * 3 / 2 + random(ap) > dp)
        {
                damage = 0;
                        me->start_busy(4);
                        damage = ap + random(ap / 2);
                        me->add("neili", -400);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                                   damage, 90, HIR "$N" HIR "��"
                                                   "���ʱ�߽���$n" HIR "�Ļ�"
                                                   "��������$p" HIR "��Ԫ����"
                                                   "�������������Ѫ��\n" NOR);

                        if (objectp(weapon = target->query_temp("weapon"))
                           && weapon->query("stable", 1) < 100
                           && ap / 3 + random(ap) > dp)
                        {
                                wp = weapon->name();
                                msg += HIW "ֻ�����ϡ���һ�����죬$n" HIW "��"
                                       "�е�" + wp + HIW "��$N" HIW "��������"
                                       "��Ӧ�����飬���ֵ����ڵ��ϡ�\n" NOR;
                                me->add("neili", -150);
                                weapon->set("consistence", 0);
                                weapon->move(environment(target));
                        } else

                        if (objectp(cloth = target->query_temp("armor/armor"))
                           && cloth->query("stable", 1) < 100
                           && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "ֻ�����䡱��һ�����죬$n" HIW "��"
                                       "�ŵ�" + cl + HIW "��$N" HIW "��������"
                                       "��Ӧ�����ѣ�����һ�����Ƭ��\n" NOR;
                                me->add("neili", -150);
                                cloth->set("consistence", 0);
                                cloth->move(environment(target));
                        } else

                        if (objectp(cloth = target->query_temp("armor/cloth"))
                           && cloth->query("stable", 1) < 100
                           && ap / 3 + random(ap) > dp)
                        {
                                cl = cloth->name();
                                msg += HIW "ֻ�����䡱��һ�����죬$n" HIW "��"
                                       "�ŵ�" + cl + HIW "��$N" HIW "��������"
                                       "��Ӧ�����飬����һ�����Ƭ��\n" NOR;
                                me->add("neili", -150);
                                cloth->set("consistence", 0);
                                cloth->move(environment(target));
                        }
        } else
        {
                me->start_busy(4);
                me->add("neili", -120);
                msg += CYN "����$p" CYN "֪��$P" CYN "���е���"
                       "��������Ӳ�ӣ�����бԾ��ܿ�����\n" NOR;
        }
        message_combatd(msg, me, target);

        destruct(me);
}
