
#include <stdio.h>

template <class T>

T add(T a, T b)
{
    return a + b;
}

int main(int argc, const char *argv[])
{
    int n;
    float f;
    char c;

    n = add(8, 9);
    f = add(3.2f, 8.7f);
    c = add('Z', ' ');

    printf("n = %d, f = %.1f, c = %c\n", n, f, c);

    return 0;
}
