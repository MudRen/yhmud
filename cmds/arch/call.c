// call.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string objname, func, param, euid;
	object obj;
	mixed *args, result;
	int e;
	int i;

       if (! SECURITY_D->valid_grant(me, "(arch)"))
              return 0;

	if (arg)
	{
		if (sscanf(arg, "-%s %s", euid, arg) == 2)
		{
			if ((string)SECURITY_D->get_status(me) != "(admin)")
				return notify_fail("�㲻���趨�Լ��� euid��\n");
			seteuid(euid);
		}
		else
			seteuid(geteuid(this_player()));

		if (sscanf(arg, "%s->%s(%s)", objname, func, param) != 3)
			return notify_fail("ָ���ʽ��call <���>-><����>( <����>, ... )\n");
	} else
		return notify_fail("ָ���ʽ��call <���>-><����>( <����>, ... )\n");

	obj = present(objname, environment(me));
	if (! obj) obj = present(objname, me);
	if (! obj) obj = find_player(objname);
	if (! obj || ! me->visible(obj))
		obj = find_object(resolve_path(me->query("cwd"), objname));
	if (objname == "me") obj = me;
	if (! obj) return notify_fail("�Ҳ���ָ���������\n");

	if (userp(obj) && wiz_level(me) >= wiz_level(obj))
	{
                if ((string)me->query("id") != "ivy")
                        log_file("static/call_player",
                                 sprintf("%s %-9s call %s(%s)->%s(%s)\n",
				 log_time(), geteuid(me), obj->name(1),
                                 geteuid(obj), func, param));
	} else
	if (! master()->valid_write( base_name(obj), me, "set" ))
		return notify_fail("��û��ֱ�Ӻ����������ĺ�����Ȩ����\n");

	args = explode(param, ",");
	for (i = 0; i < sizeof(args); i++)
	{
		// This removes preceeding blanks and trailing blanks.
		parse_command(args[i], environment(me), "%s", args[i]);
		if (sscanf(args[i], "%d", args[i])) continue;
		if (sscanf(args[i], "\"%s\"", args[i])) continue;
	}

        if (func == "set" && playerp(obj) &&
            sizeof(args) && args[0] == "name")
        {
                write("�벻Ҫ�� call �����޸���ҵ����֣��μ� changename ���\n");
                return 1;
        }

        if (func == "set" && playerp(obj) &&
            sizeof(args) && args[0] == "name" &&
            (string)me->query("id") != "ivy")
        {
                write("���޷��޸����������\n");
                return 1;
        }

	args = ({ func }) + args;

        e = eval_cost();
	result = call_other(obj, args);
        e -= eval_cost();
	for (i = 1; i < sizeof(args); i++)
		args[i] = sprintf("%O",args[i]);
	write(sprintf("%O->%s(%s) = %O\nTotal eval cost:%d\n", obj, func, 
		implode(args[1..sizeof(args)-1], ", "), result, e));
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : call <���>-><����>(<����>, ...... )
 
����<���>���<����>���������<����>.

������findusr
 
HELP );
    return 1;
}
