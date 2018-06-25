inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yijin-duangu", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([      "action":"$NĬ���˹��������׽�͹ǵĿھ�����Ϣ������������������һ��"
]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}


int valid_learn(object me)
{
        if (me->query("gender") == "����" && (int)me->query_skill("yijin-duangu", 1) > 49)
                return notify_fail("���޸����ԣ�����������������������׽�͹��ڹ���\n");

        if (me->query("character") == "�ĺ�����" && (int)me->query("yijin-duangu", 1) > 199)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "���ĺ������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

        if (me->query("character") == "������" && (int)me->query("yijin-duangu", 1) > 169)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "�������������ƺ�ֻ��ѧ�����̶ֳȡ�\n");

        if (me->query("character") == "���ռ�թ" && (int)me->query("yijin-duangu", 1) > 139)
                return notify_fail("������澭�������ص��׽�͹�����ֺ룬����ٲȻ������"
                                   "�����ռ�թ�������ƺ�ֻ��ѧ�����̶ֳȡ�\n");
          if (me->query("con") < 30)
                  return notify_fail("������Լ�������ǲ��㣬һʱ����������\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�׽�͹��ڹ���\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("�׽�͹��ڹ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"yijin-duangu/" + func;
}
