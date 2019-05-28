// analectad.c
// Create by jjgod for hell. 2002/01/27.

// #pragma optimize
// #pragma save_binary

#include <ansi.h>

#define ANALECTA_DIR    DATA_DIR + "analecta/"
#define HEAD_LINES      8

inherit F_DBASE;

mapping analecta_list;                                  // ��ѡ�б�

private void    collect_all_analecta();                         // �ռ�������ѡ��Ϣ
private mapping parse_analecta(string file_name);               // ������ѡͷ��Ϣ
public  mapping query_analecta_list();                          // ��ѯ��ѡ�б�
public  int     add_analecta(int year, mapping analecta);       // ���һƪ��ѡ
public  int     delete_analecta(int year, int number);          // ɾ��һƪ��ѡ

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "��ѡ����");
        CHANNEL_D->do_channel(this_object(), "sys", "��ѡϵͳ�Ѿ�������");

        analecta_list = ([ ]);
        collect_all_analecta();
}

// ��ѯ��ѡ�б�
mapping query_analecta_list()
{
        return analecta_list;
}

// ANALECTA_D �����ռ����е���ѡ
void collect_all_analecta()
{
        string year, dir, file;
        string *analecta_year, *files;

        CHANNEL_D->do_channel(this_object(), "sys", "�����ռ���ѡ��Ϣ��");

        analecta_year = get_dir(ANALECTA_DIR);

        if (! arrayp(analecta_year) || ! sizeof(analecta_year))
        {
                CHANNEL_D->do_channel(this_object(), "sys", "���κ���ѡ��Ϣ��");
                return;
        }

        foreach (year in analecta_year)
        {
                dir = ANALECTA_DIR + year + "/";

                if (file_size(dir) != -2)
                        continue;

                analecta_list[year] = ({ });
                files = get_dir(dir);

                if (! arrayp(files) || ! sizeof(files))
                        continue;

                foreach(file in files)
                {
                        if (file_size(dir + file) <= 0)
                                continue;
                        analecta_list[year] += ({ parse_analecta(dir + file) });
                }
        }
        CHANNEL_D->do_channel(this_object(), "sys", "��ѡ��Ϣ�ռ���ɡ�");
}

// ������ѡͷ��Ϣ

// ��ʽʾ����
// subject : ������ѡ                      -> ��ѡ����
// author_name : ����                      -> ��ѡ����
// author_id : jjgod                       -> ��ѡ����ID
// time : 1012137565                       -> ����ʱ��
// board : �͵����԰�                      -> ����ص�
// file : /data/analecta/2002/10000000.txt -> �����ļ�
// add_time : 1012137565                   -> ���ʱ��
// content :
// ���������ݡ�                            -> ��ѡ����
mapping parse_analecta(string file_name)
{
        mapping data;
        int len, start, i, n;
        string info;
        string *lines;
        mixed sub_info;

        info = read_file(file_name, 1, HEAD_LINES);
        if (! stringp(info))
                return ([ ]);

        info = replace_string(info, "\r", "");
        lines = explode(info, "\n");

        data = ([ "subject"     : "����",
                  "author_name" : "����",
                  "author_id"   : "NULL_ID",
                  "time"        : 0,
                  "board"       : "δ֪���԰�",
                  "file"        : "δ֪�ļ�",
                  "add_time"    : 0,
                  "lines"       : 0, ]);

        n = sizeof(lines);
        for (i = 0; i < n; i++)
        {
                // �ֳ� '��Ŀ ' �� ' ����' ������
                sub_info = explode(lines[i], ":");

                // ���޷�����
                if (sizeof(sub_info) < 2)
                        sub_info += ({ "" });

                // ȥ����Ŀ��ǰ��Ŀո�
                len = strlen(sub_info[0]);
                start = 0;

                while (start < len && sub_info[0][start] == ' ')
                        start++;
                while (len-- && sub_info[0][len] == ' ');

                sub_info[0] = sub_info[0][start..len];

                // ȥ����Ŀ����ǰ��Ŀո�
                if (sizeof(sub_info) > 1)
                {
                        len = strlen(sub_info[1]);
                        start = 0;

                        while (start < len && sub_info[1][start] == ' ')
                                start++;
                        while (len-- && sub_info[1][len] == ' ');

                        sub_info[1] = sub_info[1][start..len];
                }

                // �����п�ʼΪ�������ݣ���ֹͣ����
                if (sub_info[0] == "content")
                        break;
                else
                {
                        if (undefinedp(data[sub_info[0]]))
                                continue;
                        // ����������ӦΪ����
                        if (intp(data[sub_info[0]]))
                                sub_info = ({ sub_info[0], atoi(sub_info[1]) });
                        // �����ʵ����Ϣ�滻��ȱʡ����Ϣ
                        data[sub_info[0]] = sub_info[1];
                }
        }

        data["file"] = file_name;
        data["lines"] = file_lines(file_name);
        return data;
}

// ���һƪ��ѡ����һ�����λ����Ϊ�ļ���
int add_analecta(int year, mapping analecta)
{
        int i;
        string file, info;
        int add_time;
        
        i = random(99999999 - 10000000 + 1) + 10000000;
        file = ANALECTA_DIR + year + "/" + i + ".txt";

        assure_file(file);
        if (file_size(file) > 0)
                return add_analecta(year, analecta);

        add_time = time();
        info = sprintf("subject : %s\n"
                       "author_name : %s\n"
                       "author_id : %s\n"
                       "time : %d\n"
                       "board : %s\n"
                       "file : %s\n"
                       "add_time : %d\n"
                       "content :\n%s",
                       analecta["subject"], analecta["author_name"], 
                       analecta["author_id"], analecta["time"],
                       analecta["board"], file,
                       add_time, analecta["content"]);

        analecta["file"] = file;
        analecta["add_time"] = add_time;
        
        write_file(file, info, 1);
        if (undefinedp(analecta_list[sprintf("%d", year)]))
                analecta_list[sprintf("%d", year)] = ({ analecta });
        else analecta_list[sprintf("%d", year)] += ({ analecta });
        return 1;
}

// ɾ��һƪ��ѡ
int delete_analecta(int year, int number)
{
        mapping *analecta;

        if (! arrayp(analecta = analecta_list[sprintf("%d", year)]) ||
            ! sizeof(analecta))
                return 0;

        if (sizeof(analecta) < number)
                return 0;

        if (number < 1)
                return 0;

        number--;
        rm(analecta[number]["file"]);

        if (number == 0)
                analecta = ({ });

        analecta = analecta[0..number - 1] + analecta[number + 1..<1];
        analecta_list[sprintf("%d", year)] = analecta;

        return 1;
}

// ���һ�����ѡ�б�
int clear_analecta_list(int year)
{
        if (undefinedp(analecta_list[sprintf("%d", year)]))
                return 0;
                
        map_delete(analecta_list, sprintf("%d", year));
        return 1;
}
