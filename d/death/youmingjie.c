// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM; 

int num_of_killer;
string call_killer();

void create() 
{ 
        set("short", HIB "��ڤ��" NOR);
        set("long", HIB @LONG
��ڤ�磬��������ô��ۺ���ߵ��������˵ġ��Ĵ�������Ũ�����
����ʲôҲ������������и������������ֵĹ����Χ�ƺ���һ˫
˫�۾������㿴�������˼�������������б����һ��ʯ��(shibei)����
��æ������ȥ��������֡�

LONG NOR);
        set("no_clean_up", 0);
        set("item_desc", ([
                "shibei" : (: call_killer :),
        ]));

        set("objects", ([
        ]));
        
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"youmingdian",
                "south" : "/d/death/qiao2",
        ]));
       
        setup();
        reset();
}

void reset()
{
        ::reset();
        num_of_killer = 5;
}

string call_killer()
{
        object ob;
        if (num_of_killer == 0) 
        return "ʯ����д�ż���Ѫ��Ĵ��֣�
"HIR"        ۺ �� �� �� �� ڤ �� �� ����"NOR"
��Ȼ����ñ����ƺ��нŲ�����������Ȼ��ͷһ��������
ʲôҲû���֣�ԭ�����龪һ����\n";
        num_of_killer --;
        if (num_of_killer == 1)
        ob = new(__DIR__"npc/qinguangwang");
        else
        ob = new(__DIR__"npc/ghost");
        ob->move("/d/death/youmingjie");
        return "ʯ����д�ż���Ѫ��Ĵ��֣�
"HIR"        ۺ �� �� �� �� ڤ �� �� ����"NOR"
��Ȼ����ñ����ƺ��нŲ�����������Ȼ��ͷһ��������\n";
}


