#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "��ũ�ٲ�ͼ" NOR, ({ "baicao tu", "baicao", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ�Źžɵ�ͼƬ���������Щ������");
                set("unit", "��");
                set("value", 16500);
                set("material", "paper");
                set("tattoo_long", "��ũ�ϳ��ٲݣ�����ȱ���");
                set("can_tattoo", ({ "�ؿ�", "��", }));
                set("tattoo_type", ({ "����", "��" }));
                set("tattoo_int", 2);
                set("tattoo_dex", 2);
                set("tattoo_special", "herb");
                set("tattoo_spcname", "����֪ʶ");
        }
}
