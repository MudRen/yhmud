// animaout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int outing(object me);
int halt_outing(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        int exercise_cost;
        object where;

        seteuid(getuid());
        where = environment(me);

       // if( !query("animaout", me) )
       if(! me->query("animaout"))
                return notify_fail("�㻹û������ԪӤ������̸ʲô�������أ�\n");

       // if( query("death", me) )
       if (me->query("death"))
                return notify_fail("���Ѿ���ͨ���������ˣ�û�б�Ҫ����һ�飡\n");

       // if( !query("no_fight", where) )
       if (! where->query("no_fight"))
                return notify_fail("�������ͨ�������أ���̫��ȫ�ɣ�\n");

       // if( !query("sleep_room", where) )
       if (! where->query("sleep_room"))
                return notify_fail("�����һ���ܹ���Ϣ�ĵط��չ����С�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

       // if( query("potential", me)-query("learned_points", me)<1000 )
       if (me->query("potential") - me->query("learned_points") < 1000)
                return notify_fail("���Ǳ�ܲ�����û���չ������Դ�ͨ�������ء�\n");

       // if( query("qi", me)*100/query("max_qi", me)<90 )
       if ((int)me->query("qi") * 100 / me->query("max_qi") < 90)
                return notify_fail("�����ڵ���̫���ˣ��޷����ıչء�\n");

      //  if( query("jing", me)*100/query("max_jing", me)<90 )
      if ((int)me->query("jing") * 100 / me->query("max_jing") < 90)
                return notify_fail("�����ڵľ�̫���ˣ��޷����ıչء�\n");

      //  if( query("max_jingli", me)<2000 )
      if ((int)me->query("max_jingli") < 2000)
                return notify_fail("����þ������в��㣬����Ŀǰ������"
                                   "��ͨ�������ء�\n");

      //  if( query("jingli", me)*100/query("max_jingli", me)<90 )
      if ((int)me->query("jingli") * 100 / me->query("max_jingli") < 90)
                return notify_fail("�����ڵľ���̫���ˣ��޷����ıչء�\n");

        message_vision("$N��ϥ���£���ʼڤ���˹����չ����С�\n", me);
       // set("startroom", base_name(where), me);
       // set("doing", "death", me);
       me->set("startroom", base_name(where));
        me->set("doing", "death");
        CLOSE_D->user_closed(me);
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("%s%s(%s)��ʼ�չ����У���ͼ��ͨ�������ء�",
                              ultrap(me) ? "����ʦ" : "",
                              me->name(1),me->query("id")));

        return 1;
}

int continue_outing(object me)
{
        me->start_busy(bind((:call_other, __FILE__, "outing" :), me),
                       bind((:call_other, __FILE__, "halt_outing" :), me));
        CLOSE_D->user_closed(me);
        tell_object(me, HIR "\n������չ�������ͼ��ͨ��������...\n" NOR);
        return 1;
}

private void stop_outing(object me)
{
        CLOSE_D->user_opened(me);
        if (! interactive(me))
        {
                me->force_me("chat* sigh");
                call_out("user_quit", 0, me);
        }
}

int outing(object me)
{
        string msg;

      //  if( query("potential", me) <= query("learned_points", me) )
      if (me->query("potential") <= me->query("learned_points"))
        {
                tell_object(me, "��û�а취������ȥ�ˡ�\n");
                message_vision("$N����˫Ŀ����������һ������վ��������\n", me);
                CLOSE_D->user_opened(me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�չؽ������ƺ�û��ʲô�ɹ���",
                                      me->name(1),me->query("id")));
                if (! interactive(me))
                {
                        me->force_me("chat* sigh");
                        call_out("user_quit", 0, me);
                }

                return 0;
        }

        //addn("learned_points", 1, me);
        me->add("learned_points", 1);

        if (random(10))
                return 1;

        //if( random(100000)<query("con", me) )
        if (random(40000) < me->query("int"))
        {
                message_vision(HIY "ֻ��$N" HIY "ͷ���ֳ�����������"
                               "�����䣬һʱ�������˱ǡ��뵱�أ�\n" NOR, me);
                tell_object(me, HIM "����þ���ԴԴ��������Ȼ����ֹˮ�������"
                            "��ʣ���Դ�޾�����ʱ�󳹴���\n" NOR);

               // set("death", 1, me);
               me->set("death", 1);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      sprintf("��˵%s(%s)�����չؿ��ޣ���"
                                      "�ڲ��������֮������ͨ���������ء�",
                                      me->name(1),me->query("id")));

                CHAR_D->setup_char(me);
                stop_outing(me);
                return 0;
        }

        switch (random(4))
        {
        case 0:
                msg = "���Ŀ������ͼ�������Ҿ��硣\n";
                break;

        case 1:
                msg = "����ͼ��Ԫ����֫����룬Ȼ���������֮����\n";
                break;

        case 2:
                msg = "����ͼ��Ԫ��Ƴ����ϣ�Ȼ�������Ĵ������ջء�\n";
                break;

        default:
                msg = "�㻺���������ɣ���������ˮ¶����Ϊ���á�\n";
                break;
        }

        tell_object(me, msg);
        return 1;
}

int halt_outing(object me)
{
        CLOSE_D->user_opened(me);
        tell_object(me, "����ֹ�˱չء�\n");
        message_vision(HIY "$N" HIY "����̾��һ�����������������ۡ�\n\n" NOR, me);
       // addn("potential", (query("learned_points", me)-query("potential", me))/2, me);
       me->add("potential", (me->query("learned_points") - me->query("potential")) / 2);
        CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + me->name(1) +
                              "�չ���;ͻȻ������");
        return 1;
}

private void user_quit(object me)
{
        if (! me || interactive(me))
                return;

        me->force_me("quit");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : death

��������ԪӤ�����Ժ󣬲��Ҿ��зǳ�����ľ�����Ϊʱ��������
����ָ���ͨ�������ء���ͨ�������غ����ʹ���������м��ʲ�
��ʧ�书���ܡ�

HELP );
        return 1;
}