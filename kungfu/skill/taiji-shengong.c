inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "yijinjing" ||
               force == "wudang-xinfa" ||
               force == "linji-zhuang" ||
               force == "emei-xinfa" ||
               force == "shaolin-xinfa";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taiji-shengong", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("gender") == "����"
           && (int)me->query_skill("taiji-shengong", 1) > 19)
                return notify_fail("���޸����ԣ����������������������̫���񹦡�\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ((int)me->query_skill("taoism", 1) < 100)
                return notify_fail("��Ե����ķ������̫ǳ���޷�����̫���񹦡�\n");

        if (me->query_skill("taoism", 1) < 320
           && me->query_skill("taoism", 1) < me->query_skill("taiji-shengong", 1))
                return notify_fail("��Ե�ѧ�ķ������ⲻ�������Զ���������̫���񹦡�\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("̫����ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"taiji-shengong/" + func;
}