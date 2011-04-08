#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main (void)
{
        fd_set read_set;
        fd_set write_set;
        int i;

        FD_ZERO (&read_set);
        FD_ZERO (&write_set);

        FD_SET (28, &read_set);
        printf("Read FDSET \n");
        for (i = 0; i < sizeof(read_set.__fds_bits); i++ )
        {
                printf("%ld ", read_set.__fds_bits[i]);
        }
        printf("\n");
        printf("Write FDSET \n");
        FD_SET (28, &write_set);
        for (i = 0; i < sizeof(write_set.__fds_bits); i++ )
        {
                printf("%ld ", write_set.__fds_bits[i]);
        }
        printf("\n");
        FD_SET (30, &read_set);
        printf("Read FDSET \n");
        for (i = 0; i < sizeof(read_set.__fds_bits); i++ )
        {
                printf("%ld ", read_set.__fds_bits[i]);
        }
        printf("\n");
        printf("Write FDSET \n");
        FD_SET (30, &write_set);
        for (i = 0; i < sizeof(write_set.__fds_bits); i++ )
        {
                printf("%ld ", write_set.__fds_bits[i]);
        }
        printf("\n");

        printf ("read_set:\n");
        for (i = 0; i < 4; i++) {
                printf ("  bit %d is %s\n", i,
                        (FD_ISSET (i, &read_set)) ? "set" : "clear");
        }

        printf ("write_set:\n");
        for (i = 0; i < 4; i++) {
                printf ("  bit %d is %s\n", i,
                        (FD_ISSET (i, &write_set)) ? "set" : "clear");
        }

        return (0);
}

