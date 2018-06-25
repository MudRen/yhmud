#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, club;
        
        if (userp(me) && !me->query("can_perform/weituo-chu/jishi"))
                return notify_fail("�㻹����ʹ�á��������ա�!\n");

        if( !target && me->is_fighting() ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("���������ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon = me->query_temp("weapon")) 
           || weapon->query("skill_type") != "staff" )
                return notify_fail("���������ƣ��������á��������ա�����\n");

        if( me->query_temp("sl_leidong") )
                return notify_fail("���ʹ�꡸�������ա���Ŀǰ��Ѫ��ӿ���޷��ٴ����ã�\n");
        
        if( (int)me->query_skill("weituo-chu", 1) < 120)
                return notify_fail("��Τ������Ϊ����������δ��ʹ�á��������ա���\n");

        if( me->query_skill("force", 1) < 120 )
                return notify_fail("����ڹ���Ϊ���δ����ʩչֻ���˼�����\n");                             
      
        if( me->query("max_neili") <= 1500 )
                return notify_fail("���������Ϊ���㣬����������ʩչ���������ա���\n");

        if( me->query("neili") <= 600 )
                return notify_fail("�����������������������ʩչ���������ա���\n");

        message_vision(BLU "\nͻȻ$N���һ�������������ա�����ɫ৵ı��ͨ�죬�뷢�Էɣ���������" + 
                           weapon->name() + BLU "���У����ˡ���һ��������" HIW " �������� " BLU "��\n " NOR, me);
        
        damage = me->query_skill("weituo-chu", 1) + me->query_skill("buddhism",1);
        damage /= 6;
        club = me->query_skill("staff") / 3;
        
        if ( userp(me) ) 
        {
                me->add("neili", -300);
                me->start_busy(1);
                if ( damage > weapon->query("weapon_prop/damage") * 2)
                     damage = weapon->query("weapon_prop/damage") * 2;
                else weapon->add("rigidity", 1);
        }

        me->set_temp("sl_leidong", 1); 
        me->add_temp("apply/damage", damage);
        me->add_temp("apply/attack", damage);
        
        call_out("remove_effect1", club/2, me, weapon, damage);
        call_out("remove_effect2", club * 2/3, me);
        me->start_perform(club * 2 / 6, "���������ա�");

        return 1;
}

void remove_effect1(object me, object weapon, int damage) 
{
        if (!me) return;
        me->add_temp("apply/attack", -damage);  

        if (!weapon) {
                me->set_temp("apply/damage", 0);
                return;
        }
        me->add_temp("apply/damage", -damage);
        message_vision(HIY "\n$Nһ�ס��������ա�ʹ�꣬����"NOR + weapon->name() + HIY"�ϵĹ�â����Ҳ��ʧ�ˡ�\n"NOR, me);                
}

void remove_effect2(object me)
{
        if (!me) return;
        me->delete_temp("sl_leidong");
        tell_object(me, HIG "\n �㾭��һ��ʱ�������Ϣ���ֿ���ʹ�á��������ա��ˡ�\n"NOR); 
}

