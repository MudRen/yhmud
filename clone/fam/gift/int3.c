#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIW "���ͨ���ɵ�" NOR, ({ "tonghui xiandan", "tonghui",
                                                  "xiandan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "��˵�˵������칬�е���Ʒ�����˳��˿���ƽ�����ԡ�\n" NOR);
                set("base_unit", "��");
                set("base_value", 100000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "int");
                set("gift_name", "��������");
                set("gift_point", 85);
                set("gift_msg", HIG "ͻȻ����ֻ����̨��һƬ��������̩�ޱȡ�\n" NOR);
        }
        setup();
}
