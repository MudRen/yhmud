#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "���ͼ��" NOR, ({ "chiyou tu", "chiyou", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 9000);
                set("material", "paper");
                set("tattoo_long", "ħ����ȵ�����");
                set("can_tattoo", ({ "�ؿ�", "��", "���", "�ұ�" }));
                set("tattoo_type", ({ "����", "����" }));
                set("tattoo_str", 1);
                set("tattoo_dex", 2);
        }
}