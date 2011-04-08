#include <stdio.h>

int main()
{
    FILE *fp;
    printf("Sleep Started\n");
    sleep(5);
    printf("Sleep End\n");
    char arr[] = "File writing works\n";
    fp = fopen("test.txt","wb+");
    fwrite(arr, 1,sizeof(arr), fp);
    return 1;
}
