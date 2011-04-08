#include <stdio.h>
#include <string.h>

int main()
{
    char buf[50];
    FILE *fp;
    fp = fopen("temp", "wb");
    fprintf(fp, "%x\r\n", 35);
    fwrite(buf, 1, 35, fp);

}
