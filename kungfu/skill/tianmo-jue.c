// tianmojue.c

inherit SKILL;

#include <ansi.h>

void create()
{
    seteuid(getuid());
}

string type() { return "knowledge"; }

int practice_skill(object me)
{
    return notify_fail("��ħ��ֻ�ܿ�ѧ(learn)����ߡ�\n");
}
void skill_improved(object me)
{
    tell_object(me, HIR "��о��Լ����ĳ�����ɱ¾��������\n" NOR);
    me->add("shen", -200);
}
