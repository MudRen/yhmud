inherit ITEM;

int is_task() { return 1; }
varargs int move(mixed dest, int raw)
{
        object ob;

        if (::move(dest, raw)) 
        {
                ob = environment();
                if (objectp(ob) && ! this_object()->query("geter") && userp(ob)) 
                        this_object()->set("geter", ob->name(1));
                return 1;
        }    
}

/*
string extra_long()
{
        string str;
        
        str =  "\n��Ʒ���� : ������Ʒ\n";
        str += sprintf("��    �� : %d\n", query("weapon_prop/damage"));
        str += sprintf("��    �� : %d\n", this_object()->query_weight());
        str += sprintf("ɱ    ¾ : %d\n", query("combat/PKS"));
        // str += sprintf("ʹ�÷�ʽ : ����ָ�� wield %s װ����\n", query("id"));
        str += sprintf("                  ����ָ�� unwield %s ж�¡�\n", query("id"));
        if (this_object()->query_autoload())
                str += "���߶�ʧ : ��\n";
        else
                str += "���߶�ʧ : ��\n";
        return str;
}
*/
