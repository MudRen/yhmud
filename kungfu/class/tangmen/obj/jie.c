#include <ansi.h>
#include <weapon.h>
inherit ITEM;

void create()
{
        set_name(HIG "����ǧǧ��" NOR, ({"qianqian jie"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "����һö�Ĵ��������Ƶİ�������ǧǧ�ᣬһ�����������������ᣬ�����ޱȡ�\n");
                set("unit", "��");
                set("value", 21);
        }
        setup();
}