// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h> 
#include <weapon.h> 
inherit SWORD; 

void create() 
{ 
        set_name(HIW "�޼�����" NOR, ({"wujian shandian", "wujian", "shandian"})); 
        set_weight(15000); 
        if (clonep()) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "��"); 
                set("long", sort_msg(HIR "�������ɽ֮��ʯΪ�������������һ�ѽ�����˵Щʲô�أ�"
                                     "��ۣ��������ǻۡ��ʰ���һ�����������֣�ʥ�����޼�����"
                                     "��һ���޵�֮����ʹ�÷�����װ������ smash id ���ݻٶ��֡�\n" NOR));
                set("value", 100000); 
                set("material", "steel");
                set("no_sell", "�ҵ��졭�㡭��֪������ɶô������Ҳ����������"); 
                set("rigidity", 500); 
                set("no_put",1); 
                set("no_steal",1);   
                set("wield_msg",HIR"$N[��]��һ�����һ���޼����磬�������ƣ�����������ɱ���Ľ���\n"NOR); 
                set("unwield_msg",HIR"$N�����е��޼�������뽣�ʣ�������ɢ���׵���ʧ��ɱ�����ޡ�\n"NOR); 
        }
        init_sword(2100000); 
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing", me->query("str") * 200, me);
        victim->receive_wound("jing", me->query("str") * 200, me);
        return HIM "�޼�����д��Ŵ̶����ƿ�������һ�������磬��ʱ��$n"
               HIM "ֻ�е��������١�\n" NOR;
}

