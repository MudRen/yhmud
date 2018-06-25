// item.c

#include <dbase.h>
#include <move.h>
#include <name.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

STATIC_VAR_TAG string s_name;
STATIC_VAR_TAG string s_id;

void setup()
{
	seteuid(getuid());
}

void set_name(string name, string *id)
{
        ::set_name(name, id);
        s_name = ::query("name");
        s_id = ::query("id");
}

string short()
{
        string colorname;

        if (! stringp(colorname = this_object()->query("colorname"))) 
                return s_name + "(" + s_id + ")";
        else
                return colorname + "(" + s_id + ")";
}


int fire(object me, object ob)
{
        string msg;

        if (this_object()->is_item_make())
                return notify_fail("���۵���ͷ�󺹣���ô��Ҳ�㲻�š�\n");

        if (stringp(msg = query("no_light")))
                return notify_fail(msg);

        switch (query("material"))
        {
        case "wood":
                msg = "$N��$n����$f�����ȼ�ˣ������������"
                      "��ֻʣ����һ��̼��������\n";
                break;
        case "leather":
        case "feather":
        case "silk":
                msg = "$N��$f��$n�����ˣ����ɢ����һ���������ŵĳ�ζ��\n";
                break;
        case "paper":
        case "cloth":
                msg = "$N������$n���������˼������ܿ��"
                      "���˸��ɸɾ�����ʲô��û��ʣ������\n";
                break;
        default:
                return notify_fail("�ⶫ������ȥû���㣬����ʡʡ�����ɡ�\n");
        }

        msg = replace_string(msg, "$n", name());
        msg = replace_string(msg, "$f", ob->name());
        message_vision(msg, me);
        destruct(this_object());
        return 1;
}



string type()
{
        if ( this_object()->is_weapon() )
                return "����";
        if ( this_object()->is_armor() )
                return "����";
        if ( this_object()->is_food() )
                return "ʳ��";
        if ( this_object()->is_liquid() )
                return "����";
        if ( this_object()->is_container() )
                return "����";
        if ( this_object()->is_book() )
                return "����";
        if ( this_object()->is_money() )
                return "����";
        if ( this_object()->is_charm() )
                return "�����";
        if ( this_object()->is_rune() )
                return "����";
        if ( this_object()->is_inlaid() )
                return "��Ƕ��";
        if ( this_object()->is_task() )
                return "������Ʒ";
        return "����";
}

