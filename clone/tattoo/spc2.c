#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "�������ͼ" NOR, ({ "fengwu tu", "fengwu", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "һֻԡ�����������Ƽ䣬���˳���");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����" }));
                set("tattoo_int", 4);
                set("tattoo_special", "energy");
                set("tattoo_spcname", "���ǻ���");
        }
}
