#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ͥԺ");
        set("long", @LONG
���������µ���Ժ����ɨ�÷ǳ��ɾ�����Ժ�����Ǽ�����ݣ�ȫ����ľ��
�ɣ������ľ����ľ�Ͼ���ȥƤ����Ȼ���ӣ�ȴ���Ժ���Ե�һ����̻Ի͵ĵ�
�ý�Ȼ��ͬ�����ﵽ�������ɹű����䱸�������ϡ�
LONG );
        set("exits", ([
                "west" : "/d/tulong/yitian/was_dayuan",
        ]));

        set("objects", ([
                "/d/tulong/yitian/npc/bing1" : 5,
        ]));

        set("outdoors", "beijing");
        setup();
}


