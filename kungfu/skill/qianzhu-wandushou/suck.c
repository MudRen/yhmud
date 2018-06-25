#include <ansi.h>
inherit F_SSERVER;

int perform(object me,object target)
{
        int sp, dp, temp;
        int my_skill, my_force, tg_age, skill_count, duli;

        if (userp(me) && ! me->query("can_perform/qianzhu-wandushou/suck"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (environment(me)->query("no_fight"))
                return notify_fail("����̫���ӣ��㲻�ܾ�������������\n");

        if( !objectp(target)
        ||  target->query_temp("owner_id") != me->query("id") )   
                return notify_fail("��Ҫ��ȡʲô����Ķ��أ�\n");

     /*   if( target->query("age") < 99 )
                return notify_fail("�㿴����㣬�Ƕ������Ƕ�����\n"); */
	if( ! target->query("worm_poison") )
		  return notify_fail("�㿴����㣬�Ƕ������Ƕ�����\n"); 

        my_skill = (int)me->query_skill("qianzhu-wandushou", 1);
        my_force = (int)me->query_skill("xiuluo-yinshagong", 1);
        tg_age = (int)target->query("age");

        if( my_skill < 100 )
                return notify_fail("���ǧ�����ֻ��̫ǳ������������ȡ���أ�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ�������ǧ�����֣�\n");

        if( me->is_fighting() )
                return notify_fail("ս�����޷�����ǧ�����֣�\n");

        if( me->is_busy() )
                return notify_fail("����æ���أ�\n");

        if( target->is_fighting() || target->is_busy() )
                return notify_fail("������æ���أ����ܺ�����ϣ�\n");

        if( me->query_temp("wudu_suck") )
                return notify_fail("�����������У�\n");

        if (! me->can_improve_skill("qianzhu-wandushou"))
                return notify_fail("���ʵս���鲻�����޷���������ǧ�����֣�\n");

     
         if( tg_age - my_skill >= 50 )
                return notify_fail(target->query("name") + "�Ķ���������˵̫ǿ�ˣ�С�İ�С�����ˣ�\n"); 
         if( my_skill - tg_age >= 50 )
                return notify_fail(target->query("name") + "�Ķ���������˵�Ѿ�̫��΢�ˣ�\n"); 

        if( (int)me->query("neili") < 200 )
                return notify_fail("������������������ԶԿ����������С���͵���\n");

        if( (int)target->query("qi") < 50 )
                return notify_fail( target->query("name") + "�Ѿ�����һϢ�ˣ���"
                                    "�޷�����������ȡ�κζ��أ�\n");

        if( (int)me->query("qi") < 200 )
                return notify_fail( "��첻���ˣ������������ģ�\n");

        tell_object(me, RED "��С������Ľ����쵽" + target->query("name") +
                        RED "����ǰ���������ҧס�������ָ��������һ��\n����"
                        "���϶�ʱ����һ�ɺ���������ĺ���Ӷ�ͷ������������ֻ"
                        "����" + target->query("name") + RED "��\n�������˴�"
                        "ԴԴ���������˽������������鲼ȫ��\n\n" NOR );

        target->receive_wound("qi", 5);

        if( tg_age < 200 )
        {
                duli = 3;
        }

        if( tg_age > 200 && tg_age < 300)
        {
                duli = 5;
        }

        if( tg_age > 300 )
        {
                duli = 7;
        }
    
        //skill_count = duli * (10 + random((int)me->query_int()));
        skill_count = duli * (50 + random((int)me->query_int()));
        me->improve_skill("qianzhu-wandushou", skill_count);
        me->improve_skill("poison", skill_count);
        tell_object(me, HIC "��ġ�ǧ�����֡��͡���������������������ˣ�\n" NOR);

        me->set_temp("wudu_suck", 1);
        call_out("del_wudusuck", 3, me, target);
        return 1;
}

void del_wudusuck(object me,object target)
{
        if( me->query_temp("wudu_suck") )
        {
                me->delete_temp("wudu_suck");
                tell_object(me, RED "\nֻ�����Ķ���Խ��Խ�󣬡���ડ�һ������"
                                "���ڵ����˵��ϡ�" + target->query("name") + RED
                                "��������\nѪ������͸��һ�㱦�⣬���Ӷ�ʱ�Ǵ�"
                                "����࣡\n\n\n" NOR,);
                me->receive_damage("qi", 20);
        }

        target->set_temp("nopoison", 0);
}
