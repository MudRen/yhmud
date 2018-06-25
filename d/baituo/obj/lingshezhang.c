// Code of ShenZhou
#include <weapon.h>
// kane, 2/9/98

#include <ansi.h>
inherit STAFF;

void create()
{
        set_name(HIW"������"NOR, ({ "lingshe zhang", "staff", "shezhang", "zhang"}));
        set_weight(4000);  //***** ADDED BY SCATTER *****                 set("wposition", "/d/baituo/obj/lingshezhang.c");
//***** END OF ADDING ***** 
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ�����������ĺ�ɫ���ȣ����Ǹ������ƣ�\n"+
		"��ͷ���Ÿ��ѿڶ�Ц����ͷ����ͷ����¶������ѩ�׵����ݣ�\n"+
		"ģ�������������죬�����������������������������С�ߣ���ס���������¡�\n");
                set("value", 1);
                set("material", "steel");
                set("snake_type","����");
                set("wield_msg", "$N���һ��$n�������У��ȶ˵������������졣\n");
                set("unwield_msg", "$N�����е�$n����������\n");
		            set("poison_applied", 50);
        }
        init_staff(180);
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
	if (!present("lingshe zhang", me)) 
		return notify_fail("������û�������ȡ�\n");

        if (me->query_skill("training",1) < 70+random(70)) {
        message_vision("$N���������������㵸�����񷢷�һ�㡣\n"
                ,me);
		me->receive_damage("jing", 95);
                return 1;
        }
        message_vision("$N���������������㵸���͵�������һˤ�������Ȼ�Ϊһ�����ߡ�\n",
                me,);
        ob = new("/d/baituo/npc/lingshe");
        ob->move(environment(me));
        destruct(this_object());
        return 1;
}

