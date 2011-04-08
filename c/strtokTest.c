#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
int
main(int argc, char *argv[])
{
    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s string delim subdelim\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("String %s\n", argv[1]);
    printf("Delim %s\n", argv[2]);
    printf("SubDelim %s\n", argv[3]);
    for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
        token = strtok_r(str1, argv[2], &saveptr1);
        if (token == NULL)
            break;
        printf("%d: %s\n", j, token);

        for (str2 = token; ; str2 = NULL) {
            subtoken = strtok_r(str2, argv[3], &saveptr2);
            if (subtoken == NULL)
                break;
            printf(" --> %s\n", subtoken);
        }
    }

    exit(EXIT_SUCCESS);
} /* main */

#else
int main()
{
    /*
       Module-Ref:
       1) arib-dc://<original_network_id>.<transport_stream_id>.<service_id>[;<content_id>] [.<event_id>]/<component_tag>/<moduleName>
       2)/<componenet_tag>/<moduleName>
       */
    char arr[] = "arib-dc://10.16.22;25.24/40/1000";
    //char arr[] = "/40;0000/";
    char *ptr = arr, *savePtr;
    ptr += 10;
    ptr = strtok_r(ptr, "/", &savePtr);
    printf("The first token is :\n");
    printf("%s\n", ptr);
    printf("The component_tag token is :\n");
    ptr = strtok_r(NULL, "/", &savePtr);
    printf("%s\n", ptr);
    printf("The third token is :\n");
    ptr = strtok_r(NULL, "/", &savePtr);
    printf("%s\n", ptr);
    printf("The array is %s\n", arr);
    printf("The fourth token is :\n");
    ptr = strtok_r(NULL, "/", &savePtr);
    printf("%s\n", ptr);
    printf("The fifth token is :\n");
    ptr = strtok_r(NULL, "/", &savePtr);
    ptr = strtok_r(NULL, "/", &savePtr);
    ptr = strtok_r(NULL, "/", &savePtr);
    printf("Came here\n");
    printf("%s\n", ptr);
}
#endif
