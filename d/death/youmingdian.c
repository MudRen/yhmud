// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short", HIB "��ڤ��" NOR   );
        set("long", HIB @LONG
��������������£����������ľ�����������ڤ������󶼻���
�����ܵ�Ӧ�еĴ��á���ǰһ�Ŵ�������ǰ����ʮ�����ޡ�

LONG NOR);
        set("exits", ([ /* sizeof() == 1 */
                "south" : __DIR__"youmingjie",
                "north" : __DIR__"yanluodian",
        ]));
        
        set("hell", 1);
        set("no_fight", 1);
        
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/yanluo"        : 1,
                __DIR__"npc/yinchangsheng" : 1,
                __DIR__"npc/wangfangping"  : 1,                
        ]));
        setup();

}

int valid_leave(object me, string dir)
{
        //int i;
        //object ob;
        me = this_player();
        if (dir == "north")
        {
                if (! me->query("hell_quest/������") && ! me->query("HellZhenPass"))
                        return notify_fail(CYN "ʮ�����޿�����һ�ۣ��ȵ����㻹����"
                                           "��ȥ�������������ʲô���֣�\n" NOR);
        }
        return ::valid_leave(me, dir);
}

