#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned int    OLSP_UINT32;
typedef unsigned char   OLSP_UINT8;
typedef unsigned char   uchar;
typedef unsigned char   OLSP_CHAR;
#define osal_isxdigit   isxdigit
#define osal_sscanf     sscanf
#define OSAL_TRACE_FUNCTION_ENTRY()
#define OSAL_TRACE_FUNCTION_EXIT()

typedef enum E_streamlibHttpClientChunkOutputTag
{
    E_STREAMLIB_HTTP_CHUNKED_NO_ERROR,
    E_STREAMLIB_HTTP_CHUNKED_PARTIAL,
    E_STREAMLIB_HTTP_CHUNKED_ERROR,
    E_STREAMLIB_HTTP_CHUNKED_CRLF
}E_streamlibHttpClientChunkOutput_t;

#if 1
E_streamlibHttpClientChunkOutput_t  streamlib_httpClientCoreGetChunkedLength(OLSP_UINT8 **pp_u8_msg,
                                                                             OLSP_UINT32  *p_u32_msgSize,
                                                                             OLSP_UINT32  *p_u32_chunkLength)
{
    OLSP_UINT8 *p_u8_msgPtr;
    OLSP_UINT32 u32_remBytes;
    E_streamlibHttpClientChunkOutput_t e_chunkError = E_STREAMLIB_HTTP_CHUNKED_NO_ERROR;

    if (u32_remBytes == 0)
    {
        e_chunkError = E_STREAMLIB_HTTP_CHUNKED_ERROR;
        goto END_streamlib_httpClientCoreGetChunkedLength;
    }

//    if (u32_remBytes < 2)
//    {
//        e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
//        goto END_streamlib_httpClientCoreGetChunkedLength;
//    }

    if (((**pp_u8_msg) == '\r') && (*((*pp_u8_msg) + 1) == '\n'))
    {
        (*pp_u8_msg) += 2;
        (*p_u32_msgSize) -= 2;
        e_chunkError = E_STREAMLIB_HTTP_CHUNKED_CRLF;
        p_u8_msgPtr = *pp_u8_msg;
        u32_remBytes = *p_u32_msgSize;
        goto END_streamlib_httpClientCoreGetChunkedLength;
    }
    else if ((**pp_u8_msg) == '\n')
    {
        e_chunkError = E_STREAMLIB_HTTP_CHUNKED_CRLF;
        (*pp_u8_msg)++;
        (*p_u32_msgSize)--;
        p_u8_msgPtr = *pp_u8_msg;
        u32_remBytes = *p_u32_msgSize;
        goto END_streamlib_httpClientCoreGetChunkedLength;
    }

    while (0 == isxdigit(**pp_u8_msg))
    {
        (*pp_u8_msg)++;
        (*p_u32_msgSize)--;
        if ((*p_u32_msgSize) == 0)
        {
            e_chunkError = E_STREAMLIB_HTTP_CHUNKED_ERROR;
            p_u8_msgPtr = *pp_u8_msg;
            u32_remBytes = *p_u32_msgSize;
            goto END_streamlib_httpClientCoreGetChunkedLength;
        }
    }

    p_u8_msgPtr = *pp_u8_msg;
    u32_remBytes = *p_u32_msgSize;

    while((*p_u8_msgPtr != ';') && ((*p_u8_msgPtr != '\r') || (*(p_u8_msgPtr + 1) != '\n')))
    {
        p_u8_msgPtr ++;
        u32_remBytes --;
        if (u32_remBytes == 0)
        {
            e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
            goto END_streamlib_httpClientCoreGetChunkedLength;
        }
    }

    if (*p_u8_msgPtr == ';')
    {
        *p_u8_msgPtr = '\0';
        while((*p_u8_msgPtr != '\r') || (*(p_u8_msgPtr + 1) != '\n'))
        {
            p_u8_msgPtr ++;
            u32_remBytes --;
            if (u32_remBytes == 0)
            {
                e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
                goto END_streamlib_httpClientCoreGetChunkedLength;
            }
        }
    }
    else
    {
        *p_u8_msgPtr = '\0';
    }

    p_u8_msgPtr += 2;
    u32_remBytes -= 2;
    if (u32_remBytes == 0)
    {
        goto END_streamlib_httpClientCoreGetChunkedLength;
    }

END_streamlib_httpClientCoreGetChunkedLength:
    if (e_chunkError != E_STREAMLIB_HTTP_CHUNKED_ERROR)
    {
        sscanf(*pp_u8_msg, "%x", p_u32_chunkLength);
    }
    *pp_u8_msg = p_u8_msgPtr;
    *p_u32_msgSize = u32_remBytes;
    return e_chunkError;
}
#endif
#if 0
static E_streamlibHttpClientChunkOutput_t  streamlib_httpClientCoreGetChunkedLength(OLSP_UINT8   **pp_u8_message,
                                                                             OLSP_UINT32  *p_u32_msgSize,
                                                                             OLSP_UINT32  *p_u32_chunkLength)
{
    E_streamlibHttpClientChunkOutput_t e_chunkError = E_STREAMLIB_HTTP_CHUNKED_NO_ERROR;
    OLSP_UINT32 u32_remBytes = *p_u32_msgSize;
    OLSP_UINT8  *p_u8_msgRef = *pp_u8_message;
    OSAL_TRACE_FUNCTION_ENTRY();

    switch(u32_remBytes)
    {
        case 0:
            e_chunkError = E_STREAMLIB_HTTP_CHUNKED_ERROR;
            goto END_streamlib_httpClientCoreGetChunkedLength;
            break;
        case 1:
            u32_remBytes = 0;
            if ((*p_u8_msgRef) == '\n')
            {
                e_chunkError = E_STREAMLIB_HTTP_CHUNKED_CRLF;
                p_u8_msgRef ++;
                goto END_streamlib_httpClientCoreGetChunkedLength;
            }
            else
            {
                if (0 != osal_isxdigit(*p_u8_msgRef))
                {
                    e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
                }
                else
                {
                    e_chunkError = E_STREAMLIB_HTTP_CHUNKED_ERROR;
                }
                p_u8_msgRef ++;
            }
            goto END_streamlib_httpClientCoreGetChunkedLength;
        case 2:
            if ((*p_u8_msgRef) == '\r' && *(p_u8_msgRef + 1) == '\n')
            {
                e_chunkError = E_STREAMLIB_HTTP_CHUNKED_CRLF;
                p_u8_msgRef += 2;
                u32_remBytes = 0;
                goto END_streamlib_httpClientCoreGetChunkedLength;
            }
            break;
        default:
            break;
    }

    /*
     * At this point msgsize is >= 2
     */
    while((*p_u8_msgRef != ';') && ((*p_u8_msgRef != '\r') || (*(p_u8_msgRef + 1) != '\n')))
    {
        p_u8_msgRef ++;
        u32_remBytes --;
        if (u32_remBytes == 0)
        {
            e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
            goto END_streamlib_httpClientCoreGetChunkedLength;
        }
    }

    if (*p_u8_msgRef == ';')
    {
        *p_u8_msgRef = '\0';
        while((*p_u8_msgRef != '\r') || (*(p_u8_msgRef + 1) != '\n'))
        {
            p_u8_msgRef ++;
            u32_remBytes --;
            if (u32_remBytes == 0)
            {
                e_chunkError = E_STREAMLIB_HTTP_CHUNKED_PARTIAL;
                goto END_streamlib_httpClientCoreGetChunkedLength;
            }
        }
    }
    else
    {
        *p_u8_msgRef = '\0';
    }

    /*
     * Since we wan't to increment by 2 for moving past CRLF, checking is done
     * not to corrupt memory
     */
    if (u32_remBytes < 2)
    {
        goto END_streamlib_httpClientCoreGetChunkedLength;
    }
    p_u8_msgRef += 2;
    u32_remBytes -= 2;

END_streamlib_httpClientCoreGetChunkedLength:
    if (e_chunkError == E_STREAMLIB_HTTP_CHUNKED_NO_ERROR || e_chunkError == E_STREAMLIB_HTTP_CHUNKED_PARTIAL)
    {
        osal_sscanf((OLSP_CHAR *)*pp_u8_message, "%x", p_u32_chunkLength);
    }
    *pp_u8_message = p_u8_msgRef;
    *p_u32_msgSize = u32_remBytes;
    OSAL_TRACE_FUNCTION_EXIT();
    return e_chunkError;
}
#endif

