#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ͥԺ");
        set("long", @LONG
���������µĴ�Ժ����ɨ�÷ǳ��ɾ�����Ժ�����Ǽ�����ݣ�ȫ����ľ��
�ɣ������ľ����ľ�Ͼ���ȥƤ����Ȼ���ӣ�ȴ���Ժ���Ե�һ����̻Ի͵ĵ�
�ý�Ȼ��ͬ��
LONG );
        set("exits", ([
                "out" : "/d/tulong/yitian/was_damen",
                "east" : "/d/tulong/yitian/was_change",
                "west" : "/d/tulong/yitian/was_changw",
                "north" : "/d/tulong/yitian/was_zoulang1",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/zhao1" : 1,
                "/d/tulong/yitian/npc/qian2" : 1,
                "/d/tulong/yitian/npc/sun3" : 1,
                "/d/tulong/yitian/npc/li4" : 1,
                "/d/tulong/yitian/npc/zhou5" : 1,
                "/d/tulong/yitian/npc/wu6" : 1,
                "/d/tulong/yitian/npc/zheng7" : 1,
                "/d/tulong/yitian/npc/wang8" : 1,
        ]));

        setup();
}

int valid_leave(object me,string dir)
{
        object ob;

        if ( dir == "north" && ob = present("zhao yishang"))
        {
                message_vision(CYN "$N�ȵ���������Ҳ���Ҵ���ȥ���ɣ�\n" NOR,ob,me);
                ob->kill_ob(me);
                ob = present("qian erbai");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("sun sanhui");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("li sicui");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("zhou wushu");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("wu liupo");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("zheng qimie");
                if (objectp(ob)) ob->kill_ob(me);
                ob = present("wang bashuai");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("�򱱵�·�����������ס�ˡ�\n");
        }
        return 1;
}

