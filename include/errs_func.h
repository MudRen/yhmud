// by naihe 200?.??.??   ���ǵ�ʲôʱ��д����
// ��ʱ�������� notify_fail() ����һЩ add_action() ������ return errs() ���Խ�ֹ����ִ�С�
varargs int errs(string msg, object who)
{
        if( !msg )
                return 1;
        if( objectp(who) )
                tell_object( who, msg );
        else
                write( msg );
        return 1;
}

