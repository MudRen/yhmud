// container.c

inherit ITEM;

int is_container() { return 1; }

string extra_long()
{
        string str;

        str =  "\n��Ʒ���� : ����\n";
        str += sprintf("��    �� : %d\n", this_object()->query_max_encumbrance());
        str += sprintf("��    �� : %s\n", this_object()->no_limit_amount() ? "��" : "��");
        str += sprintf("ʹ�÷��� : ����ָ�� put <id> in %s ���롣\n", query("id"));
        str += sprintf("                  ����ָ�� get <id> from %s ȡ����\n", query("id"));
        if (this_object()->query_autoload())
                str += "���߶�ʧ : ��\n";
        else
                str += "���߶�ʧ : ��\n";
        return str;
}
