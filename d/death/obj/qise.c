#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "��ɫ���" NOR, ({"qise yingluo"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "\nһ�鴿��ɫ��ˮ������Ө��͸����Ͼ�ı�����\n"
                            "��ҫ�۵Ĺ������з·��̲���ǧǧ�������\n"
                            "��������������Ϣ��ɢ������������������\n"
                            "�Ǵ�˵�е�����������ɫ����ഫֻ���ڵ�\n"
                            "���вŻ���֡�\n" NOR);
                set("unit", "��");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "ying luo");
                set("material_name", HIW "��ɫ���" NOR);
                set("can_make", "all");
				set("not_make", ({ "ս��", "����", "����", "ѥ��" }));
                //set("power_point", 200);
				set("power_point", 100);
        }
}

int query_autoload()
{
        return 1;
}