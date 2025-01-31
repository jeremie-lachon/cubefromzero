#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main()
{
    struct timeval tv;

    time_t curtime;
    while(1)
    {
        gettimeofday(&tv, NULL);
        printf("Time %ld\n", tv.tv_sec % 5);
        sleep(1);
    }
    return 0;
}