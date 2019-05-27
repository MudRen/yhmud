// shield.c �׽ �׽�ͨ��

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill/*, qi, maxqi*/;


        //if (me->query("family/family_name") != "������")
        //        return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ�á��׽�ͨ������\n");
        if (userp(me) && ! me->query("can_perform/yijinjing/tong"))
                return notify_fail("����ѧ���ڹ���û�����ֹ��ܡ�\n");
                
        if (target != me)
                return notify_fail("��ֻ�����׽��Ϊ�Լ��׽�ͨ���� \n");

        if ((skill = (int)me->query_skill("yijinjing", 1)) < 100)
                return notify_fail("����׽�ȼ�������\n");

        if ((int)me->query("eff_qi")*100/(int)me->query("max_qi") > 80)
                return notify_fail("�����ƺ��ᣬ���ü����׽���߾�ѧ��\n");

        if ((int)me->query("eff_qi")*100/(int)me->query("max_qi") < 10)
                return notify_fail("������̫�أ��޷������׽���߾�ѧ��\n");

        if ((int)me->query("neili") < skill*5 || (int)me->query("max_neili") < 500)
                return notify_fail("�������������\n");

        me->add("neili", -skill*4);
        me->receive_damage("qi", 0);

        message_combatd(HIM "$N" HIM "Ĭ���׽�Ŀھ�: "
                            "Ԫ��,��������,�����⡣"
                            "�׽�,�л���Ϣ,����֧....\n"
                        HIW "һ����͵İ�ɫ�����ͷ��Ѹ��"
                        HIW "�α�" HIW "$N" HIW "���澭������\n"
                        HIC "$N" HIC "������ɲ�Ǽ��Ϊ��ת����\n" NOR, me);

        me->add("max_neili", -skill/4);

        me->add("eff_qi",skill*8);
        if (me->query("eff_qi") > me->query("max_qi"))
                me->set("eff_qi",me->query("max_qi"));
        me->set("qi",me->query("eff_qi"));

        if (me->is_fighting()) me->start_busy(4);

        return 1;
}
