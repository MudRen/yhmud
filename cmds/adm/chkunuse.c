#define unusedvar_log_file "/log/unused.var"

string file, *f_line, new_f_line, chk, unusedvar;
string wfile, *wf_line, lastw;
string filename, argv_name, c1, c2;

int start, line_n;
    
int check(int s);
int clean(string line);
int isdata(string s);//����һ�м򵥷���,�ж��Ƿ������ݶ�����
int peidui(string s);//����һ�м򵥷���,�ж�([{}])�Ƿ��ȱ

int main(object me, string arg)
{    
    string *founded;//�Ѿ����ֹ��Ĵ���

    unusedvar = "";
    new_f_line = "";

    if ( !arg )
    {
        arg = "/log/log";
    }

    if ( file_size(arg) == -1 ) 
    {
        write(arg + "�ļ������ڡ�\n");
        return 1;
    }    

    if ( !(file = read_file(arg)) || sizeof(file) == 0 )
    {
        write("�޷���ȡ���ļ���" + arg + "\n");
        return 1;
    }

    unusedvar += file + "\n";
    f_line = explode(file, "\n");
    write_file(arg, "", 1);
    founded = ({});
    lastw = "";//��һ�������ļ���

    foreach (chk in f_line) //chk log file each line
    {
        if ( sscanf(chk, "%s line %d: Warning: Unused local variable '%s'", filename, line_n, argv_name) == 3 )
        {
            if ( member_array(chk, founded) != -1 )
            {
                continue;//this mistake have be treated 
            }

            founded += ({chk});
            if ( lastw != filename )//���ļ��д�
            {
                if ( lastw != "" )
                {
                    write_file(lastw, implode(wf_line, "\n"), 1);    //�ȱ����޸����ļ�
                    unusedvar += "----write_file name==" + lastw + " end.....\n\n";                    
                }

                lastw = filename;

                if ( !(wfile = read_file(filename)) )//�ٶ����ļ�
                {
                    write("�޷���ȡ���ļ���" + filename + "\n");
                    return 1;
                }

                wf_line = explode(wfile, "\n");    //wrong file lines
            }

            //��������޸ĸղŵ��ļ��������ظ����޸Ĵ���ͬһ�ļ�
            unusedvar += "��" + filename + " @line=" + line_n + ", Unused variable=" + argv_name + "\n"; 

            if ( line_n >= sizeof(wf_line) )
            {
                line_n = sizeof(wf_line) - 1; // ��Щ�ļ�����������,\n��ϻ���һ����
            }

            while ( line_n >= 0 ) 
            {    
                if ( isdata(wf_line[line_n]) )
                {
                    //write("line_n number=="+(line_n+1)+"    argv_name is "+argv_name +"\n");
                    start = 0;

                    if ( check(start) ) //�ҵ����޸ĳɹ�
                    {
                        break;
                    }
                }    

                line_n--;
            }
        }
        else
        {
            new_f_line = new_f_line + chk + "\n";
        }
    }

    if ( lastw != "" )
    {
        write_file(lastw, implode(wf_line, "\n"), 1);
    }

    if ( lastw != "" )
    {
        unusedvar += "-----------write file name==" + lastw + " end.....\n";
    }
    else
    {
        unusedvar += "\n-----------no file found Unused local variable. end.....\n";
    }

    write_file(unusedvar_log_file, unusedvar, 1);
    write_file(arg, new_f_line);//����ʶ��д��ԭlog�ļ�
    write("ok.check /log/unused.var for examination��\n");
    return 1; 
}

int isdata(string s)//����һ�м򵥷���,�ж��Ƿ������ݶ�����
{
    string chk,
        *leixing = ({"int","string","object","mapping","mixed","float","buffer"});//class,array �����У������˲��ÿ����Լ�С
    int n;

    foreach (chk in leixing)
    {
        if ( (n = strsrch(s, chk)) != -1 ) 
        {
            if ( n!=0 && s[n-1] != ' ' && s[n-1] != '\t' && s[n-1] != ';' ) // ��������ǰ���ܵ��ǿհװ�
            {
                return 0;
            }

            n += sizeof(chk);
            if ( s[n] == ' ' || s[n] == '*' || s[n] == '/' || s[n] == '\t' ) //��Щ���������������ͺ����*����ĳЩ�����Ѿ�ע�������޷�ȷʵ��������
            {
                return 1;
            }
        }
    }

    return 0;
}

