// �����Թ�
// by Lonely
// inherit VRM_SERVER;
#include <ansi.h>
inherit "/adm/daemons/vrm_server";

void create()
{
        //�Թ��������̳е�����ĵ������ơ�
        set_inherit_room( ROOM );

        //�Թ�������Ĺ��
        //set_maze_npcs(__DIR__"npc/baihu");

        //�Թ��ĵ��߳�
        set_maze_long(10);

        //��ڷ���(�����ڶ���)
        set_entry_dir("south");

        //�������������ӷ���
        set_link_entry_dir("south");

        //�������������ӵ�����
        set_link_entry_room(__DIR__"jimiesi");

        //��������������ӷ���
        set_link_exit_dir("north");

        //��������������ӵ�����
        set_link_exit_room(__DIR__"baihuxue");

        //��ڷ��������
        set_entry_short(HIB "��ɭ��" NOR);

        //��ڷ�������
        set_entry_desc(HIB @LONG
�����˵���Ǻ�ɭ�֣�����ȫ�������������ˣ���С�ľͿ�����
ʧ�����ˡ�
LONG NOR);

        //���ڷ��������
        set_exit_short(HIB "��ɭ��" NOR);

        //���ڷ�������
        set_exit_desc(HIB @LONG
����ǰһ������������˿��������������ǳ����ˡ�������ɫ����һ
�䣬��ǰ����һ���ں�����ɽ����
LONG NOR
);

        //�Թ�����Ķ�����
        set_maze_room_short(HIB "��ɭ��" NOR);

        //�Թ����������������ж�������������ÿ����
        //���ʱ���������ѡ��һ����
        set_maze_room_desc(HIB @LONG
����Խ��Խ���ˣ��㵨���ľ�����ǰ�����ţ�������һЩ
��·�˵�ʬ������á���ʱ����һ�����޶��Ǻ�,������ʲô
�����ڰ��п����ţ��㲻�ɵļӿ��˽Ų���
LONG NOR
);

        // �Թ������Ƿ�Ϊ���ⷿ�䣿
        set_outdoors(0);
}


