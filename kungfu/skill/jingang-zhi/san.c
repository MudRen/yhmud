#include <ansi.h>
#include <combat.h>

#define DIE "��" HIR "һָ������" NOR "��"

inherit F_SSERVER;

string *xue_name = ({ 
"�͹�Ѩ", "����Ѩ", "����Ѩ", "��ԪѨ", "����Ѩ", "�м�Ѩ",
"�н�Ѩ", "��ͻѨ", "�ٻ�Ѩ", "����Ѩ", "����Ѩ", "���Ѩ",
"�Ϲ�Ѩ", "��ԨѨ", "�쾮Ѩ", "��ȪѨ", "����Ѩ", "����Ѩ", }); 

int perform(object me, object target)
{
        int damage, lvl;
        string msg, wp;
        object weapon;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/jingang-zhi/san"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))

                return notify_fail(DIE "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(DIE "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("jingang-zhi", 1) < 200)
                return notify_fail("��������ָ������죬����ʩչ" DIE "��\n");

        if ((me->query_skill_mapped("force") != "hunyuan-yiqi") && (me->query_skill_mapped("force") != "yijinjing") && (me->query_skill_mapped("force") != "luohan-fumogong"))
                return notify_fail("������û�м��������ڹ�Ϊ�ڹ�������ʩչ" DIE "��\n");
        if ((int)me->query_skill("jingluo-xue", 1) < 200)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" DIE "��\n");

        if (me->query_skill_mapped("finger") != "jingang-zhi")
                return notify_fail("��û�м����������ָ������ʩչ" DIE "��\n");

        if (me->query_skill_prepared("finger") != "jingang-zhi")
                return notify_fail("��û��׼���������ָ������ʩչ" DIE "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹�������ʩչ" DIE "��\n");

        if (me->query("max_neili") < 5000)
                return notify_fail("���������Ϊ���㣬����ʩչ" DIE "��\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("�����ڵ���������������ʩչ" DIE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        damage = (int)me->query_skill("finger") + (int)me->query_skill("force") + (int)me->query_skill("jinluo-xue",1); 
        damage += random(damage);
        lvl = (int)me->query_skill("jingang-zhi", 1);
        ap = me->query_skill("finger");
        dp = target->query_skill("parry");

        msg = HIW "ͻȻ��";
        
        msg += "$N" HIW "������ָ����" HIR "һָ������" HIW "���������ʱһ��"
               "����������ֱϮ$n" HIW "�ؿڣ�\n" NOR;
        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 150,
                                           HIR "���$n" HIR "��$N" HIR "һָ����"
                                           HIY + xue_name[random(sizeof(xue_name))] +
                                           HIR "��ȫ�������������ϣ���ʱŻ��һ��"
                                           "����Ѫ��\n" NOR);

                target->start_busy(lvl/30);
        } else
        {
                msg += CYN "����$p" CYN "�����磬ȫ��������$P"
                       CYN "�⾫���һָ��\n" NOR;
        }
       
        
        me->start_busy(3 + random(3));
        me->add("neili", -800);
        message_combatd(msg, me, target);

        return 1;
}

