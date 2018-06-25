// wangqing.c �����ɵ�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�����ɵ�" NOR, ({ "wangqing xiandan", "xiandan", "dan" }));
        set_weight(200);
        if( clonep() )
            set_default_object(__FILE__);
        else {
            set("long", HIG "һ����Ө��͸���ɵ�����˵��̫���Ͼ�"
                        "�������Ƶ��鵤��ҩ��\n" NOR);
            set("value", 100000000);
            set("unit", "��");
            set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        int effect;

        log_file("static/using", sprintf("%s(%s) eat �����ɵ� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);

        if (me->query_skill("literate", 1)
           || me->query("learned_literate"))
        {
                effect++;
                write(HIC "�˵�һ������о��Լ�����һƬ�հס�\n" NOR);
                me->delete_skill("literate");
                me->delete_skill("calligraphy");
                me->delete_skill("japanese");
                me->delete_skill("mathematics");
                me->delete_skill("count");
                me->delete_skill("qimen-wuxing");
                me->delete_skill("muslim");
                me->delete_skill("russian");
                me->delete_skill("sanscrit");
                me->delete_skill("tadpole");
                me->delete("learned_literate");
                me->add("forgot_literate", 1);
                me->unconcious();
        }

        if (! effect)
                tell_object(me, "��������ú���ûʲô���á�\n");

        destruct(this_object());
        return 1;
}

