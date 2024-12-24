#include <unistd.h>
#include <stdio.h>

int main(void)
{
    // int x;

    // x = a ;
    // x |= (b << 8);
    // x |= (c << 16);

    // int a2 = x & 0xFF;
    // int b2 = (x >> 8) & 0xFF;
    // int c2 = (x >> 16) & 0xFF;
    // printf("A2 %d\n", a2);
    // printf("B2 %d\n", b2);
    // printf("C2 %d\n", c2);

    int a = 150;
    int b = 255;
    int c = 135;
    int ret;

    ret = (a << 16);
    if (((ret >> 16) & 0xFF) < 0 || ((ret >> 16) & 0xFF) > 255)
        return (-1);
    ret |= (b << 8);
    if (((ret >> 8) & 0xFF) < 0 || ((ret >> 8) & 0xFF) > 255)        
        return (-1);
    ret |= c;
    if ((ret & 0xFF) < 0 || ((ret & 0xFF) > 255))
        return (-1);
    int a2 = (ret >> 16) & 0xFF;
    int b2 = (ret >> 8) & 0xFF;
    int c2 = (ret) & 0xFF;
    printf("A2 %d\n", a2);
    printf("B2 %d\n", b2);
    printf("C2 %d\n", c2);
    return (0);
}