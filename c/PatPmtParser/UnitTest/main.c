/*
 * main.c
 *
 *  Created on: Feb 9, 2009
 *      Author: bharath
 */
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tsheaderparse.h"


int g_s32_patParsed = 0;
int g_s32_pmtParsed = 0;

//    "Stream Type = %d = %0.4x\n", s_pmt.a_u32_streamType[s32_dummyVariable], s_pmt.a_u32_streamType[s32_dummyVariable],
int main(int argc, char *argv[])
{
    S_tsPacketHeader_t s_tsPacket;
    FILE *p_s_inputFilePtr;
    E_tsParseErrorCode_t e_errorCode;
    int s32_bytesRead, s32_dummyVariable = 0, s32_defaultServiceId = 0;
    long long int s64_sizeOfFile = 0;
    int s32_tsPacketCount = 0;
    unsigned char a_u8_buffer[TS_PACKET_LENGTH];
    unsigned char *p_u8_bufPtr = a_u8_buffer;
    S_pat_t s_pat;
    S_pmt_t s_pmt;
    int s32_pmtPid = -1;
    int s32_audioPid = 0x1FFF;
    int s32_videoPid = 0x1FFF;
    int s32_pcrPid = 0x1FFF;
    int s32_tsskip = 0;
    int s32_discontinuityCount = 0;

    if (argc != 2)
    {
        PRINT_ARGS("Usage : <exe> <input tsfile> \n");
        exit(0);
    }

    p_s_inputFilePtr = fopen(argv[1], "rb");

    if (p_s_inputFilePtr == NULL)
    {
        ERR_PRINT("Error opening file\n");
        perror("");
        return -1;
    }

    if (-1 != fseek(p_s_inputFilePtr, 0, SEEK_END))
    {
        s64_sizeOfFile = ftell(p_s_inputFilePtr);
        fseek(p_s_inputFilePtr, 0, SEEK_SET);
        DBG_PRINT("Size of File = %lld\n", (s64_sizeOfFile /(1024 * 1024)));
    }

    /* Finding the location of valid ts packet header */
    e_errorCode = find_next_ts_packet(&p_s_inputFilePtr, &s32_tsskip);
    if (e_errorCode != E_TS_HEADER_PARSE_ERR_NONE)
    {
        ERR_PRINT("Error in parsing\n");
        return -1;
    }

    while (s32_bytesRead = fread(a_u8_buffer, 1, (TS_PACKET_LENGTH + s32_tsskip), p_s_inputFilePtr))
    {
        DBG_PRINT("%0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x\n", p_u8_bufPtr[0], p_u8_bufPtr[1], p_u8_bufPtr[2], p_u8_bufPtr[3], p_u8_bufPtr[4], p_u8_bufPtr[5], p_u8_bufPtr[6], p_u8_bufPtr[7]);

        if (p_u8_bufPtr[0] != 0x47)
        {
            p_u8_bufPtr += s32_tsskip ;
        }

        e_errorCode = transport_packet(&s_tsPacket, &p_u8_bufPtr);

        s32_tsPacketCount ++;

        if (e_errorCode != E_TS_HEADER_PARSE_ERR_NONE)
        {
            ERR_PRINT("Packet discontinuity received at count %d\n", s32_tsPacketCount);
            s32_discontinuityCount ++ ;

            if (s32_discontinuityCount > 5)
            {
                ERR_PRINT("This stream is corrupted. Cannot proceed further...\n");
                return -1;
            }
            continue;
        }

        if (s_tsPacket.s32_packetId == 0)
        {
            DBG_PRINT("%0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x %0.2x\n", p_u8_bufPtr[0], p_u8_bufPtr[1], p_u8_bufPtr[2], p_u8_bufPtr[3], p_u8_bufPtr[4], p_u8_bufPtr[5], p_u8_bufPtr[6], p_u8_bufPtr[7]);

            program_association_section(s_tsPacket, &s_pat, &p_u8_bufPtr);

            INFO_PRINT("Following are the service id's found. Please select one among the following:\n");
            INFO_PRINT("If you are unsure, please press 'd' for default\n");

            for (s32_dummyVariable = 0; s32_dummyVariable < s_pat.u32_numberOfPrograms ; s32_dummyVariable++)
            {
                if(s_pat.a_u32_programNumber[s32_dummyVariable] != 0)
                {
                    INFO_PRINT("%d. %d\n",(s32_dummyVariable + 1), s_pat.a_u32_programNumber[s32_dummyVariable]);
                    if ((s32_defaultServiceId == 0) && (s32_dummyVariable != 0))
                    {
                        s32_defaultServiceId = s32_dummyVariable;
                    }
                }
                else
                {
                    INFO_PRINT("%d. Invalid Service Id\n", (s32_dummyVariable + 1));
                }
            }

            if(scanf("%d", &s32_dummyVariable) <= 0)
            {
                s32_pmtPid = s_pat.a_u32_programMapPid[s32_defaultServiceId];
            }
            else
            {
                s32_pmtPid = s_pat.a_u32_programMapPid[s32_dummyVariable - 1];
            }

            INFO_PRINT("==============================================\n");
            INFO_PRINT("TS SKIP : %-5d [0x%02x]\n", s32_tsskip, s32_tsskip);
            INFO_PRINT("TS ID   : %-5d [0x%02x]\n", s_pat.u32_transportStreamId, s_pat.u32_transportStreamId);
            INFO_PRINT("PMT PID : %-5d [0x%02x]\n", s32_pmtPid, s32_pmtPid);
            DBG_PRINT("Byte count for pat = %d = 0x%0.8x\n", ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount), ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount));

            g_s32_patParsed = 1;
        }

        if (s_tsPacket.s32_packetId == s32_pmtPid)
        {
            DBG_PRINT("Found PMT Packet at count %d = 0x%0.8x\n", ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount)-TS_PACKET_LENGTH, ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount)-TS_PACKET_LENGTH);

            if (-1 == ts_program_map_section(s_tsPacket, &s_pmt, &p_u8_bufPtr))
            {
                continue;
            }

            s32_pcrPid = (int)s_pmt.u32_pcrPid ;
            INFO_PRINT("PCR PID : %-5d [0x%02x]\n", s32_pcrPid, s32_pcrPid);
            INFO_PRINT("Following are the Streams found :\n");

            for (s32_dummyVariable = 0; s32_dummyVariable < s_pmt.u32_numberOfStreams ; s32_dummyVariable ++)
            {
                DBG_PRINT("%d.\t", (s32_dummyVariable + 1));

                switch(s_pmt.a_u32_streamType[s32_dummyVariable])
                {
                    case 0x00:
                        DBG_PRINT("Stream Type : ITU-T | ISO/IEC Reserved stream - 未定義 with ");
                        break;
                    case 0x01:
                        s32_videoPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Video PID : %d [0x%02x] ; Video Stream Type = 0x%02x : ", s32_videoPid, s32_videoPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ISO/IEC 11172 VIDEO (MPEG 1 Video) - 映像\n");
                        break;
                    case 0x02:
                        s32_videoPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Video PID : %d [0x%02x] ; Video Stream Type = 0x%02x : ", s32_videoPid, s32_videoPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ITU-T Rec. H.262 | ISO/IEC 13818-2 VIDEO | ISO/IEC 11172-2 constrained parameter video - 映像\n");
                        break;
                    case 0x03:
                        s32_audioPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Audio PID : %d [0x%02x] ; Audio Stream Type = 0x%02x : ", s32_audioPid, s32_audioPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ISO/IEC 11172 (MPEG 1) AUDIO\n");
                        break;
                    case 0x04:
                        s32_audioPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Audio PID : %d [0x%02x] ; Audio Stream Type = 0x%02x : ", s32_audioPid, s32_audioPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ISO/IEC 13818-3 (MPEG 2) AUDIO\n");
                        break;
                    case 0x05:
                        s32_videoPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Video PID : %d [0x%02x] ; Video Stream Type = 0x%02x : ", s32_videoPid, s32_videoPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ITU-T Rec. H.222.0 | ISO/IEC 13818-1 (MPEG 2) VIDEO | private_sections - 映像\n");
                        break;
                    case 0x06:
                        DBG_PRINT("ITU-T Rec. H.222.0 | ISO/IEC 13818-1 PES packets containing private data with ");
                        break;
                    case 0x07:
                        DBG_PRINT("ISO/IEC 13522 MHEG with ");
                        break;
                    case 0x08:
                        DBG_PRINT("ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Annex A | DSM CC with ");
                        break;
                    case 0x09:
                        DBG_PRINT("ITU-T Rec. H.222.1 with ");
                        break;
                    case 0x0A:
                        DBG_PRINT("ISO/IEC 13818-6 type A with ");
                        break;
                    case 0x0B:
                        DBG_PRINT("ISO/IEC 13818-6 type B with ");
                        break;
                    case 0x0C:
                        DBG_PRINT("ISO/IEC 13818-6 type C with ");
                        break;
                    case 0x0D:
                        DBG_PRINT("ISO/IEC 13818-6 type D with ");
                        break;
                    case 0x0E:
                        DBG_PRINT("ISO/IEC 13818-1 auxiliary with ");
                        break;
                    case 0x0F:
                        s32_audioPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Audio PID : %d [0x%02x] ; Audio Stream Type = 0x%02x : ", s32_audioPid, s32_audioPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ISO/IEC 13818-7 Audio with ADTS transport syntax\n");
                        break;
                    case 0x10:
                        DBG_PRINT("ISO/IEC 14496-2 Visual with ");
                        break;
                    case 0x11:
                        s32_audioPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Audio PID : %d [0x%02x] ; Audio Stream Type = 0x%02x : ", s32_audioPid, s32_audioPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ISO/IEC 14496-3 Audio with the LATM transport syntax as defined in ISO/IEC 14496-3 / AMD 1\n");
                        break;
                    case 0x12:
                        DBG_PRINT("ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in PES packets with ");
                        break;
                    case 0x13:
                        DBG_PRINT("ISO/IEC 14496-1 SL-packetized stream or FlexMux stream carried in ISO/IEC14496_sections. with ");
                        break;
                    case 0x14:
                        DBG_PRINT("ISO/IEC 13818-6 Synchronized Download Protocol with ");
                        break;
                    case 0x15:
                        DBG_PRINT("Metadata carried in PES packets with ");
                        break;
                    case 0x16:
                        DBG_PRINT("Metadata carried in metadata_sections with ");
                        break;
                    case 0x17:
                        DBG_PRINT("Metadata carried in ISO/IEC 13818-6 Data Carousel with ");
                        break;
                    case 0x18:
                        DBG_PRINT("Metadata carried in ISO/IEC 13818-6 Object Carousel with ");
                        break;
                    case 0x19:
                        DBG_PRINT("Metadata carried in ISO/IEC 13818-6 Synchronized Download Protocol with ");
                        break;
                    case 0x1A:
                        DBG_PRINT("IPMP ストリーム（ISO/IEC 13818-11 で規定される MPEG-2 IPMP）with ");
                        break;
                    case 0x1B:
                        s32_videoPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Video PID : %d [0x%02x] ; Video Stream Type = 0x%02x : ", s32_videoPid, s32_videoPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("ITU-T Rec. H.264 | ISO/IEC 14496-10 Video\n");
                        break;
                    case 0x1C:
                        DBG_PRINT("ISO/IEC 14496-3 音声(DST,ALS,SLS など何ら 追加のトランスポート構造を使用しないもの) with ");
                        break;
                    case 0x1D:
                        DBG_PRINT("ISO/IEC 14496-17 テキスト with ");
                        break;
                    case 0x1E:
                        DBG_PRINT("ISO/IEC 23002-3 で規定される補助映像ストリーム with ");
                        break;
                    case 0x7F:
                        DBG_PRINT("IPMP stream with ");
                        break;
                    case 0x81:
                        s32_audioPid = s_pmt.a_u32_elementaryPid[s32_dummyVariable];
                        INFO_PRINT("  Audio PID : %d [0x%02x] ; Audio Stream Type = 0x%02x : ", s32_audioPid, s32_audioPid, s_pmt.a_u32_streamType[s32_dummyVariable]);
                        INFO_PRINT("AC-3\n");
                        break;
                    case 0xFF:
                        DBG_PRINT("Not defined with ");
                        break;
                    default:
                        if(s_pmt.a_u32_streamType[s32_dummyVariable] <= 0x7F)
                        {
                            DBG_PRINT("ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved 未定義 with ");
                        }
                        else
                        {
                            DBG_PRINT("Stream Type: %d [%0.4x]\n", s_pmt.a_u32_streamType[s32_dummyVariable], s_pmt.a_u32_streamType[s32_dummyVariable]);
                            DBG_PRINT("Private User Stream with ");
                        }
                        break;
                }

                DBG_PRINT("Stream Id = %d = 0x%0.2x\n", s_pmt.a_u32_elementaryPid[s32_dummyVariable],s_pmt.a_u32_elementaryPid[s32_dummyVariable]);
            }
            DBG_PRINT(" ========================= \n\n");
            g_s32_pmtParsed = 1;
        }

        if (s_tsPacket.s32_packetId == s32_audioPid)
        {
            DBG_PRINT("Found an audio packet at location = 0x%0.8x\n", ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount) - TS_PACKET_LENGTH);
        }

        if (s_tsPacket.s32_packetId == s32_videoPid)
        {
            DBG_PRINT("Found a video packet at location = 0x%0.8x\n", ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount) - TS_PACKET_LENGTH);
        }

        if (s_tsPacket.s32_packetId == s32_pcrPid)
        {
            DBG_PRINT("Found a pcr packet at location = 0x%0.8x\n", ((TS_PACKET_LENGTH + s32_tsskip) * s32_tsPacketCount) - TS_PACKET_LENGTH);
        }

        p_u8_bufPtr = a_u8_buffer;

        if ((s32_bytesRead != (TS_PACKET_LENGTH + s32_tsskip)) || (g_s32_patParsed == 1 && g_s32_pmtParsed == 1))
        {
            break;
        }
    }

    if (s32_audioPid == 0x1FFF)
    {
        INFO_PRINT("  Audio Pid : %d [0x1FFF]\n");
    }
    if (s32_videoPid == 0x1FFF)
    {
        INFO_PRINT("  Video Pid : %d [0x1FFF]\n");
    }
    if (s32_pcrPid == 0x1FFF)
    {
        INFO_PRINT("  PCR Pid   : %d [0x1FFF]\n");
    }

    INFO_PRINT("==============================================\n\n");
}
