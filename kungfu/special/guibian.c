// This program is a part of NITAN MudLIB
// sophistry.c �����ѧ
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIB "�����ѧ" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ͨ���Ӱټҵĸ���˼��ѧ˵���ڱ�����������\n"
                           "ɧ���ô˷��߿������Ƿǣ���ʯ�ɽ�ָ¹Ϊ��Ҳ\n"
                           "�����档ӵ�и��ؼ��������ȡ��ʦ������ʱ����\n"
                           "ǰ�����������㣬�Ҳ��������������ӵ�и��ؼ�\n"
                           "�����ʦ�������ȡ�Ĺ��׷�����\n");
}

