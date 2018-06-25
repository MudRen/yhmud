// zixia-shengong.c ��ϼ��
// By Hop

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) 
{       return force == "huashan-xinfa" ||
               force == "henshan-xinfa" ||
               force == "songshan-xinfa" ||
               force == "hanbing-zhenqi" ||
               force == "zhenyue-jue"; 
}

int query_neili_improve(object me)
{
        int lvl;
		lvl = (int)me->query_skill("zixia-shengong", 1);
		
		if ((int)me->query_skill("pixie-jian", 1) > 300)
		        return lvl * lvl * 15 * 5 / 100 / 200;
		else
				return lvl * lvl * 15 * 14 / 100 / 200;
}

int valid_learn(object me)
{
	//if (me->query("gender") == "����" &&
	//    (int)me->query_skill("zixia-shengong", 1) > 49)
	//	return notify_fail("���޸����ԣ������������������������ϼ�񹦡�\n");

	if ((int)me->query_skill("force", 1) < 60)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ��ϼ�񹦡�\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��ϼ��ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level(object me)
{
		me = this_player();

        if ((int)me->query_skill("pixie-jian", 1) > 300)
                return 500;
        else
                return 50;
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
