// Written By Lonely@Nitan3

#include <ansi.h>

#pragma optimize
//#pragma save_binary

#define NAME    0
#define DESC    1
#define VALUE   2
/*
mixed *jewel = ({
        ({ "��ʯ��Ƭ", "һƬ��ʯ��Ƭ��", 80000 }),
        ({ "��ʯ", "һ���������ľ�����ʯ�������쳣��", 100000 }),
        ({ "ϡ����ʯ", "һ���������ľ�����ʯ�������Բ�ͬѰ���ĸо���", 120000 }),
        ({ "��֮��ʯ", "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�", 140000 }),
        ({ "ʥ֮��ʯ", "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�", 160000 }),
        ({ "ħ֮��ʯ", "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�", 180000 }),
        ({ "��֮��ʯ", "һ����˸�������â�ı�ʯ�����˸е�һ������ļ¡�", 200000 }),
});
*/
mapping special_data = ([
        /*
        "int"   : "��������",
        "str"   : "�������",
        "con"   : "�������",
        "dex"   : "������",
        	*/
        	//���� by н������ ͳһΪ���ַ�񣬿������롣�����������������ʱ������¡�
        	//���������������ʵ��query_per()�д�������Ч���ʶ���Ϊ��Ч��ò
        "personality"   : "��Ч��ò",
        "attack"        : "ս������",
        "defense"       : "ս������",
        "parry"         : "��Ч�м�",
        "dodge"         : "��Ч�Ṧ",
        "force"         : "��Ч�ڹ�",
        "armor"         : "ս������",
        "damage"        : "�����˺�",
        "unarmed_damage": "�����˺�",
        "unarmed"       : "��Чȭ��",
        "cuff"          : "��Чȭ��",
        "strike"        : "��Ч�Ʒ�",
        "hand"          : "��Ч�ַ�",
        "finger"        : "��Чָ��",
        "claw"          : "��Чצ��",
        "warm"          : "��ů����",
        	
        	/*
        	//������������Է���ο�
        "max_neili"     : "�����������",
        "max_jingli"    : "���������",
        "max_qi"        : "�����Ѫ����",
        "max_jing"      : "���������",
        "max_potential" : "���Ǳ������",
        "max_experience": "����������",
        "attack"        : "ս����������Ч�ȼ�",
        "defense"       : "ս����������Ч�ȼ�",
        "parry"         : "ս���м�����Ч�ȼ�",
        "dodge"         : "ս����������Ч�ȼ�",
        "armor"         : "ս��������",
        "damage"        : "ս�������˺���",
        "unarmed_damage": "ս��ȭ���˺���",
        "ap_power"      : "����ս���������ٷֱ�",
        "dp_power"      : "����ս���������ٷֱ�",
        "da_power"      : "����ս���˺����ٷֱ�",
        "add_poison"            : "������������Ч���ٷֱ�",
        "reduce_poison"         : "���ⶾ������Ч���ٷֱ�",
        "avoid_poison"          : "�رܶ����������ʰٷֱ�",
        "add_cold"              : "�����䶳����Ч���ٷֱ�",
        "add_fire"              : "�������湥��Ч���ٷֱ�",
        "add_lighting"          : "�������繥��Ч���ٷֱ�",
        "add_magic"             : "����ħ������Ч���ٷֱ�",
        "reduce_cold"           : "�����䶳����Ч���ٷֱ�",
        "reduce_fire"           : "������湥��Ч���ٷֱ�",
        "reduce_lighting"       : "�������繥��Ч���ٷֱ�",
        "reduce_magic"          : "����ħ������Ч���ٷֱ�",
        "avoid_cold"            : "�ر��䶳�������ʰٷֱ�",
        "avoid_fire"            : "�رܻ��湥�����ʰٷֱ�",
        "avoid_lighting"        : "�ر����繥�����ʰٷֱ�",
        "avoid_magic"           : "�ر�ħ���������ʰٷֱ�",
        "effjing_recover"       : "���ÿ��������ָ�ֵ",
        "effqi_recover"         : "���ÿ�������Ѫ�ָ�ֵ",
        "research_times": "�����о��Ĵ���",
        "learn_times"   : "����ѧϰ�Ĵ���",
        "practice_times": "������ϰ�Ĵ���",
        "derive_times"  : "������ȡ������",
        "study_times"   : "��������Ĵ���",
        "study_effect"  : "���������Ч���ٷֱ�",
        "learn_effect"  : "����ѧϰ��Ч���ٷֱ�",
        "avoid_parry"   : "�ر������мܻ��ʰٷֱ�",                     // ���ķ���
        "avoid_dodge"   : "�ر�����������ʰٷֱ�",                     // ���ķ���
        "avoid_attack"  : "�ر����⹥�����ʰٷֱ�",                     // ���ķ���
        "reduce_age"    : "�����Լ������",
        "research_effect"       : "�����о���Ч���ٷֱ�",
        "practice_effect"       : "������ϰ��Ч���ٷֱ�",
        "derive_effect"         : "������ȡ��Ч���ٷֱ�",
        
        "avoid_noperform"       : HIR "�رܾ���ʹ�����ƻ��ʰٷֱ�",         // �ռ�����
        "target_noperform"      : HIB "���ƶ���ʹ�þ��л��ʰٷֱ�",         // �ռ�����
        "add_busy"      : HIR "����æ������",                           // �ռ�����
        "reduce_busy"   : HIB "����æ������",                               // �ռ�����
        "avoid_busy"    : HIB "�ر�æ�һ��ʰٷֱ�",                         // �ռ�����
        "xuruo_status"  : HIR "�ö��ִ�������״̬���ʰٷֱ�",               // �ռ�����
        "avoid_xuruo"   : HIB "�ر��������ʰٷֱ�",                         // �ռ�����
        "add_skilllevel": HIR "�������м��ܵȼ�",                           // �ռ�����
        "add_damage"    : HIR "׷�������˺��ٷֱ�",                         // �ռ�����
        "reduce_damage" : HIB "���������˺��ٷֱ�",                         // �ռ�����
        	*/
]);

string special_desc(string arg)
{
        if (! undefinedp(special_data[arg]))
                return special_data[arg];
        else
                return to_chinese(arg);
}
