// energy stone.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIY "����ʯ" NOR, ({"energy stone", "stone"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�龫������������ʯ��\n" NOR);
                set("unit", "��");
                set("value", 50000);
                set("weight", 40);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
       // mapping my;

        if (! me->is_magic_beast())
        {
                write("����˰�������ʯҲ�ܳ���\n");
                return 1;
        }

        me->set("food", 8*me->max_food_capacity());
        me->set("water",8*me->max_water_capacity());
        // me->start_busy(1);
        message_vision(HIR "$N" HIR "������һ������ʯ����ʱȫ�����⣡\n"NOR,me);

        destruct(this_object());

        return 1;
}

