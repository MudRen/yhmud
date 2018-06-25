// Code of ShenZhou
#include <weapon.h>
// Jay 10/7/96

inherit STAFF;

void create()
{
        set_name("����", ({ "shezhang", "staff", "zhang" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ����Լ�߳ߵĺڹ�����ĸ��ȣ��ȶ���һ����ͷ��"
		"�л��ؿ�����������ˡ�\n");
                set("value", 450);
                set("snake_type","����");
                set("material", "steel");
                set("wield_msg", "$N���һ��$n�������У��ȶ˵���ͷ�������졣\n");
                set("unwield_msg", "$N�����е�$n����������\n");
        }
        init_staff(35);
        setup();
}

void init()
{
        add_action("convert","bian");
}

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg!="shezhang" && arg!="staff" && arg!="zhang") return 0;
        if (me->query("family/family_name") != "ŷ������") 
                return notify_fail("�㲻�ܻ���Ϊ�ߡ�\n");
        if ((int)me->query("jing") < 100)
                return notify_fail("��ľ���������\n");
	if (!present("shezhang", me)) 
		return notify_fail("������û�����ȡ�\n");

        if (random(me->query_skill("training",1)) <20) {
        message_vision("$N�������������㵸�����񷢷�һ�㡣\n"
                ,me);
		me->receive_damage("jing", 95);
                return 1;
        }
        message_vision("$N�������������㵸���͵�������һˤ�������Ȼ�Ϊһ�����ߡ�\n",
                me,);
                ob = new("/d/baituo/npc/snake");
        ob->move(environment(me));
        destruct(this_object());
        return 1;
}

