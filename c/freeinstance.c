#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int s32_streamId;
    int dummy;
} S_streamlibRtspClientObj_t;

typedef struct
{
    int s32_maxNumInstance;
    S_streamlibRtspClientObj_t *p_s_streamlibRtspClientObjectListRef;
}S_streamlibRtspClientObjList_t;

S_streamlibRtspClientObjList_t g_s_streamlibRtspClientList = {0, NULL};

#define E_MDSR_VOD_TUNER_ERR_NO_RESOURCE (-2)
#define E_MDSR_VOD_TUNER_ERR_INVALID_PARAM (-1)
#define E_MDSR_VOD_TUNER_ERR_NONE (0)
#define OLSP_STREAMLIB_RTSPCLIENTCORE_INVALID_STREAM_ID (-1)

int streamlib_rtspClientCoreGetFreeInstance(S_streamlibRtspClientObj_t **pp_s_rtspClientObjRef)
{
    int e_vodTunerError = E_MDSR_VOD_TUNER_ERR_NO_RESOURCE;
    int s32_count = 0;


    if (pp_s_rtspClientObjRef == NULL)
    {
        e_vodTunerError = E_MDSR_VOD_TUNER_ERR_INVALID_PARAM;
        printf("Invalid input params\n");
        goto END_streamlib_rtspClientCoreGetFreeInstance;
    }

    *pp_s_rtspClientObjRef = NULL;

    for (s32_count = 0; s32_count < g_s_streamlibRtspClientList.s32_maxNumInstance ; s32_count ++)
    {
        if((g_s_streamlibRtspClientList.p_s_streamlibRtspClientObjectListRef[s32_count]).s32_streamId = OLSP_STREAMLIB_RTSPCLIENTCORE_INVALID_STREAM_ID)
        {
            *pp_s_rtspClientObjRef = &(g_s_streamlibRtspClientList.p_s_streamlibRtspClientObjectListRef[s32_count]) ;
            e_vodTunerError = E_MDSR_VOD_TUNER_ERR_NONE;
            break;
        }
    }
END_streamlib_rtspClientCoreGetFreeInstance:
    return e_vodTunerError;
}

int main()
{
    S_streamlibRtspClientObj_t *p_s_rtspClientObjRef = NULL;
    int s32_count = 0;

    g_s_streamlibRtspClientList.p_s_streamlibRtspClientObjectListRef = (S_streamlibRtspClientObj_t *)malloc(5 * sizeof(S_streamlibRtspClientObj_t));
    g_s_streamlibRtspClientList.s32_maxNumInstance = 5;

    for (s32_count = 0; s32_count < 5; s32_count++ )
    {
        g_s_streamlibRtspClientList.p_s_streamlibRtspClientObjectListRef[s32_count].s32_streamId = OLSP_STREAMLIB_RTSPCLIENTCORE_INVALID_STREAM_ID;
    }

    for (s32_count = 0; s32_count < 5; s32_count++ )
    {
        streamlib_rtspClientCoreGetFreeInstance(&p_s_rtspClientObjRef);

        printf("Object Address %p\n", p_s_rtspClientObjRef);

        p_s_rtspClientObjRef->s32_streamId = s32_count;
    }
}
