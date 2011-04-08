#include <stdio.h>

int main()
{
    FILE *fp;
    unsigned char buf[5];
    unsigned int num = 10;

    fp = fopen("fprintf", "wb");
    fprintf(NULL, "%c\r\n", 7);
    fprintf(fp, "%c\r\n", 21);
    fprintf(fp, "%c\r\n", 35);
    fclose(fp);
    fp = fopen("fprintf", "rb");
    fread(buf, 1, 5, fp);
    printf("%d", buf[0]);

}
