#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIG "�������⴫��" NOR+HIW "�칫��" NOR );
        set("long", @LONG                     
�����⴫������Ⱥ������Ϊ����ṩ�������ַ������֯�������ǰ칫
���������ɹ���Ա����ʰҶ���𣬻�˵�ھ�¥����칫�����ǹ��ݳ޵ģ�Ҳ
�������������ڸ�Щʲô������Կ������ұ���һ����ѯ����advisory����
�����һ������̨��serve����
LONG );
        set("no_fight", 1); 
        set("item_desc", ([
                 "advisory" : HIW "�������⴫��"NOR+HIY"����Ϸ��Ϊ����ṩ�������з������֯��\n" NOR,
                 "serve" :  "����̨��д�ţ�\n"
                            "    ������̶�����ǣ����Ǻã�\n"
                            "�����ṩ�ܶ����ַ�����Ŀ�����������Ȥ���Ե�mud.gameivy.com������\n\n"
                            "                                                                 ����ʰҶ      \n\n",
        ]));
        set("objects", ([
                __DIR__"npc/wfoxd-mm": 2,
        ]));
        set("exits", ([
                "south" : __DIR__"zuixianlou",
                "up" : "/u/ivy/mogong",
        ]));
        setup();
        "/clone/board/wfoxd_b"->foo();
        replace_program(ROOM);
}