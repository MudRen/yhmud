inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
        int lvl, max;

        lvl = me->query_skill("count", 1);
		max = 300;

        if (me->query("family/family_name") == "�һ���")
        {
                lvl -= 50;
				max += 50;
        }

        if ((int)me->query("int") * 10 < lvl || lvl > max) 
                return notify_fail("����������Բ��㣬��������������Եİ��\n");
			
		if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("�������֪ʶ���ޣ��޷�������µ��������ԡ�\n");
		/*	
		//ȡ��countѧϰ����
		if ((int)me->query("int") < gift)
                return notify_fail("����������Բ��㣬��������������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < mat)
                return notify_fail("�������֪ʶ̫��޷�����������Եİ��\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("�������֪ʶ���ޣ��޷�������µ��������ԡ�\n");
        //����û���Ÿ����Ի�������Ч������ʵ��Ч������ȡ����
        //ת���ؼ�ѭӰ����
        if (me->query_skill("zuoyou-hubo", 1) && !me->query("special_skill/qinzong"))
                return notify_fail("���ܵ����һ�������֮��Ӱ�죬��������������Եİ��\n");
*/
        return 1;
}
