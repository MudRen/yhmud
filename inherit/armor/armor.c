// armor.c
#include <ansi.h>
#include <armor.h>

inherit EQUIP;

int is_armor() { return 1; }

void setup()
{
	if (! clonep(this_object()))
	        set("armor_type", TYPE_ARMOR);

        ::setup();
 }

string extra_long() 
{ 
        mapping need;
        string str; 

        str = HIW "\n��Ʒ���� : ����(����)\n" NOR; 
        if (query("bindable"))
        {
                string type;
                int t;

                t = query("bindable");
                if (t == 1) type = "װ����";
                else if (t == 2) type = "ʰȡ�ﶨ";
                else if (t == 3) type = "ֱ�Ӱ�";
                str += sprintf(HIW "������ : %s\n" NOR, type);
        } 
        str += sprintf(HIW "��    �� : %d\n" NOR, this_object()->query_weight());
        str += sprintf(HIW "�� �� �� : %d\n" NOR, this_object()->query("armor_prop/armor"));
        str += sprintf(HIW "��Ƕ���� : %d\n" NOR, (int)query("enchase/flute"));
        if (mapp(need = query("need")) && sizeof(need))
                foreach (string key in keys(need))
                        str += sprintf(HIW "װ��Ҫ�� : %s %d\n" NOR,
                                       to_chinese(key), need[key]);
        /*
        str += sprintf(HIW "ʹ�÷�ʽ : ����ָ�� wear %s װ����\n" NOR, query("id")); 
        str += sprintf(HIW "ʹ�÷�ʽ : ����ָ�� remove %s ж�¡�\n" NOR, query("id")); 
        */
        str += sprintf(HIW "���߶�ʧ : %s\n" NOR,
                       this_object()->query_autoload() ? "��" : "��");
                       
        return str; 
} 
