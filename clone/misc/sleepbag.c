// sleepbag.c
inherit ITEM;

void create()
{
        set_name("˯��",({"sleepbag"}));
        set_weight(7000);
        set_max_encumbrance(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("long",
                "һ��˯����������ʿ������Ұ��˯���õġ�\n");
            set("unit","��");
            set("value", 1000);
        }
}
