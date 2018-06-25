// checkskill.c
// Created by smallfish.
// Updated by jjgod. 2002/11/30.
// Updated by Lonely

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
        "medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
        "cooking",
});

// ��ѯ���ܵ�����

// ����������д˼��ܵĺ��������뷵��һ���� 0 �Ľ��
// �Ż����������Ӧ����������Ľ����

// $N ��ʾ�����ѯ����� $C ��ʾ�����ѯ��������ģ�
// $S ��ʾ�Ű��Ĳ�ѯ�����
mapping skill_features = ([
        "type"              : "$C����",
        "double_attack"     : "���ٹ���",
        "main_skill"        : "������Ϊ$C",
        "query_description" : "$S",
]);

// ������Ϊ�˰�˳����ʾ
string *features = ({ "type", "double_attack", "main_skill", "query_description",  });

// ��ͷ�����ݣ�Ϊ�˱��ֶ�����趨
#define PREFIX_STR      "\t      "
// ÿ�еĳ���
#define LINE_LEN        40
// ��ʾ�ϲ�ʹ�õ��ַ�
#define COMBINE_STR     "��"
// ��ʾ����ʹ�õ��ַ�
#define APPOSE_STR      " - "
// ˮƽ��
#define HORIZONTAL_STR  HIC "����������������������������"\
                        "������������������������������\n" NOR

string sort_result(string str, int prefix);
string skill_combines(object sk);
string skill_enables(object sk);

mapping valid_type = ([
        "unarmed":      "ȭ��", "medical":      "ҽ��",
        "claw":         "צ��", "cuff":         "ȭ��",
        "finger":       "ָ��", "strike":       "�ƹ�",
        "hand":         "�ֹ�", "leg":          "�ȹ�",
        "sword":        "����", "blade":        "����",
        "dagger":       "�̱�", "brush":        "�ʷ�",
        "spear":        "ǹ��", "hook":         "����",
        "stick":        "����", "staff":        "�ȷ�",
        "club" :        "����", "throwing":     "����",
        "whip":         "�޷�", "axe":          "����",
        "hammer":       "����", "force":        "�ڹ�",
        "dodge":        "�Ṧ", "parry":        "�м�",
        "poison":       "����", "cooking":      "����",
        "chuixiao-jifa":"����", "guzheng-jifa": "����",
        "tanqin-jifa":  "����",
]);

int main(object me, string arg)
{
        string  file, dir, filename;
        string  msg, msg1;
        //string  type;
        int     i, l, is_force, prefix;
        int     perform, exert;
        mixed   *all_file;
        string  *sub_skills, sub_skill;
        string  feature, temp, *feature_list;
        mixed   value;
        mapping sub_skill_list;
        object  sk;
        string  enable, combo;

        seteuid(getuid());

        if (! arg)
                return notify_fail("ָ���ʽ��checkskill <��������> | <����������>\n");

        if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
        {
                // Ӣ�ĵ��Ҳ������Ǿ���������
                if (! stringp(arg = CHINESE_D->find_skill(arg)))
                        return notify_fail("û�����ּ��ܴ��ڡ�\n");

                write("Original: " + arg + "\n");
                // �����������ҵ���Ӣ�����������Ƿ�����д˼���
                if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
                        return notify_fail("û�����ּ��ܴ��ڡ�\n");
        }

        msg = WHT + to_chinese(arg) + "(" + arg + ")����ϸ�������£�\n" NOR;
        msg += HORIZONTAL_STR;
        msg += CYN + "  �������ƣ�  " WHT + to_chinese(arg) + "(" + arg + ")\n" + NOR;

        is_force = 0;

        if (SKILL_D(arg)->valid_enable("force"))
                is_force = 1;

        // ��ȡ���������б�
        feature_list = ({ });
        foreach (feature in features)
        {
                if (value = call_other(SKILL_D(arg), feature))
                {
                        temp = skill_features[feature];

                        if (stringp(value))
                        {
                                temp = replace_string(temp, "$N", value);
                                temp = replace_string(temp, "$C", to_chinese(value));

                                if (strsrch(temp, "$S") != -1)
                                {
                                        prefix = strlen(implode(feature_list, COMBINE_STR)) +
                                                 strlen(COMBINE_STR);
                                        // ��ȡÿ�е�����
                                        prefix %= LINE_LEN;
                                        temp = replace_string(temp, "$S",
                                                              sort_result((string)value, prefix));
                                }
                        }
                        feature_list += ({ temp });
                }
        }

        if (sizeof(feature_list))
                msg += CYN "\n  �������ԣ�  " WHT + implode(feature_list, COMBINE_STR) +
                       "\n" NOR;

        sk = get_object(SKILL_D(arg));

        combo = skill_combines(sk);

        if (combo != "")
        {
                msg += CYN "\n  ���ܻ�����  " WHT + combo + "\n" NOR;
        }

        enable = skill_enables(sk);

        if (enable != "")
        {
                msg += CYN "\n  ���⼼�ܣ�  " WHT + enable + "\n" NOR;
        }

        if (member_array(arg, valid_types) != -1)
        {
                msg += CYN "\n  ����������  " WHT "��������\n" NOR;
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }

        /*
        // ��ʱ������Ҳ��ܲ鿴�Լ�û�е��书�ľ���
        if (! wizardp(me) && me->query_skill(arg) <= 0)
        {
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }
        */

        sub_skill_list = SKILL_D(arg)->query_sub_skills();
        if (mapp(sub_skill_list) && sizeof(sub_skill_list))
        {
                sub_skills = keys(sub_skill_list);
                msg += CYN "\n  ���ܺϳɣ�  " WHT;
                foreach (sub_skill in sub_skills)
                {
                        if (file_size(SKILL_D(sub_skill) + ".c") <= 0)
                                continue;

                        msg += to_chinese(sub_skill) + "(" +
                               sub_skill + ")\n" + PREFIX_STR;
                }
                msg += NOR;
        }

        // ��ѯ���ܵ� pfm ���
        msg1 = "";
        perform = 0;
        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (is_force)
                dir += "perform/";

        if (file_size(dir) != -2)
                msg1 += "";
        else
        {
                all_file = get_dir(dir);
                if (! sizeof(all_file))
                        msg1 += "";
                else
                {
                        for (i = 0; i < sizeof(all_file); i++)
                        {
                                if (i == 7) msg1 += "\n\t   ";
                                else if (i > 7 && i % 7 == 0)
                                        msg1 += "\n\t   ";

                                filename = all_file[i];
                                l = strlen(filename);
                                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                                {
                                        perform++;
                                        msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
                                        msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
                                }
                        }

                        if (msg1 != "")
                        {
                                msg += CYN "\n  ���ܾ��У�  " NOR;
                                msg += msg1;
                                msg += "\n";
                        }
                }
        }

        // ��ѯ�ڹ��� exert ���
        if (! is_force)
        {
                msg += HORIZONTAL_STR;
                if (perform) msg += WHT "����" + chinese_number(perform) + "����С�\n" NOR;
                write(msg);
                return 1;
        }

        msg1 = "";
        exert = 0;
        dir = file;

        if (dir[strlen(dir) - 1] != '/')
                dir += "/";

        if (file_size(dir + "exert/") == -2)
                all_file = get_dir(dir + "exert/");
        else
        if (file_size(dir) == -2)
                all_file = get_dir(dir);
        else
        {
                msg += HORIZONTAL_STR;
                write(msg);
                return 1;
        }

        if (! sizeof(all_file))
        {
                write(msg);
                return 1;
        }

        for (i = 0; i < sizeof(all_file); i++)
        {
                filename = all_file[i];
                l = strlen(filename);
                if (filename[l - 1] == 'c' && filename[l - 2] == '.')
                {
                        exert++;
                        msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
                        msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
                }
        }

        if (msg1 != "")
        {
                msg += CYN "\n  �ڹ����ܣ�  " NOR;
                msg += msg1;
                msg += "\n";
        }

        msg += HORIZONTAL_STR;

        if (perform)
        {
                msg += WHT "����" + chinese_number(perform) + "��ܾ���";
                if (exert)
                        msg += "��" + chinese_number(exert) + "���ڹ����ܡ�\n" NOR;
                else msg += "��\n" NOR;
        } else
        if (exert)
                msg += WHT "����" + chinese_number(exert) + "���ڹ����ܡ�\n" NOR;

        write(msg);
        return 1;
}

