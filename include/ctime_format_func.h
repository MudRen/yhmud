// naihe 05-8-16 13:18
//    �Դ� 2003-04-29 ʹ�� ctime_new() ����������һֱ������Щ��ˬ
//    ����ĳ��µķ�ʽ�����ݾɵģ��µĸ��ã�
#include "localtime.h"
#define        LT_MON_ADD            1        // ��ЩOS�������BUG��û�а� LT_MON ��һ����������һ��
#define        DEFAULT_FORMAT_STR    "YY.M.D(w) h:m:s"  // Ĭ�ϱ�׼������ʽ

string ctime_format_help()
{
    string msg;
    msg = "\n"
    + "varargs string ctime_format( mixed arg1, mixed arg2 ) ������\n"
    + "----------------------------------------------------------------------\n"
    + "����˵���������Զ���ĸ�ʽ����һ��ʱ�������������ʱ����Ϣ����������\n"
    + "          (���� string ��Ϣ)\n"
    + "���������1��(string) ��ʽ�淶(sFormat)\n"
    + "          2��(int) ����ѯ��ʱ��(iTime)\n"
    + "���ݣ�    ���ɴ��������ʹ�����д�����㡣\n"
    + "          ����1��ʡ�Բ���ʱ���õ���ǰʱ���Ĭ�ϸ�ʽ������\n"
    + "                2��ֻ���� (int) iTime ʱ��ʹ��Ĭ�ϸ�ʽ������\n"
    + "                3��ֻ���� (string) sFormat ʱ��ʹ�õ�ǰʱ�������\n"
    + "                4����������������ʱ������������ñ�����\n";
    msg += ""
    + "��ʽ�淶��["+DEFAULT_FORMAT_STR+"] �Ǳ�׼�ĸ�ʽ�����У�\n"
    + "           YY �����滻��Ϊ��ݵ������磺2005\n"
    + "           Y  �����滻 YY ֮��Y �����滻Ϊ����ݸ�ʽ�磺05\n"
    + "           M  �����滻��Ϊ�·ݵ������磺02, 11\n"
    + "           D  �����滻��Ϊ���ڵ������磺08, 31\n"
    + "           w  �����滻��Ϊ���ڵĺ����磺�����գ���\n"
    + "           h  �����滻��ΪСʱ�������磺01, 24\n"
    + "           m  �����滻��Ϊ���ӵ������磺01, 58\n"
    + "           s  �����滻��Ϊ���ӵ������磺08, 59\n";
    msg += ""
    + "           �������Ϲ��ɣ�������Զ���Ҫ�ĸ�ʽ�����磺\n"
    + "           ctime_format( \"Y-M-D h:m:s ����w\",1124174889 )  ���ó���\n"
    + "               05-08-16 14:48:09 ���ڶ�  ���ַǹ淶�ĸ�ʽ��\n"
    + "----------------------------------------------------------------------\n";
    return msg;
}

string i_to_s( int num )
{
    if( num == 0 )
        return "00";
    if( num < 10 )
        return sprintf( "0%d", num );
    return sprintf( "%d", num );
}
// ���������ļ�⺯����ϲ���Ļ���Ҳ����ֱ�ӵ��������ǻ��Ǿ������İ�ȫЩ�ɡ�
string ctime_format_real( int iTime, string sFormat )
{
    mixed *lt;
    string wday;
    if( !iTime || !sFormat )
        return 0;
    lt = localtime( iTime );
    if( !lt || !sizeof(lt) )
        return 0;
    // ������ڼ�������
    wday = chinese_number( lt[ LT_WDAY ] );
    if( lt[ LT_WDAY ] == 0 )
        wday = "��";
    sFormat = replace_string( sFormat, "YY", i_to_s(lt[LT_YEAR]) );      // ע�����Ҫ�� Y ǰ
    sFormat = replace_string( sFormat, "Y", (lt[LT_YEAR]+"")[2..<1] );   // ע�����Ҫ�� YY ��
    sFormat = replace_string( sFormat, "M", i_to_s(lt[LT_MON]+LT_MON_ADD) );
    sFormat = replace_string( sFormat, "D", i_to_s(lt[LT_MDAY]) );
    sFormat = replace_string( sFormat, "w", wday );
    sFormat = replace_string( sFormat, "h", i_to_s(lt[LT_HOUR]) );
    sFormat = replace_string( sFormat, "m", i_to_s(lt[LT_MIN]) );
    sFormat = replace_string( sFormat, "s", i_to_s(lt[LT_SEC]) );
    return sFormat;
}

varargs string ctime_format( mixed arg1, mixed arg2 )
{
    string sFormat;
    int iTime;
    
    // ����2������ʱ������Ĭ�ϸ�ʽ��õ�ǰʱ��ı���
    if( !arg1 && !arg2 )
    {
        return ctime_format_real( time(), DEFAULT_FORMAT_STR );
    }
    // ���Եڶ�������ʱ
    if( arg1 && !arg2 )
    {
        if( stringp(arg1) )
        {
            sFormat = arg1;
            iTime = time();
        }
        else if( intp(arg1) && arg1 > 0 )
        {
            iTime = arg1;
            sFormat = DEFAULT_FORMAT_STR;
        }
        else
            return 0;
    }
    // ���Ե�һ������ʱ(���紫�� 0, 1)
    if( !arg1 && arg2 )
    {
        if( stringp(arg2) )
        {
            sFormat = arg2;
            iTime = time();
        }
        else if( intp(arg2) && arg2 > 0 )
        {
            iTime = arg2;
            sFormat = DEFAULT_FORMAT_STR;
        }
        else
            return 0;
    }
    // ������������ʱ
    if( arg1 && arg2 )
    {
        if( intp(arg1) && arg1 > 0 && stringp(arg2) )
        {
            iTime = arg1;
            sFormat = arg2;
        }
        else if( stringp(arg1) && intp(arg2) && arg2 > 0 )
        {
            iTime = arg2;
            sFormat = arg1;
        }
        else
            return 0;
    }
    return ctime_format_real( iTime, sFormat );
}
