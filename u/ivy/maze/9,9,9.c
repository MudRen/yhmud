inherit ROOM;

private void create()
{
    set("short", "��ħ�þ�");
    set("long", "������һ����������Ĵ����ţ���������뿪�þ���\n");
    set("exits", ([
        "enter" : "/d/city/guangchang",
        "east" : __DIR__ "10,9,9",
        "south" : __DIR__ "9,8,9",
        "west" : __DIR__ "8,9,9",
        "north" : __DIR__ "9,10,9",
    ]));
    set("maze", "maze");
    set("outdoors", "maze");
}
