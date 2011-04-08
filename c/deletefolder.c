#include <dirent.h>
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define PRINT_ARGS(param, rest...)              printf(param, ##rest)
#else
#define PRINT_ARGS(param, rest...)
#endif


int deleteDirectory(char *p_ch_directory)
{
    DIR *p_s_dirRef = NULL;
    struct dirent s_dirEntry;
    struct dirent *p_s_dirEntRef = NULL;
    int s32_rv = 1;
    char a_ch_subDir[256];

    if (p_ch_directory == NULL)
    {
        PRINT_ARGS("Invalid input param\n");
        s32_rv = -1;
        goto END_deleteDirectory;
    }

    p_s_dirRef = opendir(p_ch_directory);
    if (p_s_dirRef == NULL)
    {
        PRINT_ARGS("Error opening directory\n");
        s32_rv = -1;
        goto END_deleteDirectory;
    }

    while(1)
    {
        s32_rv = readdir_r(p_s_dirRef, &s_dirEntry, &p_s_dirEntRef);
        if (s32_rv > 0)
        {
            PRINT_ARGS("Error reading directory\n");
            s32_rv = -1;
            goto END_deleteDirectory;
        }

        if ((s32_rv == 0) && (p_s_dirEntRef == NULL))
        {
            PRINT_ARGS("All sub-directories read\n");
            s32_rv = rmdir(p_ch_directory);
            if (s32_rv == -1)
            {
                PRINT_ARGS("Error deleting directory %s\n", p_ch_directory);
                s32_rv = -1;
                goto END_deleteDirectory;
            }
            s32_rv = 2;
            goto END_deleteDirectory;
        }

        switch(s_dirEntry.d_type)
        {
            case DT_BLK:
                PRINT_ARGS("This is a block device.\n");
                break;

            case DT_CHR:
                PRINT_ARGS("This is a character device.\n");
                break;

            case DT_DIR:
                if((strcmp(s_dirEntry.d_name,".")!=0) && (strcmp(s_dirEntry.d_name,"..")!=0))
                {
                    PRINT_ARGS("%s - ", s_dirEntry.d_name);
                    PRINT_ARGS("This is a directory.\n");
                    sprintf(a_ch_subDir, "%s/%s", p_ch_directory, s_dirEntry.d_name);
                    PRINT_ARGS("Entering subdir %s\n", a_ch_subDir);
                    while(1)
                    {
                        s32_rv = deleteDirectory(a_ch_subDir);
                        if (s32_rv == -1)
                        {
                            PRINT_ARGS("Error deleting sub-directory %s\n", a_ch_subDir);
                            s32_rv = -1;
                            goto END_deleteDirectory;
                        }

                        if(s32_rv > 0)
                        {
                            break;
                        }
                    }
                }
                break;

            case DT_FIFO:
                PRINT_ARGS("This is a named pipe (FIFO).\n");
                break;

            case DT_LNK:
                PRINT_ARGS("%s - ", s_dirEntry.d_name);
                PRINT_ARGS("This is a symbolic link.\n");
                sprintf(a_ch_subDir, "%s/%s", p_ch_directory, s_dirEntry.d_name);
                s32_rv = unlink(a_ch_subDir);
                if (s32_rv == -1)
                {
                    PRINT_ARGS("Error deleting symbolic link %s\n", a_ch_subDir);
                    s32_rv = -1;
                    goto END_deleteDirectory;
                }
                PRINT_ARGS("Removed %s\n", a_ch_subDir);
                break;

            case DT_REG:
                PRINT_ARGS("%s - ", s_dirEntry.d_name);
                PRINT_ARGS("This is a regular file.\n");
                sprintf(a_ch_subDir, "%s/%s", p_ch_directory, s_dirEntry.d_name);
                s32_rv = remove(a_ch_subDir);
                if (s32_rv == -1)
                {
                    PRINT_ARGS("Error deleting file %s\n", a_ch_subDir);
                    s32_rv = -1;
                    goto END_deleteDirectory;
                }
                PRINT_ARGS("Removed %s\n", a_ch_subDir);
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

END_deleteDirectory:
    return s32_rv;
}

int main(int argc, char *argv[])
{
    char a_ch_dir[256];
    if (argc == 1)
    {
        printf("Enter the directory to be deleted\n");
        scanf("%s", a_ch_dir);
    }
    else
    {
        strcpy(a_ch_dir, argv[1]);
    }
    PRINT_ARGS("Directory to be deleted %s\n", a_ch_dir);
    if(deleteDirectory(a_ch_dir))
    {
        PRINT_ARGS("Directory deleted successfully\n");
    }
    else
    {
        PRINT_ARGS("Unable to delete directory %s\n", a_ch_dir);
    }
}