string skill_combines(object sk)
{
        int i, j;
        string str, *skills;
        mapping skill;

        skill = this_player()->query_skills();
        if (! mapp(skill) || sizeof(skill) < 1)
                return "";

        skills = keys(skill);

        for (i = 0; i < sizeof(skills); i++)
        {
                if (sk->valid_combine(skills[i]))
                        continue;

                skills[i] = 0;
        }

        skills -= ({ 0 });
        j = sizeof(skills);

        if (! j || j < 1)
                return "";

        str = "";
        for (i = 0; i < j; i++)
        {
                if (i == 2) str += "\n\t      ";
                else if (i > 2 && i % 2 == 0)
                        str += "\n\t      ";

                str += sprintf("%-14s ", CHINESE_D->chinese(skills[i]) + "(" + skills[i] + ")");

                /*
                if (i < j -1)
                        str += "- ";
                */
        }

        return str;
}

string skill_enables(object sk)
{
        int i, j;
        string str, *skills;

        skills = keys(valid_type);

        for (i = 0; i < sizeof(skills); i++)
        {
                if (sk->valid_enable(skills[i]))
                        continue;

                skills[i] = 0;
        }

        skills -= ({ 0 });
        j = sizeof(skills);

        if (! j || j < 1)
                return "";

        str = "";
        for (i = 0; i < j; i++)
        {
                if (i == 3) str += "\n\t      ";
                else if (i > 3 && i % 3 == 0)
                        str += "\n\t      ";

                str += sprintf("%-14s ", valid_type[skills[i]] + "(" + skills[i] + ")");

                /*
                if (i < j -1)
                        str += "- ";
                */
        }

        return str;
}

string sort_result(string str, int prefix)
{
        string *str_list;

        str = replace_string(str, "\r", "");
        str = replace_string(str, "\n\n", "$EOP");
        str = replace_string(str, "\n", "");
        str = replace_string(str, "$EOP$", "\n\n");

        str = sort_string(str, LINE_LEN, prefix);

        str_list = explode(str, "\n");
        str = implode(str_list, "\n" + PREFIX_STR);

        return str;
}

string input_file(string file)
{
        if (! previous_object() ||
            geteuid(previous_object()) != "Kungfu")
                return 0;

        return read_file(file);
}

int help(object me)
{
        write(@HELP
ָ���ʽ��skill|checkskill <��������> | <����������>

���ָ��������ָ����ĳ�ּ��ܻ��ܣ��������ƿ�������
�����������������ʦ�����߱���߱�����ܣ������ʾ��
�ü��ܵľ��м���Ϊ�ڹ������⹦�ܡ�ͬʱ���㻹���Բ鵽��
����ص�һЩ���ԣ����缼�ܵ����͡��Ƿ�˫�������ٶȡ���
������ʲô�ȵȣ�����������ڶ�������ص������Ļ����㻹
���Բ鵽����������ܵ�һЩ�ƹʡ�

���⣬������������һ���ɱ������ϲ��ļ��ܣ��������ʾ
��������Щ����������������

���ָ�skills

HELP);
        return 1;
}

