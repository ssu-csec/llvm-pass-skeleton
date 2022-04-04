int foo()
{
    int a = 4;
    int b = 5;
    int c = 6;
    int d = 7;
    int e = 8;
    int f = 9;
    a = b + c;
    b = d + e;
    c = e + f;
    return a + 1;
}
int bar(int a, int b)
{
    int c = 12;
    int d = 7;
    int e = 8;
    int f = 9;
    c = e + f;
    d = a+c;
    f = a+b;
    d = c-f;
    e = b-d;
    f = a%c;
    d = b*f;
    return c;
}