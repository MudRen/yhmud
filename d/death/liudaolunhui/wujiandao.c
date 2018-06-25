// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;

void recreate();

string *enter_msg = ({
        HIB+"\n��ֻ������ǰһ����ͻȻʲôҲ��������ʲôҲ������......\n\n"+NOR,
        HIB+"ֻ�������岻�ϵ���׹......\n\n"+NOR,
        HIB+"׹���޾��ĺڰ�......\n\n"+NOR,
        HIB+"��Ȼ�·�һֻ����������һ��......\n\n"+NOR,
        HIB+"ڤڤ����Լ�������󶣶�������ײ��......\n\n"+NOR,
        HIB+"������һ���������Լ���������һ���������ƺ�����İ��������......\n\n"+NOR,
});

void entering_world(object me, int n);

void create()
{
        set("short", HIW "\n\n                ��        ��        ��" NOR);
        set("long", HIW "\n"
"��������������粻�ܵ��ռ��޼䣬����û���κγ�·��ֻ�кڰ���\n\n" NOR);

        setup();
}

void init()
{
        set("poem_said", 0);
        add_action("do_say", "say");
        add_action("do_enter", "enter");
        add_action("do_smash", "smash");
}

int do_say(string arg)
{
        string dir;
        object ob;

        if( ! arg || arg == "" ) return 0;

        if( arg == "Ǳ�����ޣ�������ͨ����ӻ������������ף�" 
        &&  (int)query("poem_said") != 1 )
        {
                message_vision(HIW "\nֻ��$N" HIW "��Ȼ�����ȵ�����Ǳ����"
                               "�ޣ�������ͨ����ӻ������������ף���\n" NOR + 
                               HIR "\n$N" HIR "������"
                               "�䣬����ͻȻ����¡¡���ζ��˼��¡���ǰ��"
                               "����һ�����ӡ�\n\n"
                               NOR, this_player());
                ob = new("/d/death/obj/wujian");
                ob->move(this_player(), 1); 
                message_vision(HIW "ͻȻ����������������޵�֮���޼���������ŵ������紩��$N�Ļ��У�\n", this_player());     
                this_object()->recreate();
                set("poem_said", 1);
                return 1;
        }

        if( arg == "Ǳ�����ޣ�������ͨ����ӻ������������ף�" && (int)query("poem_said") == 1 )
        {
                write(HIC "\n����źڰ�һ���ͺȣ�������˾�ڻص��˺�һ������š�\n" NOR);
                return 1;
        }
}

void recreate()
{
        set("short", HIW "\n\n                ��        ��        ��" NOR);
        set("long", HIW "\n"
"��������������粻�ܵ��ռ��޼䣬����û���κγ�·��ֻ�кڰ���\n"
"ǰ����һ������һ�˸ߵĴ�ͭ��(mirror)��\n\n" NOR);

        set("item_desc", ([
                "��ͭ��": "һ������һ�˸ߵĴ�ͭ������ֵ��Ǿ�����һƬ���磬�ղ����κ���Ӱ��\n",
                "ͭ��"  : "һ������һ�˸ߵĴ�ͭ������ֵ��Ǿ�����һƬ���磬�ղ����κ���Ӱ��\n",
                "mirror": "һ������һ�˸ߵĴ�ͭ������ֵ��Ǿ�����һƬ���磬�ղ����κ���Ӱ��\n",
        ]));
        set("objects", ([
                "/d/death/npc/ghost" : 21,
        ]));
        set("poem_said", 1);
        setup();
}


int do_enter(string arg)
{
        object me = this_player();
        
        if (! query("poem_said")) return 0;
       
       //������ֹתǰ��ʱת������ 2017-02-21
                if (me->query_skill("force") < 800)
                	return notify_fail("����书��Ϊ̫�ȥ���������ɣ�\n");
      //������ֹתǰ��ʱ����ת�����ɽ���
      
        if (objectp(present("ghost", environment(me)))) 
                return notify_fail("�㻹���Ƚ������Щ����ɣ�\n");
              
        me->set_temp("entering_world", 1);
        message_vision("$N����ͭ���ķ�����ȥ��\n",me);
        call_out("entering_world", 1, me, 0);
        return 1;
}

void entering_world(object me, int n)
{
        object item; 

        remove_call_out("entering_world");

        tell_object(me, enter_msg[n]);

        if (n == sizeof(enter_msg) - 1)
        {
                me->delete_temp("entering_world");
                tell_room(environment(me), sprintf(HIY"ͭ���зų�һ���������%s�����%s�����ˡ�\n"NOR,
                          me->name(), me->name()), ({ me }));
                          
                me->clear_condition();
 
                foreach (item in all_inventory(me))
                {
                        message_vision("$N������$n��\n", me, item);
                        if (item->is_character())
                                item->move(environment(me));
                        else
                                destruct(item);
                }

                // ѡ�����⼼��
                UPDATE_D->zhuan_player(me);

                me->move("/d/city/wumiao");
                me->set("startroom", "/d/city/wumiao");
                tell_room(environment(me),me->name()+"ͻȻ��������ǰ��\n",({me}));                                
                me->save();
                return;                
        }
        else
        {
                call_out("entering_world", 3, me, n + 1);
                return;
        }
}

int do_smash(string arg)
{
        object ob, weapon;
        object me = this_player();

        if (! objectp(weapon = me->query_temp("weapon")) || 
            weapon->query("id") != "wujian shandian")
                return notify_fail("��û��װ���޼����磬�޷�ʹ���� smash ������\n");

        if (! arg)
                return notify_fail("ָ���ʽ: smash <living>\n");
        
        ob = present(arg, environment(me));
        if (! ob )        
                return notify_fail("�Ҳ���������\n");

        message_vision(HIM "�޼����绯�������������" + ob->query("name") + "...\n\n"
                       NOR, me);        
        if (! ob->is_character())
        {
                message_vision(HIM + ob->name() + HIM "�������������ʧ��...\n\n"
                               NOR, me);
                destruct(ob);
                return 1;
        }
        
        ob->die();
        
        return 1;
}


