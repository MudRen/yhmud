#include <ansi.h>
inherit ROOM; 

void create() 
{ 
        set("short", HIR "Ѫ�ص���" NOR);
        set("long", HIR @LONG
Ѫ�ص�������������ô��ۺ���ߵ��������˵ġ��Ĵ�������Ũ���
Ѫ����ʲôҲ������������и������������ֵĹ��Ѫ���ﵽ����
������ͷ��ڵ���Ѫ��ʮ�ֲֿ���

LONG NOR);
        set("no_clean_up", 0);
        
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"yanluodian",
                "down"  : "/d/death/xuechi2",
        ]));
       
        setup();
}

int valid_leave(object me, string dir)
{
//      int i;
        object ob;
        me = this_player();
        if (dir == "down")
        {
                if (! present("qilin xue", me) || 
                    ! objectp(ob = me->query_temp("armor/boots")) ||
                    ob->query("id") != "qilin xue") 
                        return notify_fail(CYN "��û�д�����ѥ�޷�������ڵ�Ѫ���У�\n" NOR);
        }
        return ::valid_leave(me, dir);
}