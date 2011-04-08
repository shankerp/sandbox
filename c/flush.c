#include <stdio.h>

typedef int OLSP_SINT32;

typedef enum E_mdsrVodTunerTrickPlayModeTag
{
    E_MDSR_VOD_TUNER_TRICK_PLAY_MODE_NONE     = 0,
    E_MDSR_VOD_TUNER_TRICK_PLAY_NORMAL        = 1,
    E_MDSR_VOD_TUNER_TRICK_PLAY_PAUSE         = 2,
    E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_FORWARD  = 3,
    E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_REWIND   = 4,
    E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_FORWARD  = 5,
    E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_REWIND   = 6,
    E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_FORWARD = 7,
    E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND  = 8,
    E_MDSR_VOD_TUNER_TRICK_PLAY_JUMP          = 9
}E_mdsrVodTunerTrickPlayMode_t;

static OLSP_SINT32 vodTunerCoreIsBufferFlushRequired(E_mdsrVodTunerTrickPlayMode_t e_previousMode,
                                                     E_mdsrVodTunerTrickPlayMode_t e_currentMode,
                                                     E_mdsrVodTunerTrickPlayMode_t e_requestedMode)
{
    OLSP_SINT32 s32_returnValue = 0;
    OLSP_SINT32 s32_count = 0;

    switch(e_requestedMode)
    {
        case E_MDSR_VOD_TUNER_TRICK_PLAY_MODE_NONE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_NORMAL:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_PAUSE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_FORWARD:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_FORWARD:
            break;

        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_FORWARD:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_JUMP:
            s32_returnValue = 1;
            goto END_vodTunerCoreIsBufferFlushRequired;
            break;
    }

    switch(e_currentMode)
    {
        case E_MDSR_VOD_TUNER_TRICK_PLAY_NORMAL:
            if (e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_FORWARD)
            {
                goto END_vodTunerCoreIsBufferFlushRequired;
            }
            break;
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_FORWARD:
            if (e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_NORMAL ||
                    e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_FORWARD ||
                    e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_PAUSE)
            {
                goto END_vodTunerCoreIsBufferFlushRequired;
            }
            break;
        case E_MDSR_VOD_TUNER_TRICK_PLAY_MODE_NONE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_PAUSE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_FORWARD:
            if(e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND)
            {
                s32_returnValue = 1;
                goto END_vodTunerCoreIsBufferFlushRequired;
            }
            break;

        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND:
            if(e_requestedMode == E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND)
            {
                s32_returnValue = 0;
                goto END_vodTunerCoreIsBufferFlushRequired;
            }
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_FORWARD:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_JUMP:
            s32_returnValue = 1;
            goto END_vodTunerCoreIsBufferFlushRequired;
            break;
    }

    switch(e_previousMode)
    {
        case E_MDSR_VOD_TUNER_TRICK_PLAY_PAUSE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_MODE_NONE:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_NORMAL:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_FORWARD:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_FORWARD:
            break;

        case E_MDSR_VOD_TUNER_TRICK_PLAY_FRAME_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_FORWARD:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_FAST_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_SLOW_REWIND:
        case E_MDSR_VOD_TUNER_TRICK_PLAY_JUMP:
            s32_returnValue = 1;
            goto END_vodTunerCoreIsBufferFlushRequired;
            break;
    }
END_vodTunerCoreIsBufferFlushRequired:
    return s32_returnValue;
}

int main()
{
    int s32_count = 0;
    char array[][20] = {
                        "NONE",
                        "PLAY",
                        "PAUSE",
                        "FAST_FORWARD",
                        "FAST_REWIND",
                        "SLOW_FORWARD",
                        "SLOW_REWIND",
                        "FRAME_FORWARD",
                        "FRAME_REWIND",
                        "JUMP",
                     };


    for (s32_count = 0; s32_count <1000; s32_count ++)
    {
#if 0
        printf("%s to %s to %s -->", &array[(s32_count/100)][0], &array[((s32_count%100)/10)][0], &array[((s32_count%100)%10)]);
#endif
        printf("%s to %s to %s\n", &array[(s32_count/100)][0], &array[((s32_count%100)/10)][0], &array[((s32_count%100)%10)][0]);
#if 0
        if(0 == vodTunerCoreIsBufferFlushRequired((s32_count/100), ((s32_count%100)/10), ((s32_count%100)%10)))
        {
            printf("Not Required\n");
        }
        else
        {
            printf("Required\n");
        }
#endif
    }
}
