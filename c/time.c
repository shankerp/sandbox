#include <stdio.h>
#include <time.h>

int main()
{
    struct tm ltime;
    time_t timer;
    char arr[22];

    timer = time(NULL);
    localtime_r(&timer, &ltime);
    strftime(arr, 22, "%Y-%b-%d  %T", &ltime);
    printf("%s\n", arr);
}
