/*
 * tsheaderparse.h
 *
 *  Created on: Feb 8, 2009
 *      Author: bharath
 */

#ifndef TSHEADERPARSE_H_
#define TSHEADERPARSE_H_

#define TS_PACKET_LENGTH                        188
#define TS_PACKET_LENGTH_WITHOUT_HEADER         184
#define ADAPTATION_FIELD_CONTROL_MASK           0x30

/* ================================================== */
#ifdef TRACE_PARAM

/* ----- */
#if (TRACE_PARAM > 0)
#define ERROR               (TRACE_PARAM & 0x1)
#define WARNING             (TRACE_PARAM & 0x2)
#define DEBUG               (TRACE_PARAM & 0x4)
#define INFO                (TRACE_PARAM & 0x8)
#define TEST                (TRACE_PARAM & 0x10)
#else
#define ERROR               (0x1)
#define WARNING             (0x2)
#define DEBUG               (0x4)
#define INFO                (0x8)
#define TEST                (0x10)
#endif
/* ----- */

#else
#define ERROR               1
#define WARNING             0
#define DEBUG               0
#define INFO                1
#define TEST                0
#endif
/* ================================================== */

#if 1
#ifndef QUIET
#define PRINT_ARGS(param, rest...)              \
    printf("Hello\n");\
    printf(param, ##rest)
#else
#define PRINT_ARGS(param, rest...)
#endif

#if (ERROR == 1)
#define ERR_PRINT(param, rest...)               \
    printf("Hello!\n"); \
    printf(param, ##rest)
#else
#define ERR_PRINT(param, rest...)
#endif

#if (WARNING == 1)
#define WARN_PRINT(param, rest...)              printf(param, ##rest)
#else
#define WARN_PRINT(param, rest...)
#endif

#if (DEBUG == 1)
#define DBG_PRINT(param, rest...)               printf(param, ##rest)
#else
#define DBG_PRINT(param, rest...)
#endif

#if (INFO == 1)
#define INFO_PRINT(param, rest...)              printf(param, ##rest)
#else
#define INFO_PRINT(param, rest...)
#endif

#if (TEST == 1)
#define TEST_PRINT(param, rest...)              printf(param, ##rest)
#else
#define TEST_PRINT(param, rest...)
#endif
#else
#define PRINT_ARGS(param, rest...)              printf("%s %s %d \"param\" \n",  __FILE__, __FUNCTION__, __LINE__, ##rest)
#define ERR_PRINT(param, rest...)              printf("%s %s %d ", __FILE__, __FUNCTION__, __LINE__, param, ##rest)
#define WARN_PRINT(param, rest...)              printf("%s %s %d ", __FILE__, __FUNCTION__, __LINE__, param, ##rest)
#define DBG_PRINT(param, rest...)              printf("%s %s %d ", __FILE__, __FUNCTION__, __LINE__, param, ##rest)
#define INFO_PRINT(param, rest...)              printf("%s %s %d ", __FILE__, __FUNCTION__, __LINE__, param, ##rest)
#define TEST_PRINT(param, rest...)              printf("%s %s %d ", __FILE__, __FUNCTION__, __LINE__, param, ##rest)
#endif
/*
 * \enum    : E_tsParseErrorCode_t
 * \brief   : Contains error code for parsing ts packet
 */
typedef enum E_tsParseErrorCodeTag
{
    E_TS_HEADER_PARSE_ERR_NONE = 0,
    E_TS_HEADER_PARSE_ERR_INPUT_PARAMETERS,
    E_TS_HEADER_PARSE_ERR_SYNC_BYTE,
    E_TS_HEADER_PARSE_ERR_READING_FROM_FILE,
    E_TS_HEADER_PARSE_ERR_EOF_REACHED,
}E_tsParseErrorCode_t;

/*
 * \struct  : S_tsPacketHeader_t
 * \brief   : Used to store information extracted from TS Packet Header
 */
typedef struct S_tsPacketHeaderTag
{
    int s32_synchronizationByte;
    int s32_transportErrorIndicator;
    int s32_payloadUnitStartIndicator;
    int s32_transportPriority;
    int s32_packetId;
    int s32_transportScramblingControl;
    int s32_doesPayloadFieldExist;
    int s32_doesAdaptationFieldExist;
    int s32_adaptationFieldLength;
    int s32_payloadFieldLength;
    int s32_continuityCounter;
}S_tsPacketHeader_t;

/*
 * \struct  : S_AdaptationOptionField_t
 * \brief   : Used to store information extracted from the optional elements of Adaptation Field
 */
typedef struct S_AdaptationOptionFieldTag
{
    long long int   s64_pcrBase;
    int             s32_pcrExtension;
    long long int   s64_opcrBase;
    int             s32_opcrExtension;
    int             s32_spliceCountDown;
    int             s32_privateDataLength;
}S_AdaptationOptionField_t;

/*
 * \struct  : S_adaptationField_t
 * \brief   : Used to store information extracted from adaptation field of a TS packet
 */
typedef struct S_adaptationFieldTag
{
    unsigned int                u32_discontinuityIndicator;
    unsigned int                u32_randomAccessIndicator;
    unsigned int                u32_elementaryStreamPriorityIndicator;
    unsigned int                u32_pcrFlag;
    unsigned int                u32_opcrFlag;
    unsigned int                u32_splicingPointFlag;
    unsigned int                u32_transportPrivateDataFlag;
    unsigned int                u32_adaptationFieldExtensionFlag;
    unsigned int                u32_offset;
    S_AdaptationOptionField_t   s_optionField;
}S_adaptationField_t;

/*
 * \struct  : S_pesOptionalPacketHeader_t
 * \brief   : Used to stre information about the optional elements in a PES packet
 */
typedef struct
{
    int s32_fixedBits;
    int s32_pesScramblingControl;
    int s32_pesPriority;
    int s32_dataAlignmentIndicator;
    int s32_originalCopyFlag;
}S_pesOptionalPacketHeader_t;

/*
 * \struct  : S_pesPacketHeader_t
 * \brief   : Used to store information about PES header
 */
typedef struct S_pesPacketHeaderTag
{
    int s32_pesPacketStartCodePrefix;
    int s32_streamId;
    int s32_pesPacketLength;
}S_pesPacketHeader_t;

/*
 * \struct  : S_pat_t
 * \brief   : Object to Store PAT information
 */
typedef struct S_patTag
{
    unsigned int        u32_tableId;
    unsigned int        u32_sectionSyntaxIndicator;
    unsigned int        u32_sectionLength;
    unsigned int        u32_transportStreamId;
    unsigned int        u32_versionNumber;
    unsigned int        u32_currentNextIndicator;
    unsigned int        u32_sectionNumber;
    unsigned int        u32_lastSectionNumber;
    unsigned int        u32_numberOfPrograms;
    unsigned int        a_u32_programNumber[256];
    unsigned int        a_u32_networkPid[256];
    unsigned int        a_u32_programMapPid[256];
    unsigned int        u32_crc32;
}S_pat_t;

/*
 * \struct  : S_pmt_t
 * \brief   : Object to Store PMT information
 */
typedef struct S_pmtTag
{
    unsigned int u32_tableId;
    unsigned int u32_sectionSyntaxIndicator;
    unsigned int u32_sectionLength;
    unsigned int u32_programNumber;
    unsigned int u32_versionNumber;
    unsigned int u32_currentNextIndicator;
    unsigned int u32_sectionNumber;
    unsigned int u32_lastSectionNumber;
    unsigned int u32_crc32;
    unsigned int u32_calcCrc32;
    unsigned int u32_codedLength;
    unsigned int u32_pcrPid;
    unsigned int u32_programInfoLength;
    unsigned int a_u32_streamType[256];
    unsigned int a_u32_elementaryPid[256];
    unsigned int u32_numberOfStreams;
}S_pmt_t;

/* Finds next TS Packet */
E_tsParseErrorCode_t find_next_ts_packet(FILE **filePointer, int *p_s32_tsskip);

/* Parses TS Packet Header */
E_tsParseErrorCode_t transport_packet(S_tsPacketHeader_t *ts_packet, unsigned char **pp_u8_buffer);
#endif /* TSHEADERPARSE_H_ */
