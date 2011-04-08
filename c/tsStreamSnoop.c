#include <stdio.h>
#include <stdlib.h>

#define TS_PACKET_LENGTH                        188
#define TS_PACKET_LENGTH_WITHOUT_HEADER         184
#define SCRAMBLING_CONTROL_MASK                 0xC0
#define ADAPTATION_FIELD_CONTROL_MASK           0x30
#define CONTINUITY_COUNTER_MASK                 0x0F

#ifndef QUIET
#define PRINT_ARGS(param, rest...)              printf(param, ##rest)
#else
#define PRINT_ARGS(param, rest...)
#endif

/* Global flags to indicate the presence of Adaptation Field and Payload */
int doesAdaptationFieldExist = 0;
int doesPayloadExist = 0;

int main(int argc, char *argv[])
{
    PRINT_ARGS("%s Entry\n", __FUNCTION__);
    FILE *inputFilePtr, *outputFilePtr;
    int ch, bytesToSkip = 0;
    unsigned char buffer[TS_PACKET_LENGTH];

    if (argc != 3)
    {   
        printf("Usage : <exe> <input tsfile> <output file>\n");
        exit(0);
    }

    inputFilePtr = fopen(argv[1], "rb");
    outputFilePtr = fopen(argv[2], "wb");

    while ((ch = fgetc(inputFilePtr)) != EOF)
    {
        PRINT_ARGS("\n\n========================================\n\n");
        if (ch != 0x47)
        {
            PRINT_ARGS("Sync byte not found\n");
            break;
        }
        PRINT_ARGS("The sync byte received is 0x%x\n", ch);
        
        /* Skipping Transport error indicator, Payload unit start indicator and Packet Id */
        fseek(inputFilePtr, 2, SEEK_CUR);

        ch = fgetc(inputFilePtr);
        PRINT_ARGS("The current scrambling control detail is :\t");
        switch(ch & SCRAMBLING_CONTROL_MASK)
        {
            case 0x00:
                PRINT_ARGS("Not Scrambled.\n");
                break;
            case 0x40:
                PRINT_ARGS("Reserved for future use.\n");
                break;
            case 0x80:
                PRINT_ARGS("Scrambled with even key.\n");
                break;
            case 0xC0:
                PRINT_ARGS("Scrambled with odd key.\n");
                break;
            default:
                PRINT_ARGS("Somewhere some error has occurred!\n");
                break;
        }

        /* Parsing the Adaptation Field and Payload Field exist flags by 'AND'ing with 00110000 */
        switch (ch & ADAPTATION_FIELD_CONTROL_MASK)
        {
            case 0x00:
                PRINT_ARGS("Both Adaptation Field and Payload are absent\n");
                break;
            case 0x10:
                PRINT_ARGS("Only Payload is present\n");
                doesPayloadExist = 1;
                break;
            case 0x20:
                PRINT_ARGS("Only Adaptation Field Exist\n");
                doesAdaptationFieldExist = 1;
                break;
            case 0x30:
                PRINT_ARGS("Both Adaptation Field and Payload exist. Adaptation field followed by payload.\n");
                doesPayloadExist = 1;
                doesAdaptationFieldExist = 1;
                break;
            default:
                PRINT_ARGS("Somewhere some error has occurred!\n");
                break;
        }
        
        /* Parsing the continuity counter by 'AND'ing with 00001111*/
        PRINT_ARGS("The Continuity Counter got is 0x%x\n", (ch & CONTINUITY_COUNTER_MASK));

        bytesToSkip = TS_PACKET_LENGTH_WITHOUT_HEADER;
        if (doesAdaptationFieldExist)
        {
            ch = fgetc(inputFilePtr);
            PRINT_ARGS("The length of the Adaptation Field is %d bytes (0x%x)\n", ch, ch);
            bytesToSkip = TS_PACKET_LENGTH_WITHOUT_HEADER - ch - 1;
            fseek(inputFilePtr, (ch), SEEK_CUR);
            PRINT_ARGS("Skipped %d bytes of Adaptation Field\n", ch);
            doesAdaptationFieldExist = 0;
        }

        if (doesPayloadExist)
        {
            PRINT_ARGS("Length of the Payload is %d\n", bytesToSkip);
            fread(buffer, 1, bytesToSkip, inputFilePtr);
            if (buffer[0] == 0x00 && buffer[1] == 0x00 && buffer[2] == 0x01)
            {
                printf("Found PES Start Code Prefix ");
                if (0xE0 == (buffer[3] & 0xF0))
                {
                    printf("& Video Stream\n");
                    printf("The PES Packet Length is %x%x\t%d %d", buffer[4], buffer[5], buffer[4], buffer[5]);
                }
                else if((0xC0 == (buffer[3] & 0xF0)) || (0xD0 == (buffer[3] & 0xF0)))
                {
                    printf("& Audio Stream\n");
                }
                else
                {
                    printf("but some unknown stream and the value of stream Id is 0x%x\n", buffer[3]);
                }
            }
            fwrite(buffer, 1, bytesToSkip, outputFilePtr);
            doesPayloadExist = 0;
        }
    }
}
