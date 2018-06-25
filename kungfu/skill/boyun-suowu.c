/* boyun-suowu �������� */

inherit SKILL;

mapping *action = ({
([	 "action" : "$N˫��Ʈ������,ͻȻ�Ӳ�����˼��ĽǶȣ�����$n���ؿ�",
	 "dodge"  : 50,
	 "damage" : 30,
	 "lvl"    : 10,
	 "skill_name"  : "��������",
	 "damage_type" : "����"
]),
([	 "action" : "$N��Хһ����ƽ�ط������ɣ��Ӹ����½���ͷ�£�˫���ص���һ���˾�ѹ����֣�$n��ʧɫ",
	 "dodge"  : 60,
	 "damage" : 50,
	 "skill_name"  : "��������",
	 "damage_type" : "����"
]),
([	 "action" : "$n��ǰһ����ʧȥ$N����Ӱ��ֻ�����������һ���Ʒ磬ֻ��$N˫��ͬʱ����$n����Ҫ��",
	 "dodge"  : 70,
	 "damage" : 40,
	 "skill_name"  : "��������",
	 "damage_type" : "����"
]),
([	 "action" : "$N��ָ��������ò�ʩ������$n����·Ҫ��",
	 "dodge"  : 90,
	 "damage" : 50,
	 "lvl"    : 10,
	 "skill_name"  : "��������",
	 "damage_type" : "����"
]),
([	 "action" : "$N��������������˷�����������Ӱ��һ��ͻ���������������֮ʽ����$n",
	 "dodge"  : 120,
	 "damage" : 100,
	 "lvl"    : 80,
	 "skill_name"  : "��������",
	 "damage_type" : "����"
]),
});

string *parry_msg = ({
	 "$Nһ�л���$n���ϣ�ȴ��$n������ȥ��\n",
	 "$n����һ����$N�����Լ�����������ա�\n",
	 "$n��ǣ������$N��������������ת�˺ü���Ȧ��\n",
	 "$n����һת��$Nһ�л��ڵ��ϣ�ֻ��ó������\n",
});

int valid_enable( string usage )
{
	return( (usage == "hand") || (usage == "parry") );
}

string query_parry_msg( string limb )
{
	return(parry_msg[random( sizeof(parry_msg) )]);
}

int valid_learn( object me )
{
	if ( me->query_temp( "weapon" ) || me->query_temp( "secondary_weapon" ) )
		return(notify_fail( "���������������֡�\n" ) );

	if ( (int) me->query_skill( "biyun-xinfa", 1 ) < 10 )
		return(notify_fail( "��ı����ķ���򲻹����޷�ѧ��������\n" ) );

	if ( me->query( "max_neili" ) < 100 )
		return(notify_fail( "�������̫�����޷�����������\n" ) );

	return(1);
}

string query_skill_name( int level )
{
	int i;
	for ( i = sizeof(action) - 1; i >= 0; i-- )
		if ( level >= action[i]["lvl"] )
			return(action[i]["skill_name"]);
}

mapping query_action( object me, object weapon )
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
	int	d_e1	= 20;
	int	d_e2	= 40;
	int	p_e1	= -35;
	int	p_e2	= 15;
	int	f_e1	= 200;
	int	f_e2	= 300;
	int	i, lvl, seq, ttl = sizeof(action);

	lvl = (int) me->query_skill( "boyun-suowu", 1 );
	for ( i = ttl; i > 0; i-- )
		if ( lvl > action[i - 1]["lvl"] )
		{
			seq = i;        /* �������������� */
			break;
		}
	seq = random( seq );            /* ѡ������������ */
	return([
		       "action"      : action[seq]["action"],
		       "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
		       "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
		       "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
		       "damage_type" : random( 2 ) ? "����" : "����",
	       ]);
}

/*
 * int learn_bonus()
 * {
 * return(15);
 * }
 *
 * int practice_bonus()
 * {
 * return(15);
 * }
 *
 * int success()
 * {
 * return(15);
 * }
 *
 * int power_point( object me )
 * {
 * return(1.0);
 * }
 */

int practice_skill( object me )
{
	if ( me->query( "qi" ) < 30 )
		return(notify_fail( "�������̫���ˡ�\n" ) );

	if ( me->query( "neili" ) < 100 )
		return(notify_fail( "���������������������\n" ) );

	me->receive_damage( "qi", 25 );
	return(1);
}

string perform_action_file( string action )
{
	return(__DIR__ "boyun-suowu/" + action);
}

int query_effect_parry( object attacker, object me )
{
	int lvl;

	lvl = me->query_skill( "boyun-suowu", 1 );
	if ( lvl < 80 )
		return(0);
	if ( lvl < 200 )
		return(50);
	if ( lvl < 280 )
		return(80);
	if ( lvl < 350 )
		return(100);
	return(120);
}