int calculateNearestPlaceValue(int number)
{
    int count = 10;
    while (number)
    {
        number = number/10;
        if (number)
        {
            count *= 10;
        }
    }
    return count;
}

int main(int argc, char *argv[])
{
    FILE *read, *write;
    int chunklength = 0;
    uchar data[32000];
    uchar aux[32000];
    uchar *ptr = data;
    int msgSize = 32000;
    int auxlen = 32000;
    E_streamlibHttpClientChunkOutput_t e_chunkError;
    int partial = 0;
    int byteswritten = 0;
    char hexbuf[8];

    read = fopen(argv[1], "rb");
    write = fopen(argv[2], "wb");

    if (read == NULL || write == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while(1)
    {
        if (msgSize == 32000)
        {
            if(32000 != fread(data, 1, 32000, read))
            {
                break;
            }
        }
        if (chunklength == 0)
        {
            e_chunkError = streamlib_httpClientCoreGetChunkedLength(&ptr, &msgSize, &chunklength);
            if (e_chunkError == E_STREAMLIB_HTTP_CHUNKED_PARTIAL)
            {
                partial = chunklength;
                msgSize = 32000;
                ptr = data;
                chunklength = 0;
                e_chunkError = E_STREAMLIB_HTTP_CHUNKED_NO_ERROR;
                continue;
            }
        }

        if (e_chunkError == E_STREAMLIB_HTTP_CHUNKED_CRLF)
        {
            e_chunkError = E_STREAMLIB_HTTP_CHUNKED_NO_ERROR;
            chunklength = partial;
            partial = 0;
        }
        else if (partial != 0)
        {
            sprintf(hexbuf, "%x%x", partial, chunklength);
            sscanf(hexbuf, "%x", &chunklength);
            partial = 0;
        }

        if ((chunklength) < msgSize)
        {
            if (auxlen != 32000)
            {
                fwrite(aux, 1, (32000 - auxlen), write);
                byteswritten += (32000 - auxlen);
                auxlen = 32000;
            }
            fwrite(ptr, 1, chunklength, write);
            byteswritten += chunklength;
#if 0
            if (byteswritten >= 79790000)
            {
                printf("Byteswritten = %d\n", byteswritten);
            }
#endif
            ptr += chunklength;
            msgSize -= chunklength;
            if ((msgSize >= 2) && ((*ptr == '\r') && (*(ptr + 1) == '\n')))
            {
                ptr += 2;
                msgSize -= 2;
            }
            if (msgSize == 0)
            {
                msgSize = 32000;
                ptr = data;
            }
            chunklength = 0;
        }
        else
        {
            memcpy(aux, ptr, msgSize);
            chunklength -= msgSize;
            auxlen -= msgSize;
            msgSize = 32000;
            ptr = data;
        }
    }
}
