// whip.c
#include <ansi.h>
#include <weapon.h>

#ifdef AS_FEATURE
#include <dbase.h>
#else
inherit EQUIP;
#endif

int is_weapon() { return 1; }

varargs void init_whip(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", flag );
	set("skill_type", "whip");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "whip" }) );
	}
}

string extra_long()
{
        mapping need;
        string str;

        str = HIW "\n��Ʒ���� : ����(��)\n" NOR;
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
        str += sprintf(HIW "�� �� �� : %d\n" NOR, query("weapon_prop/damage"));
        // str += sprintf(HIW "ɱ    ¾ : %d\n" NOR, query("combat/PKS"));
        str += sprintf(HIW "��Ƕ���� : %d\n" NOR, (int)query("enchase/flute"));
        if (mapp(need = query("need")) && sizeof(need))
                foreach (string key in keys(need))
                        str += sprintf(HIW "װ��Ҫ�� : %s %d\n" NOR,
                                       to_chinese(key), need[key]);
        /*
        str += sprintf(HIW "ʹ�÷�ʽ : ����ָ�� wield %s װ����\n", query("id"));
        str += sprintf(HIW "ʹ�÷�ʽ : ����ָ�� unwield %s ж�¡�\n", query("id"));
        */
        str += sprintf(HIW "���߶�ʧ : %s\n" NOR,
                       this_object()->query_autoload() ? "��" : "��");

        return str;
}
