#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "�����Ƕ�ͼ" NOR, ({ "jingang tu", "jingang", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "�����Ƕ��鲼��գ�������Զ");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����", "����", "����", "��" }));
                set("tattoo_str", 1);                     // ��Ӧ����ĺ����������࣬����
                set("tattoo_int", 1);                     // ��Ӧ�ļǺš�
                set("tattoo_con", 1);
                set("tattoo_dex", 1);
                set("tattoo_special", "self");
                set("tattoo_spcname", "������ת");
        }
}
