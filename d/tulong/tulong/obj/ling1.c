#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void init()
{
        add_action("do_du", "yanjiu");
        add_action("do_du", "research");
}

void create()
{
        set_name(CYN "ʥ����" NOR, ({ "shenghuo ling", "shenghuo", "ling" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "�����̵ģ�����ʲô���⣿");
                set("long", CYN "����һ�����������ĺ��ƣ��ǽ�������ʵؼ�Ӳ�ޱȣ�\n"
                                "��͸���������������л�����ڣ�ʵ��������ӳ�⣬��\n"
                                "ɫ��á����Ͽ̵��в��ٲ�˹���֡� \n" NOR);
                set("wield_msg", CYN "$N��ৡ���һ������������һƬ����������������С�\n");
                set("unwield_msg", CYN "$N��ʥ���������䡣\n" NOR);
        }
        init_sword(100);
        setup();
}

int do_du(string arg)
{
        object me = this_player();
//      object where = environment(me);
//      object ob;
//      mapping skill;
        int pxlevel; 

        if (!(arg=="shenghuo ling" || arg == "shenghuo" || arg == "ling" ))
        return 0;
        if (me->is_busy()) {
                write("��������æ���ء�\n");
                return 1;
        }
        if( me->is_fighting() ) {
                write("���޷���ս����ר�������ж���֪��\n");
                return 1;
        }
        if (!id(arg)) { 
                write("��Ҫ��ʲô��\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");
                return 1;
        }
        if( me->query_skill("sanscrit", 1) < 199){
                write("�������ˮƽ̫�ͣ��޷�����ʥ�����������ص����ݡ�\n");
                return 1;
        }

        message("vision", me->name() + "��ר�ĵ��ж�ʥ���\n", environment(me), me);

        if( (int)me->query("jing") < 80 ) {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        if( (int)me->query("qi") < 80 ) {
                write("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
                return 1;
        }
        pxlevel = me->query_skill("shenghuo-ling", 1);

        if( (int)me->query("combat_exp") < 100000 ) {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }
        if( (int)me->query("combat_exp") < (int)pxlevel*pxlevel*pxlevel/10 ) {
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }
        if( me->query_skill("shenghuo-ling", 1) > 49){
                write("���ж���һ��������Ƿ���ʥ�����������صĶ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
                return 1;
        }
        me->receive_damage("qi", 50);
        me->receive_damage("jing", 50);
        me->improve_skill("shenghuo-ling", (int)me->query_skill("literate", 1)/5+1);
        write("���ж�ʥ��������ĵá�\n");
        return 1;
}
