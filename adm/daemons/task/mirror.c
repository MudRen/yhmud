
#include <ansi.h>
#define   TASK_OBJ_PATH  "/adm/daemons/task/obj/"       //task���Ŀ¼


 
inherit ITEM;

void create()
{
        set_name(HIR"Ǭ" HIY"��" HIW"��" HIG "��" NOR, 
                   ({ "bao jing", "jing", "mirror"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "������ͥʧ���һ�汦������˵����ǧ�ﶨλ��\n"NOR);                     
                set("unit", "��");
                set("weight", 10);
                set("material", "tian jing");   
                set("no_sell", 1);
                set("no_put",  1);
                set("no_store",1);
            //    set("no_give",1);
             }           
        setup();
}

void init()
{
        add_action("do_locate", "locate");
        add_action("do_locate", "mirror");
        add_action("do_task",   "task");
        add_action("do_task",   "listtask");
}

int do_locate( string arg )
{ 
        //object ob, npc, env, me, room;
        object ob, npc, env, me;
        string msg, *msg_arr, dir_name, dir_total;
        mapping dir;
        int dir_tot_num, x, rank, file, per;

        me = this_player();
        dir_total = ""; 

    if ( me->is_busy() )
    return notify_fail("��������æ��û��ʹ�ñ�����\n");
        
    if ( query("power") <= 0 )
    return notify_fail("���Ǭ�������Ѿ�û�������ˣ�\n");

    if (!arg) 
    return notify_fail("��Ҫ��λʲô������\n");
        
        if ( file_size( TASK_OBJ_PATH + arg + ".c" ) < 0 )
        return notify_fail(HIR"û�����TASK��Ʒ��\n"NOR);

        ob = find_object(TASK_OBJ_PATH + arg );

        if (! ob)
        return notify_fail(HIC + arg + "�����Ʒ�Ѿ����ԭ���ˣ�\n"NOR);

        npc = environment(ob);

        if (! npc || npc == 0)
        return notify_fail("ȷ������" + arg + "��λ�á�\n");       

        if ( npc->is_player() )
        return notify_fail("������������Ѿ����������ˣ����Ϲæ�ˡ�\n");
 
        me->start_busy(2);

        if ( ! npc->is_character() )
                {
                        env = npc;
                }
        else
                {
                        env = environment(npc);                 
                }
        msg = env->long();   //��Ʒ���ڷ��������
        per = sizeof(msg)/2 * ( 100 - query("power"))/100;

    dir = env->query("exits");      //��Ʒ���ڵĵط��м�������
        
    foreach(dir_name in keys(dir))

        {
               dir_total += " " + dir_name + " ";
               dir_tot_num += 1;
        }
    

         msg_arr = explode(msg,"\n");

         for (x = 0; x < per; x++)
         {
            rank = random(sizeof(msg_arr));

            file = random( strlen(msg_arr[rank])/2 ) * 2;

            msg = replace_string( msg, msg_arr[rank][file..(file+1)],
                  HIG"[]"NOR,1);

         }

        if ( ! msg || msg == 0)        
        return notify_fail("ȷ������" + arg + "��λ�á�\n");

           tell_object(me, WHT "Ǭ��������ʾ" NOR + ob->name() + NOR
                       WHT"�������ڵط���������:\n\n" NOR + msg + "\n" + 
                         "����ط��ĳ�����"HIG + dir_total + NOR"��\n");

       this_object()->add("power",-(random(3) + 3));
       if ( this_object()->query("power") < 0 )
       this_object()->set("power", 0);
       return 1;

}

int do_task( string arg)
{ 
     if ( ! arg )
     {
         //string msg, msg1, msg2, space, *i_list;
         string msg, msg1, space, *i_list;
         object task;
         int x,len;

         if ( this_player()->is_busy() )
         return notify_fail("��������æ��û��ʹ�ñ�����\n");

         i_list = get_dir(TASK_OBJ_PATH);
         msg = "";
         msg1 = "";
         space = "                                                         ";

         msg += "=================================================="
                "====================\n";
         msg += HIG"                         ��������ʹ����\n\n"NOR;

         for(x=0; x<sizeof(i_list); x++)
         {
             task = find_object(TASK_OBJ_PATH + i_list[x]);
             if ( ! task)
             {
                task = load_object(TASK_OBJ_PATH + i_list[x]);
                msg1 = task->query("owner") + "��" + task->name() + "(" +
                       task->query("id") + ")";
                len = sizeof(task->query("owner")) + 4 +
                      sizeof(filter_color(task->name())) +
                      sizeof(task->query("id"));
                len = 26 -len;

                msg1 = msg1 + space[0..len] + HIB"(����)"NOR;

                destruct(task);
             }

            if ( task )
             {
                msg1 = task->query("owner") + "��" + task->name() + "(" +
                       task->query("id") + ")";
                len = sizeof(task->query("owner")) + 4 +
                      sizeof(filter_color(task->name())) +
                      sizeof(task->query("id"));
                len = 26 -len;

                msg1 = msg1 + space[0..len] + HIG"(δ��)"NOR;

             }
            if ( x % 2 == 1 )
            {
               msg += msg1 + "\n";
            }
            else
            {
               msg += msg1 + "  ";
            }

         }


        msg += "\n=================================================="
                "====================\n";
        if ( this_player()->query("mirror_count") )
        {
           msg +=   HIY"���ۼ������" +  HIR +
                    chinese_number(this_player()->query("mirror_count")) + NOR
                    + HIY"����������\n"NOR;
        }

        tell_object(this_player(), msg + "\n");
        return 1;
     }

}
string long()
{
        return query("power") ? query("long") + HIW"���ڱ���������Ϊ��" +
        query("power") + "\n"NOR: query("long") + HIR"���ڱ����������Ѿ�"
        "�ľ��ˡ�\n"NOR;
}
                

