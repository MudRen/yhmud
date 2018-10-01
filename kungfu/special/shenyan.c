#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

#define HP_CMD              "/cmds/usr/hp"
#define SKILLS_CMD              "/cmds/skill/skills"

int is_scborn() { return 1; }

string name() { return HIC "ͨ������" NOR; }

int perform(object me, string skill, string arg)
{
        //int i;
      
        object ob;

        if (me->query("neili") < 500)
        	  return notify_fail("���������㣬�޷�����ͨ�����ۣ�\n");

        if (me->is_busy()) 
        	  return notify_fail("����æ����˵�ɣ�\n");
	        
        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("����û������ˣ���������ĸ�ʽ�д���\n"
                                   "��ʽ �� special shenyan <����id> \n");

	if (ob->query_temp("apply/invisible"))
                return notify_fail("����û������ˣ���������ĸ�ʽ�д���\n"
                                   "��ʽ �� special shenyan <����id> \n");
                                   		
        write(HIW "��ʩչ��ͨ������֮�� ����\n" NOR, me);
	
        me->add("neili", -400);
        me->start_busy(2);

        HP_CMD->main(me, arg, 1);
        SKILLS_CMD->main(me, arg, 1);

        return 1;
}
