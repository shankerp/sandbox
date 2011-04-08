#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define PRINT_ARGS(param, rest...)              printf(param, ##rest)
#else
#define PRINT_ARGS(param, rest...)
#endif

int filter(const struct dirent *p_s_dirEntRef)
{
    int s32_rv = 0;

    if (p_s_dirEntRef != NULL)
    {
        switch(p_s_dirEntRef->d_type)
        {
            case DT_BLK:
                break;

            case DT_CHR:
                break;

            case DT_DIR:
                if((strcmp(p_s_dirEntRef->d_name,".")!=0) && (strcmp(p_s_dirEntRef->d_name,"..")!=0))
                {
                    s32_rv = 1;
                }
                break;

            case DT_FIFO:
                PRINT_ARGS("This is a named pipe (FIFO).\n");
                break;

            case DT_LNK:
                PRINT_ARGS("This is a symbolic link.\n");
                s32_rv = 1;
                break;

            case DT_REG:
                PRINT_ARGS("This is a regular file.\n");
                s32_rv = 1;
                break;

            case DT_SOCK:
                PRINT_ARGS("This is a Unix domain socket.\n");
                break;

            default:
            case DT_UNKNOWN:
                PRINT_ARGS("The file type is unknown.\n");
                break;
        }
    }

    return s32_rv;
}

int scandirectory(char *p_ch_directory, struct dirent ***ppp_s_namelist)
{
    int s32_rv = 0;

    s32_rv = scandir(p_ch_directory, ppp_s_namelist, filter, alphasort);
    if (s32_rv < 0)
    {
        PRINT_ARGS("Error scanning directory\n");
    }
    return s32_rv;
}

void freescanned(struct dirent ***ppp_s_namelist, int s32_count)
{
    while(s32_count--)
    {
        free(ppp_s_namelist[s32_count]);
    }
    free(ppp_s_namelist);
}

int main(int argc, char *argv[])
{
    char a_ch_dir[256];
    struct dirent **pp_s_namelist;
    int s32_rv = 0;
    int s32_count = 0;

    if (argc == 1)
    {
        printf("Enter the directory to be sorted\n");
        scanf("%s", a_ch_dir);
    }
    else
    {
        strcpy(a_ch_dir, argv[1]);
    }
    PRINT_ARGS("Directory to be sorted %s\n", a_ch_dir);

    s32_rv = scandirectory(a_ch_dir, &pp_s_namelist);
    if (s32_rv)
    {
        PRINT_ARGS("Directory sorted successfully\n");
        while(s32_rv--)
        {
            printf("%s\n", pp_s_namelist[s32_count]->d_name);
            s32_count++;
        }
    }
    else
    {
        PRINT_ARGS("Unable to sort directory %s\n", a_ch_dir);
    }

    freescanned(&pp_s_namelist, s32_count);
}
