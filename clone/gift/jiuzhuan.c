// jiuzhuan.c ��ת��
// IvyΪ����Ⱥ������ԭ��ÿ����������+4�޸�Ϊ+2
//н��������Ϊ+1
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "��ת��" NOR, ({ "jiuzhuan jindan", "jindan", "dan" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIY "һ����ɫ���ɵ�����˵��̫���Ͼ�"
					"�������Ƶ��鵤��ҩ��\n" NOR);
		set("value", 50000000);
		set("unit", "��");
		set("only_do_effect", 1);
	}
}

int do_effect(object me)
{
        int effect;

        log_file("static/using", sprintf("%s(%s) eat ��ת�� at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
        if (me->query("gift/jiuzhuan/int") < 1 && random(2))
        {
                effect++;
                write(HIM "������Լ���ͷ�Ը������ˡ�\n" NOR);
                me->add("gift/jiuzhuan/int", 1);
                me->add("int", 1);
        }

        if (me->query("gift/jiuzhuan/dex") < 1 && random(2))
        {
                effect++;
                write(HIR "������Լ����ȽŸ�����ˡ�\n" NOR);
                me->add("gift/jiuzhuan/dex", 1);
                me->add("dex", 1);
        }

        if (me->query("gift/jiuzhuan/con") < 1 && random(2) &&
            me->query("gender") != "����")
        {
                effect++;
                write(HIC "������Լ�����Ϣ��ͨ���ˡ�\n" NOR);
                me->add("gift/jiuzhuan/con", 1);
                me->add("con", 1);
        }

        if (me->query("gift/jiuzhuan/str") < 1 && random(2))
        {
                effect++;
                write(HIG "������Լ���������ǿ���ˡ�\n" NOR);
                me->add("gift/jiuzhuan/str", 1);
                me->add("str", 1);
        }

        if (! effect)
                tell_object(me, "��������ú���ûʲô���á�\n");

        destruct(this_object());
	return 1;
}

