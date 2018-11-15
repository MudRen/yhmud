//Room: qunyulou2.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "群玉楼二楼");
        set("long", @LONG
群玉楼二楼。这是一座三层高的小楼，本来是某一位大亨陪同夫人
赏月之处，现在已被群玉楼用重金买下。只听一声声划拳行令，加杂着
女人的娇笑，不时的从房间中传出。
LONG);
        set("exits", ([ /* sizeof() == 6 */
        	"north" : __DIR__"qunyuys1",
        	"south" : __DIR__"qunyuys2",
        	"west"  : __DIR__"qunyuys3",
        	"east"  : __DIR__"qunyuys4",
        	"down"  : __DIR__"qunyulou1",
        	"up"    : __DIR__"qunyulou3",
        ]));
		if (random(5) > 3)
		set("objects", ([
        	__DIR__"npc/fuyun" : 1,
        ]) );

	setup();
        replace_program(ROOM);
}

void init()
{
        add_action("do_say", "say");
}

int do_say(string arg)
{
        string dir;
        object ob;

        if( ! arg || arg == "" ) return 0;

        if( arg == "天王盖地虎，宝塔镇河妖！" )
        {
                ob = new("/d/changan/npc/fuyun");
                ob->move("/d/changan/qunyulou2"); 
                message_vision(HIW "忽然屏风后面钻出一个鬼鬼祟祟的小老头。\n");     
                return 1;
        }
}