// atoi.c

int atoi(string str)
{
        int v;

        if (! stringp(str) || ! sscanf(str, "%d", v))
                return 0;

	return v;
}

//���������ֵ by н������
mixed abs(mixed n)
{

        if (! floatp(n) && ! intp(n))
                return 0;

        return (n < 0)? -n : n;

}