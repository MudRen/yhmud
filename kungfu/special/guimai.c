// guimai.c ��������
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ǧ��һ�������⾭��������������\n"
                           "�������˾�����Ӥ����������Ϊ������\n"
                           "��ҽ�������䷨����������ز�ۡ�����\n"
						               "��Ů������ֱ��������а�������ǿ���ħ\n"
						               "�������������Թ�������������ֵ���ޱ�\n"
						               "һ����Ҫ�ͣ����������ޱ�һ���˸ߣ���\n"
						               "�ж���������ʱ���󽵵��߻���ħ���ʡ�\n"
						               "�о�����ħ���ͱ�а����ʱ��������Ѷȡ�\n");
}