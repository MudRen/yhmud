// enchase.c
#include <ansi.h>
inherit ITEM;

int is_inlaid() { return 1; }

string chinese_s(mixed arg)
{
      if (! stringp(arg)) return "��";
      if (arg == "cold") return HIB "��" NOR;
      if (arg == "fire") return HIR "��" NOR;
      if (arg == "magic") return HIY "ħ" NOR;
      if (arg == "wind") return HIW "��" NOR;
      if (arg == "poison") return HIG "��" NOR;
      if (arg == "lighting") return HIM "��" NOR;
}

string extra_long()
{
        string str;
        
        str = "\n��Ʒ���� : ��Ƕ��\n";
        str += sprintf("��    �� : %d\n", this_object()->query_weight());
        str += sprintf("��    �� : %d\n", (int)query("enchase/consistence"));
        if (mapp(query("magic")))
        {  
                str += sprintf("ħ������ : %s\n", chinese_s(query("magic/type")));              
                str += sprintf("ħ �� ֵ : %d\n", (int)query("magic/power"));  
        }
        // str += sprintf("ʹ�÷��� : ����ָ�� enchase %s in <����> ��Ƕ��\n", query("id"));
        if (this_object()->query_autoload())
                str += "���߶�ʧ : ��\n";
        else
                str += "���߶�ʧ : ��\n";
        return str;
}
