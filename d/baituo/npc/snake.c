// Code of ShenZhou
// animal: snake.c
// Jay 3/18/96
#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name("����", ({ "snake", "she" }) );
        set("age", 4);
        set("long", "һֻ�����������Դ����ߣ�β��ɳɳ���졣\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n��$N˻��һ����ͷ");
        set("msg_succ", "$n˻˻���죬��ͷ����$N���ֶ�������");
        set("msg_trained","$n������Ϣ���ε�$N�Ľ��²�����");
        set("auto_follow",0);
        set("wildness", 9);

        set("str", 26);
        set("con", 30);

        set("combat_exp", 1000);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 6);
        set_temp("apply/armor", 2);

        setup();
}

void init()
{
        object ob;
        ::init();
	add_action("convert","bian");
        if (interactive(ob = this_player()) &&
	    ob->query("family/family_name") != "ŷ������" &&
                random(ob->query_kar() + ob->query_per()) < 30) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}
void die()
{
        object ob;
        ob = new(__DIR__"obj/shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}


mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
       int poison;
       poison = me->query("snake_poison");

	if( poison > 0 && !victim->query("snake_poison")) 
             victim->affect_by("snake_poison",
                              ([ "level" : poison/5 + random(poison/5),
                                 "id"    : me->query("id"),
                                 "duration" :  poison/20 ]));
       return HIR "ֻ��$nʹ����һ���������ߺݺݵ�ҧ��һ�ڣ�\n" NOR;
	if (me->query("bite_busy")) victim->start_busy(2);
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she") return 0;
	if (me->query("family/family_name") != "ŷ������") 
		return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
	if (random(me->query_skill("training",1)) <20) {
		kill_ob(me);
		return 1;
	}
	message_vision("$N���ְ�ס��ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
		me,);
	        ob = new("/d/baituo/obj/shezhang");
        ob->move(environment(this_object()));
        destruct(this_object());
	return 1;
}

