#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����������������п׷����������ʵ۶������������˼��������
�Լ��Ľ�ɽ��𢣬�����ʵ���ȻҲ�����⡣���ۺ��˵��ˣ����Ϲ��Ͼ�����
�����(pray)��
LONG );
        set("exits", ([
                "south" : __DIR__"dong_3",
        ]));

        set("objects", ([
                __DIR__"npc/shusheng1" : 2,
                __DIR__"npc/shusheng2" : 1,
                "/clone/npc/walker" : 1,
        ]));

        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_pray", "pray");
}

int do_pray(string arg)
{
        object me = this_player();
        int exp, pot, age, month, birthday, *born;

        age = me->query("age");
        month = me->query("mud_age");

        if (age >= 60)
        {
                month -= (age - 60) * 86400 * 4;
                month = (month - 118 * 86400) / 7200 / 4 + 1;
        } else
        if (age >= 30)
        {
                month -= (age - 30) * 86400 * 3;
                month = (month - 28 * 86400) / 7200 / 3 + 1;
        } else
        if (age >= 18)
        {
                month -= (age - 18) * 86400 * 2;
                month = (month - 4 * 86400) / 7200 / 2 + 1;
        } else
        {
                month -= (age - 14) * 86400;
                month = month / 7200 + 1;
        }

        if (month > 12 || month < 1)
                month = 1;

        born = localtime((((int)me->query("birthday")- 971000000) % 86400) * 365);
        birthday = born[4] + 1;
        exp = me->query("combat_exp");

        if (me->is_busy())
        {
                return notify_fail("��������æ���أ�û��������������\n");
        }

        message_vision(HIG "\n$N" HIG "��������ǰ�����������Ŀ���������ͷ��Ȼ��ĬĬ�����š�\n" NOR, me);

        if (age > 15 && month == birthday)
        {
            if (me->query("birthgift/" + age))
            {
                tell_object(me,
HIW
"     ����������������������������������������������\n"+
"     ��  ��������������������������������������  ��\n"+
"     ��  ��             "YEL"���տ���"HIW"             ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��             *  *"HIR"r"HIW"*  *            ��  ��\n"+
"     ��  ��          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         ��  ��\n"+
"     ��  ��         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        ��  ��\n"+
"     ��  ��         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        ��  ��\n"+
"     ��  ��         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        ��  ��\n"+
"     ��  ��        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       ��  ��\n"+
"     ��  ��        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       ��  ��\n"+
"     ��  ��        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       ��  ��\n"+
"     ��  ��         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        ��  ��\n"+
"     ��  ��           "GRN"^^\\_ \\// _/^^"HIW"          ��  ��\n"+
"     ��  ��               "GRN"\\_\\_/"HIW"              ��  ��\n"+
"     ��  ��                "GRN"/|\\"HIW"               ��  ��\n"+
"     ��  ��               "GRN"/\\\\/\\"HIW"              ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                  "RED"����Ⱥ��������"HIW"  ��  ��\n"+
HIW"     ��  ��������������������������������������  ��\n"+
"     ����������������������������������������������\n" NOR);
                tell_object(me, HIC "                 ���ù�" + chinese_number(sizeof(keys(me->query("birthgift")))) + "������ף��\n\n" NOR);
                me->start_busy(3);
                return 1; 
            }
            if (me->query("potential") > me->query_potential_limit()) 
            {
                    tell_object(me, YEL "ڤڤ֮����о��Լ��������ã��ɲ�֪��Ϊʲôû��Ч����\n" NOR);
                    return 1; 
            }

            if (exp >= 800000)
                    pot = age * 150 + random(age) * 30;
            else
            if (exp >= 500000)
                    pot = age * 100 + random(age) * 20;
            else
            if (exp >= 100000)
                    pot = age * 50 + random(age) * 10;
            else   
                    pot = age * 20;
            if (pot > 8000) pot = 8000;
            me->add("potential", pot);
            if (! me->query("skybook/guard/death"))
                    me->set("skybook/guard/death", 1);
            me->set("birthgift/" + age , 1);
            tell_object(me, HIR "���տ��֣�������" + chinese_number(pot) + "��Ǳ��ף����\n" NOR);
            tell_object(me,
HIW
"     ����������������������������������������������\n"+
"     ��  ��������������������������������������  ��\n"+
"     ��  ��             "YEL"���տ���"HIW"             ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��             *  *"HIR"r"HIW"*  *            ��  ��\n"+
"     ��  ��          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         ��  ��\n"+
"     ��  ��         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        ��  ��\n"+
"     ��  ��         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        ��  ��\n"+
"     ��  ��         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        ��  ��\n"+
"     ��  ��        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       ��  ��\n"+
"     ��  ��        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       ��  ��\n"+
"     ��  ��        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       ��  ��\n"+
"     ��  ��         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        ��  ��\n"+
"     ��  ��           "GRN"^^\\_ \\// _/^^"HIW"          ��  ��\n"+
"     ��  ��               "GRN"\\_\\_/"HIW"              ��  ��\n"+
"     ��  ��                "GRN"/|\\"HIW"               ��  ��\n"+
"     ��  ��               "GRN"/\\\\/\\"HIW"              ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                  "RED"����Ⱥ��������"HIW"  ��  ��\n"+
HIW"     ��  ��������������������������������������  ��\n"+
"     ����������������������������������������������\n\n" 
NOR);
            me->start_busy(5);
            return 1;
        }
        tell_object(me, HIB "��о��Լ�����û���κ�Ч����\n" NOR);
        me->start_busy(1 + random(10));
        return 1;
}
