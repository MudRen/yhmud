inherit ROOM;

private void create()
{
    set("short", "�����Թ�");
    set("long", "������һ����������Ĵ����ţ���������뿪�Թ���\n");
    set("exits", ([
        "enter" : "/d/city/guangchang",
        "east" : __DIR__ "10,9,0",
        "south" : __DIR__ "9,8,0",
        "west" : __DIR__ "8,9,0",
        "north" : __DIR__ "9,10,0",
    ]));
    set("maze", "maze");
    set("outdoors", "maze");
}
