// MODIFY BY RCWIZ 2003

#include <ansi.h>
#include <combat.h>

#define FEI "��" HIG "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
//	object weapon;
	string msg;
	int skill;
	
	skill = me->query_skill("shenxing-baibian", 1);

	
		if (skill < 60)
				return notify_fail("������аٱ䲻����죬����ʹ��" FEI  "��\n");

        if (me->query_skill_mapped("dodge") != "shenxing-baibian")
                return notify_fail("��û��ʹ�����аٱ䣬�޷�ʩչ" FEI  "��\n");
			
		if (me->query_temp("shenxing"))
                return notify_fail("���Ѿ�����������翡��ˡ�\n");
			
		if ((int)me->query_condition("cd_drug") > 0)
				return notify_fail("���ڶ�ʱ�����޷�����ʩչ" FEI  "��\n");

        if (me->query("neili") < 60)
                return notify_fail("�����������������޷�ʩչ" FEI  "��\n");

        msg = HIM "ֻ��$N" HIM "��ȫ���������ת�𶯣����ζ�һ���һ�Σ�"
              "��������ҡ����������������ʵʵ��Ʈ�첻����\n" NOR;
		
		message_sort(msg, me);
			  

			me->add("neili", -100);
			me->add_temp("apply/dodge", skill);
			me->set_temp("shenxing", 1);
			me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), 3);
			me->apply_condition("cd_drug", 2);//20��cd��˧����3��
	
	return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("shenxing"))
        {
                me->add_temp("apply/dodge", -amount);
                me->delete_temp("shenxing");
                tell_object(me, "��ġ�������翡��˹���ϣ��������ջص��\n");
        }
}