int check(int s)//����һ����ϸ����
{    
    int temp; //��¼�����ַ���λ�ã���������ԣ���ֹ���˿�ʼ�������ʱ���к������ø��ӵĶ������ʼ��

    start = s;   

    if ( (temp = strsrch(wf_line[line_n][s..], argv_name)) != -1 ) //���ǰ���ַ������Ƿ����������
    {
        start += temp;//��ʼλ��        

        c1 = wf_line[line_n][start - 1 .. start - 1];
        //write("111argv_name is "+argv_name +" c1 is "+c1+"\n");

        if ( member_array(c1, ({" ", ",", "*", "/", "\t"})) == -1 )
        {
            return check(start + sizeof(argv_name));//ǰ�治�ǿո�򶺺Ż��Ǻţ�Ӧ�ò��Ǳ�����������������������
        }
        //write("111\n");

        c2 = wf_line[line_n][start + sizeof(argv_name) .. start + sizeof(argv_name)];

        if ( member_array(c2, ({" ", ",", ";", "=", "/", "\t"})) == -1 )//���治�ǿո�򶺺Ż�ֺţ�Ӧ�ò��Ǳ�����������������������
        {
            return check(start + sizeof(argv_name));
        }

        while ( member_array(c1, ({" ", ",", "*", "/", "\t"})) != -1 )
        {
            //write("left argv_name is "+argv_name +" c1 is "+c1+"\n");
            if ( c1 == "/" )
            {
                break;
            }
            argv_name = c1 + argv_name;
            start--; 
            c1 = wf_line[line_n][start - 1 .. start - 1];
        }

        while ( 1 )
        {
            if ( peidui(argv_name) == 1 ) 
            {
                //write("right argv_name is "+argv_name +" c2 is "+c2+"\n");
                if ( c2 == ";" || c2 == "/" || c2 == "," )  //һ��Ҫ����
                {
                    if ( strsrch(argv_name, ",") == -1 )//û�ж��ţ�˵���ǵ�һ����������Ҫ��������ģ�
                    {
                        if ( c2 == "," )
                        {
                            argv_name = argv_name + c2;
                        }
                    }

                    break;
                }
            }

            argv_name = argv_name + c2;
            c2 = wf_line[line_n][start + sizeof(argv_name) .. start + sizeof(argv_name)];
        }

        if ( argv_name[0..1] == "* " || argv_name[0..1] == "*\t" )
        {
            argv_name = argv_name[1..];//��ֹ���˰�*д�����ͺ����ϰ��
        }

        if ( argv_name[0..0] == " " || argv_name[0..0] == "\t" )
        {
            argv_name = argv_name[1..];//��ֹ���е�ע�Ͱ�/*д�����ͺ���,�����޷�ʶ������
        }

        unusedvar += "��the wrong is " + "@line" + (line_n + 1) + "��" + wf_line[line_n] + "��\n";
        wf_line[line_n] = wf_line[line_n][0..start - 1] + replace_string(wf_line[line_n][start..], argv_name, "/*" + argv_name + "*/", 1);//ע�͵�����
        clean(wf_line[line_n]);

        return 1;
    }

    return 0;
}

int clean(string line)  //clean so much *//* together,and type name alone
{
    string f, s1, s2, *fs;

    f = line + "";
    f = replace_string(f, "*//*", "");//clean so much *//* together,
    f = replace_string(f, "\t", " ");

    while ( sscanf(f, "%s/*%*s*/%s", s1, s2) == 3 )
    {
        f = s1 + " " + s2;
    }

    sscanf(f, "%s//%*s", f);
    fs = explode(f, " ");    
    fs -= ({"", ";", "{"});

    wf_line[line_n] = replace_string(wf_line[line_n], "*//*", "");

    if ( sizeof(fs) < 2 )
    {
        wf_line[line_n] = replace_string(wf_line[line_n], "/*", "");
        wf_line[line_n] = replace_string(wf_line[line_n], "*/", "");
        wf_line[line_n] = replace_string(wf_line[line_n], " ;", ";");

        if ( strsrch(wf_line[line_n], "{") != -1 )
        {
            wf_line[line_n]= replace_string(wf_line[line_n], "{", "{ //", 1);
        }
        else
        {
            wf_line[line_n] = "//" + wf_line[line_n];
        }

        wf_line[line_n] = replace_string(wf_line[line_n], "//  ", "//");        
    }

    unusedvar += "��the corrected line" + (line_n + 1) + "��" + wf_line[line_n] + "��\n";
}

int peidui(string arg)//from nt7,����һ�м򵥷���,�ж�([{}])�Ƿ��ȱ
{
    int idx, chr, mark, marked;
    int s_symbol, m_symbol, b_symbol, d_quote, s_quote;

    idx = 0;
    chr = 0;
    mark = 0;
    marked = 0;
    s_symbol = 0;
    m_symbol = 0;
    b_symbol = 0;
    d_quote = 0;
    s_quote = 0;

    for ( idx = 0; idx < strlen(arg); idx++ )
    {
        chr = arg[idx];
        mark = (chr == '\\');

        if ( mark ) marked++;
        if ( !(s_quote%2) && (!marked || !(marked%2)) && chr == '\"' ) d_quote++;
        if ( !(d_quote%2) && (!marked || !(marked%2)) && chr == '\'' ) s_quote++;
        if ( !mark ) marked = 0;
        if ( d_quote%2 ) continue;

        switch(chr)
        {
            case '(':
                s_symbol++;
                break;

            case ')':
                s_symbol--;
                break;

            case '[':
                m_symbol++;
                break;

            case ']':
                m_symbol--;
                break;

            case '{':
                b_symbol++;
                break;

            case '}':
                b_symbol--;
                break; 

            default:
                break;
        }
    }

    if ( d_quote%2 || s_quote%2 || s_symbol || m_symbol || b_symbol )
    {
        return 0;
    }

    return 1;
}

int help (object me)
{
    write(@HELP
    �Զ�ע�͵�Դ�ļ�������mudos��fluffos���ֵ�δʹ�õı�����
�Խ�Լ�ڴ棬ע�ͺ���ļ���¼���log�ļ���ɾ�����Լ�Сlog��
������������ʶ�Ĵ����д��ԭlog�ļ�.�Է�����ʦ���
    �Ѿ�ע�͵��ļ����һ����¼��Ĭ���ļ���Ϊ/log/unused.var
ǰ����log�ļ������������޸�������������ʼ���γ����з��
���Ʊ�����Է����ж��Ƿ�ע����ȷ��
        
ָ���ʽ��chkunuse [logfile]
û�� logfile����logfileĬ��Ϊ log/log 
HELP
    );

    return 1;
}

