
#include <ansi.h>
inherit ROOM; 

void create() 
{ 
        set("short", HIR "Ѫ�ص���" NOR);
        set("long", HIR @LONG
Ѫ�ص�������������ô��ۺ���ߵ��������˵ġ��Ĵ�������Ũ���
Ѫ����ʲôҲ������������и������������ֵĹ��Ѫ���ﵽ����
������ͷ��ڵ���Ѫ��ʮ�ֲֿ���ֻ�������������ڳ��������⡣

LONG NOR);
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xuanwu" : 1,
        ]));

        set("exits", ([ /* sizeof() == 2 */
                "up"  : "/d/death/xuechi1",
        ]));
       
        setup();
}
