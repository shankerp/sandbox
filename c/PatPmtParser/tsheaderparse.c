/*
 * tsheaderparse.c
 *
 *  Created on: Feb 8, 2009
 *      Author: bharath
 */

#include <stdio.h>
#include <stdlib.h>
#include "tsheaderparse.h"

/*
 * \function        : find_next_ts_packet(FILE **filePointer)
 * \brief           : Finds the occurrence of a valid ts packet in the given file
 * \param[IN/OUT]   : filePointer
 *                    --> Pointer to the file where the valid occurrence of TS packet needs to be found
 * \param[OUT]      : p_s32_tsskip
 *                    --> TS skip to find the next ts packet
 * \return          : Success or Failure
 */
E_tsParseErrorCode_t find_next_ts_packet(FILE **filePointer, int *p_s32_tsskip)
{
    int s32_currentChar = 0;
    E_tsParseErrorCode_t e_errorCode = E_TS_HEADER_PARSE_ERR_NONE;
    int s32_byteCount = 0;
    *p_s32_tsskip = 0;
    while(1)
    {
        if (EOF == (s32_currentChar = fgetc(*filePointer)))
        {
            e_errorCode = E_TS_HEADER_PARSE_ERR_EOF_REACHED;
            goto END_find_next_ts_packet;
        }
        if (s32_currentChar != 0x47)
        {
            /* WARNING: Tricky logic used to find tsskip
             * Will fail if the current packet is damaged
             */
            continue;
        }
        while (EOF != (s32_currentChar = fgetc(*filePointer)))
        {
            (s32_byteCount) ++ ;
            if (s32_currentChar != 0x47)
            {
                /* WARNING: Tricky logic used to find tsskip
                 * Will fail if the current packet is damaged
                 */
                continue;
            }
            TEST_PRINT("byte count is %d\n", s32_byteCount);
            if (s32_byteCount < TS_PACKET_LENGTH)
            {
                continue;
            }
            TEST_PRINT("byte count is %d\n", s32_byteCount);
            break;
        }
        if (EOF == s32_currentChar)
        {
            e_errorCode = E_TS_HEADER_PARSE_ERR_READING_FROM_FILE;
            goto END_find_next_ts_packet;
        }
        if (-1 == fseek (*filePointer, (s32_byteCount - 1), SEEK_CUR))
        {
            perror("The error occurred in fseek was\n");
            e_errorCode = E_TS_HEADER_PARSE_ERR_READING_FROM_FILE;
            goto END_find_next_ts_packet;
        }
        if (EOF == (s32_currentChar = fgetc(*filePointer)))
        {
            e_errorCode = E_TS_HEADER_PARSE_ERR_EOF_REACHED;
            goto END_find_next_ts_packet;
        }
        if (s32_currentChar != 0x47)
        {
            fseek(*filePointer, -(s32_byteCount - 1), SEEK_CUR);
            *p_s32_tsskip = 0;
            continue;
        }
        fseek(*filePointer, -(2 * s32_byteCount + 1), SEEK_CUR);
        (*p_s32_tsskip) = s32_byteCount - TS_PACKET_LENGTH;
        {
            TEST_PRINT("Found TS Packet\nOffset value is %ld\n", ftell(*filePointer));
            goto END_find_next_ts_packet;
        }
    }
END_find_next_ts_packet:
    return e_errorCode;
}

/* \function        : transport_packet(S_tsPacketHeader_t *p_s_tsPacket, unsigned char **pp_u8_buffer)
 * \brief           : Parses the transport packet header information. Mainly used to get packet Id.
 * \param[IN/OUT]   : pp_u8_buffer
 *                    --> Buffer containing TS Data
 * \param[OUT]      : p_s_tsPacket
 *                    --> Pointer to the address where the ts information needs to be stored
 * \return          : Success or Failure
 */
E_tsParseErrorCode_t transport_packet(S_tsPacketHeader_t *p_s_tsPacket,
    unsigned char **pp_u8_buffer)
{
    E_tsParseErrorCode_t e_errorCode = E_TS_HEADER_PARSE_ERR_NONE;
    int s32_doesAdaptationFieldExist = 0;
    int s32_doesPayloadFieldExist = 0;
    int s32_packetId = 0;
    int s32_payloadUnitStartIndicator = 0;
    int s32_synchronizationByte = 0;
    int s32_transportErrorIndicator = 0;
    int s32_transportPriority = 0;
    int s32_transportScramblingControl = 0;
    int s32_adaptationFieldLength = 0;
    int s32_payloadFieldLength = TS_PACKET_LENGTH_WITHOUT_HEADER;
    int s32_continuityCounter = 0;

    DBG_PRINT("\n\n========================================\n\n");

    if (p_s_tsPacket == NULL || pp_u8_buffer == NULL || *pp_u8_buffer == NULL)
    {
        ERR_PRINT("Error in input parameters\n");
        e_errorCode = E_TS_HEADER_PARSE_ERR_INPUT_PARAMETERS;
        goto END_tsheaderparse;
    }
    if ((**pp_u8_buffer) != 0x47)
    {
        ERR_PRINT("Sync byte not found\n");
        e_errorCode = E_TS_HEADER_PARSE_ERR_SYNC_BYTE;
        goto END_tsheaderparse;
    }
    DBG_PRINT("The sync byte received is 0x%x\n", (**pp_u8_buffer));
    s32_synchronizationByte = 0x47;
    (*pp_u8_buffer)++;

    s32_transportErrorIndicator = ((**pp_u8_buffer) & 0x80) ? 1 : 0;
    DBG_PRINT("The Transport Error Indicator is %d\n", s32_transportErrorIndicator);
    s32_payloadUnitStartIndicator = ((**pp_u8_buffer) & 0x40) ? 1 : 0;
    DBG_PRINT("Payload Unit Start Indicator is %d\n", s32_payloadUnitStartIndicator);
    s32_transportPriority = ((**pp_u8_buffer) & 0x20) ? 1 : 0;
    DBG_PRINT("Transport Priority is %d\n", s32_transportPriority);
    /*
     * Extracting the packet Id
     */
    (**pp_u8_buffer) &= 0x1F;
    s32_packetId = (((**pp_u8_buffer) << 8) | *(*pp_u8_buffer + 1));
    DBG_PRINT("Packet Id is %d\n", s32_packetId);

    /*
     * Extracting the Scrambling Control
     */
    (*pp_u8_buffer) += 2;
    s32_transportScramblingControl = (((**pp_u8_buffer) & 0xC0) >> 6);
    DBG_PRINT("Transport Scrambling Control is %d\n", s32_transportScramblingControl);
    /*
     * Parsing the Adaptation Field and Payload Field exist flags by 'AND'ing with 00110000
     */
    s32_doesAdaptationFieldExist = ((**pp_u8_buffer) & 0x20) ? 1 : 0;
    DBG_PRINT("Adaptation Field Exist is %d\n", s32_doesAdaptationFieldExist);
    s32_doesPayloadFieldExist = ((**pp_u8_buffer) & 0x10) ? 1 : 0;
    DBG_PRINT("Payload Field Exist is %d\n", s32_doesPayloadFieldExist);
    /*
     * Parsing the continuity counter by 'AND'ing with 00001111
     */
    s32_continuityCounter = ((**pp_u8_buffer) & 0x0F);
    DBG_PRINT("Continuity Counter is %d\n", s32_continuityCounter);
    (*pp_u8_buffer)++;

#if (DEBUG == 1)
    DBG_PRINT("The current Scrambling Control detail is :\t");
    switch (s32_transportScramblingControl)
    {
        case 0x00:
            DBG_PRINT("Not Scrambled.\n");
            break;
        case 0x40:
            DBG_PRINT("Reserved for future use.\n");
            break;
        case 0x80:
            DBG_PRINT("Scrambled with even key.\n");
            break;
        case 0xC0:
            DBG_PRINT("Scrambled with odd key.\n");
            break;
        default:
            DBG_PRINT("Somewhere some error has occurred!\n");
            break;
    }
#endif

    if (s32_doesAdaptationFieldExist)
    {
        DBG_PRINT("The length of the Adaptation Field is %d bytes (0x%x)\n",
            (**pp_u8_buffer), (**pp_u8_buffer));
        s32_payloadFieldLength = TS_PACKET_LENGTH_WITHOUT_HEADER
            - (**pp_u8_buffer) - 1;
        s32_adaptationFieldLength = (**pp_u8_buffer);
        (*pp_u8_buffer) += (s32_adaptationFieldLength + 1);
    }

    END_tsheaderparse:
    p_s_tsPacket->s32_doesAdaptationFieldExist = s32_doesAdaptationFieldExist;
    p_s_tsPacket->s32_doesPayloadFieldExist = s32_doesPayloadFieldExist;
    p_s_tsPacket->s32_packetId = s32_packetId;
    p_s_tsPacket->s32_payloadUnitStartIndicator = s32_payloadUnitStartIndicator;
    p_s_tsPacket->s32_synchronizationByte = s32_synchronizationByte;
    p_s_tsPacket->s32_transportErrorIndicator = s32_transportErrorIndicator;
    p_s_tsPacket->s32_transportPriority = s32_transportPriority;
    p_s_tsPacket->s32_transportScramblingControl
        = s32_transportScramblingControl;
    p_s_tsPacket->s32_adaptationFieldLength = s32_adaptationFieldLength;
    p_s_tsPacket->s32_payloadFieldLength = s32_payloadFieldLength;
    p_s_tsPacket->s32_continuityCounter = s32_continuityCounter;
    return e_errorCode;
}

/* \function        : adaptation_field(S_adaptationField_t *p_s_adaptationField, unsigned char *p_u8_buffer)
 * \brief           : Parses the Adaptation Field in a TS packet
 * \param[IN]       : p_u8_buffer
 *                    --> Pointer to buffer containing adaptation field data
 * \param[OUT]      : p_s_adaptationField
 *                    --> Pointer to the address where the adaptation field info needs to be updated
 * \return          : NONE
 * \attention       : WARNING - FUNCTION NOT IMPLEMENTED/TESTED FULLY. USE IT AT YOUR OWN RISK.
 */
static void adaptation_field(S_adaptationField_t *p_s_adaptationField,
    unsigned char *p_u8_buffer)
{
    if (p_s_adaptationField == NULL || p_u8_buffer == NULL)
    {
        goto END_adaptation_field;
    }
    p_s_adaptationField->u32_discontinuityIndicator = ((*p_u8_buffer) >> 7);
    p_s_adaptationField->u32_randomAccessIndicator = (((*p_u8_buffer) & 0x40)
        >> 6);
    p_s_adaptationField->u32_elementaryStreamPriorityIndicator
        = (((*p_u8_buffer) & 0x20) >> 5);
    p_s_adaptationField->u32_pcrFlag = (((*p_u8_buffer) & 0x10) >> 4);
    p_s_adaptationField->u32_opcrFlag = (((*p_u8_buffer) & 0x08) >> 3);
    p_s_adaptationField->u32_splicingPointFlag = (((*p_u8_buffer) & 0x04) >> 2);
    p_s_adaptationField->u32_transportPrivateDataFlag
        = (((*p_u8_buffer) & 0x02) >> 1);
    p_s_adaptationField->u32_adaptationFieldExtensionFlag = ((*p_u8_buffer)
        & 0x01);

    (p_u8_buffer)++;

    if (p_s_adaptationField->u32_pcrFlag)
    {
        /*
         * Getting the 33 bit long program clock reference
         */
        p_s_adaptationField->s_optionField.s64_pcrBase
            = (((long long int) ((*p_u8_buffer) & 0xFF)) << 25);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_pcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 17);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_pcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 9);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_pcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 1);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_pcrBase
            |= (((long long int) ((*p_u8_buffer) & 0x80)) >> 7);
        /*
         * Next 6 bits are reserved. We need to skip. Last bit of the current byte
         *  and the next byte together constitute the pcrExtension
         */
        p_s_adaptationField->s_optionField.s32_pcrExtension
            = ((int) ((*p_u8_buffer) & 0x01) << 8);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s32_pcrExtension |= (*p_u8_buffer);
        (p_u8_buffer)++;
    }

    if (p_s_adaptationField->u32_opcrFlag)
    {
        /*
         * Getting the 33 bit long original program clock reference
         */
        p_s_adaptationField->s_optionField.s64_opcrBase
            = (((long long int) ((*p_u8_buffer) & 0xFF)) << 25);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_opcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 17);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_opcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 9);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_opcrBase
            |= (((long long int) ((*p_u8_buffer) & 0xFF)) << 1);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s64_opcrBase
            |= (((long long int) ((*p_u8_buffer) & 0x80)) >> 7);
        /*
         * Next 6 bits are reserved. We need to skip. Last bit of the current byte
         *  and the next byte together constitute the opcrExtension
         */
        p_s_adaptationField->s_optionField.s32_opcrExtension
            = ((int) ((*p_u8_buffer) & 0x01) << 8);
        (p_u8_buffer)++;
        p_s_adaptationField->s_optionField.s32_opcrExtension |= (*p_u8_buffer);
        (p_u8_buffer)++;
    }

    if (p_s_adaptationField->u32_splicingPointFlag)
    {
        p_s_adaptationField->s_optionField.s32_spliceCountDown = (*p_u8_buffer);
        (p_u8_buffer)++;
    }

    if (p_s_adaptationField->u32_transportPrivateDataFlag)
    {
        p_s_adaptationField->s_optionField.s32_privateDataLength
            = (*p_u8_buffer);
    }

    /*
     * TODO
     * Other fields yet to implement
     */
    END_adaptation_field:
    return;
}

/* \function        : program_association_section(S_tsPacketHeader_t s_tsPacket, S_pat_t *p_s_pat, unsigned char **pp_u8_buffer)
 * \brief           : Parses PAT Information and gets PMT
 * \param[IN]       : s_tsPacket
 *                    --> TS Packet Header Information
 * \param[IN/OUT]   : pp_u8_buffer
 *                    --> Buffer containing TS Data
 * \param[OUT]      : p_s_pat
 *                    --> Pointer to address where PAT information needs to be stored
 * \return          : Success or Failure
 * \attention       : Very poor error handling.
 *                    CRC Check not done. Behaviour of corrupted packets is unknown.
 */
int program_association_section(S_tsPacketHeader_t s_tsPacket, S_pat_t *p_s_pat, unsigned char **pp_u8_buffer)
{
    int s32_i = 0, s32_remainingBytes = 0;
    if (p_s_pat == NULL || *pp_u8_buffer == NULL || pp_u8_buffer == NULL)
    {
        return -1;
    }

    if (s_tsPacket.s32_payloadUnitStartIndicator == 0)
    {
        ERR_PRINT("Packet data is not at start. This is not a valid PAT packet.\n");
        return -1;
    }

    /*
     * Moving to the location given by the pointer
     */
    if ((**pp_u8_buffer) != 0)
    {
        (*pp_u8_buffer) += (**pp_u8_buffer);
    }
    else
    {
        (*pp_u8_buffer) ++;
    }
    /* Extracting the Table Id - 8 bits
     * For PAT this must be 0x00
     */
    p_s_pat->u32_tableId = (**pp_u8_buffer);
    DBG_PRINT("Table Id is %d\n", p_s_pat->u32_tableId);

    (*pp_u8_buffer)++;
    p_s_pat->u32_sectionSyntaxIndicator = ((**pp_u8_buffer) >> 7);
    DBG_PRINT("Section Syntax Indicator is %d\n", p_s_pat->u32_sectionSyntaxIndicator);
    if (!p_s_pat->u32_sectionSyntaxIndicator)
    {
        ERR_PRINT("Section syntax indicator is not set. Packet Error.\n");
        return -1;
    }
    /* Skip 3 unwanted bits.
     * Section Length - 12 bits.
     * Tells number of bytes following till CRC
     */
    p_s_pat->u32_sectionLength = (((unsigned int) (**pp_u8_buffer) & 0x03) << 8) | (*(*pp_u8_buffer + 1));
    DBG_PRINT("Section Length is %d\n", p_s_pat->u32_sectionLength);
    s32_remainingBytes = p_s_pat->u32_sectionLength;
    (*pp_u8_buffer) += 2;

    /* TS ID - 16 bits
     * Acts as a demultiplexing key
     */
    p_s_pat->u32_transportStreamId = (((unsigned int) (**pp_u8_buffer)) << 8);
    (*pp_u8_buffer)++;
    s32_remainingBytes --;
    p_s_pat->u32_transportStreamId |= (**pp_u8_buffer);
    DBG_PRINT("Transport Stream Id is %d\n", p_s_pat->u32_transportStreamId);
    (*pp_u8_buffer)++;
    s32_remainingBytes --;
    /* Version Number - 5 bits
     * Increases whenever PMT information changes
     */
    p_s_pat->u32_versionNumber = (((**pp_u8_buffer) >> 1) | 0x1F);
    DBG_PRINT("Version Number is %d\n", p_s_pat->u32_versionNumber);
    /*
     * If current next indicator is set, version number is for current packet
     * else version number is for next packet
     */
    p_s_pat->u32_currentNextIndicator = ((**pp_u8_buffer) & 0x01);
    DBG_PRINT("Current Next Indicator is %d\n", p_s_pat->u32_currentNextIndicator);
    (*pp_u8_buffer)++;
    s32_remainingBytes --;
    /* Section number - 8 bits
     * Increases with each additional section in PAT
     */
    p_s_pat->u32_sectionNumber = (**pp_u8_buffer);
    DBG_PRINT("Section Number is %d\n", p_s_pat->u32_sectionNumber);
    (*pp_u8_buffer)++;
    s32_remainingBytes --;
    /* Last Section Number - 8 bits
     * Maximum number of sections
     */
    p_s_pat->u32_lastSectionNumber = (**pp_u8_buffer);
    DBG_PRINT("Last Section Number is %d\n", p_s_pat->u32_lastSectionNumber);
    (*pp_u8_buffer)++;
    s32_remainingBytes --;

    /*
     * The Following for loop extracts the program number (Service Id)
     * and the corresponding network id or PMT pid
     */
    p_s_pat->u32_numberOfPrograms = 0;
    for (s32_i = 0; (s32_remainingBytes > 4); s32_i++)
    {
        p_s_pat->a_u32_programNumber[s32_i]
            = (((unsigned int) (**pp_u8_buffer)) << 8);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
        p_s_pat->a_u32_programNumber[s32_i] |= (**pp_u8_buffer);
        DBG_PRINT("Program Number is %d\n", p_s_pat->a_u32_programNumber[s32_i]);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
        if (p_s_pat->a_u32_programNumber[s32_i] == 0)
        {
            p_s_pat->a_u32_networkPid[s32_i]
                = ((((unsigned int) (**pp_u8_buffer)) & 0x1F) << 8);
            (*pp_u8_buffer)++;
            s32_remainingBytes --;
            p_s_pat->a_u32_networkPid[s32_i] |= (**pp_u8_buffer);
            DBG_PRINT("Network Pid is %d\n", p_s_pat->a_u32_networkPid[s32_i]);
        }
        else
        {
            /*
             * Extracting PMT Video
             * Packets containing these pids will contain info about audio, video and pcr pids
             */
            p_s_pat->a_u32_programMapPid[s32_i]
                = ((((unsigned int) (**pp_u8_buffer)) & 0x1F) << 8);
            (*pp_u8_buffer)++;
            s32_remainingBytes --;
            p_s_pat->a_u32_programMapPid[s32_i] |= (**pp_u8_buffer);
            DBG_PRINT("Program Map Pid is %d\n", p_s_pat->a_u32_programMapPid[s32_i]);
        }
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
    }
    p_s_pat->u32_numberOfPrograms = s32_i + 1;
    DBG_PRINT("Number of Programs = %d\n", s32_i + 1);
    /*
     * Extracting the 32 bit CRC number
     * WARNING : CRC Check not done
     */
    WARN_PRINT("CRC Check not done in PAT Packet.\n");
    p_s_pat->u32_crc32 = (((unsigned int) (**pp_u8_buffer)) << 24);
    (*pp_u8_buffer)++;
    p_s_pat->u32_crc32 |= (((unsigned int) (**pp_u8_buffer)) << 16);
    (*pp_u8_buffer)++;
    p_s_pat->u32_crc32 |= (((unsigned int) (**pp_u8_buffer)) << 8);
    (*pp_u8_buffer)++;
    p_s_pat->u32_crc32 |= ((unsigned int) (**pp_u8_buffer));
    (*pp_u8_buffer)++;
    DBG_PRINT("CRC value is %d\n", p_s_pat->u32_crc32);
    /*
     * TODO CRC check
     */
}

/* Parse PMT */
/* \function        : ts_program_map_section(S_tsPacketHeader_t s_tsPacket, S_pmt_t *p_s_pmt, unsigned char **pp_u8_buffer)
 * \brief           : Parses PMT and gets Audio, Video and PCR PIDs
 * \param[IN]       : s_tsPacket
 *                    --> TS Packet header Information
 * \param[IN/OUT]   : pp_u8_buffer
 *                    --> Buffer containing TS Data
 * \param[OUT]      : p_s_pmt
 *                    --> Pointer to address where the PMT Information needs to be stored
 * \return          : Success or Failure
 * \attention       : Very poor error handling.
 *                    CRC Check not done. Behaviour of corrupted packets is unknown.
 */
int ts_program_map_section(S_tsPacketHeader_t s_tsPacket, S_pmt_t *p_s_pmt, unsigned char **pp_u8_buffer)
{
    int s32_i, s32_remainingBytes = 0;
    int s32_esInfoLength = 0;
    if (s_tsPacket.s32_payloadUnitStartIndicator)
    {
        /*
         * Moving to the location given by the pointer
         */
        if ((**pp_u8_buffer) != 0)
        {
            (*pp_u8_buffer) += (**pp_u8_buffer);
        }
        else
        {
            (*pp_u8_buffer) ++;
        }

        /* Extracting the Table Id - 8 bits
         * For PMT this must be 0x02
         */
        p_s_pmt->u32_tableId = (**pp_u8_buffer);
        if (**pp_u8_buffer != 0x02)
        {
            ERR_PRINT("Warning - mismatched table Id for PMT.\n");
            return -1;
        }
        (*pp_u8_buffer)++;

        /* Section syntax indicator - 1 bit
         */
        p_s_pmt->u32_sectionSyntaxIndicator = (**pp_u8_buffer) >> 7;

        /* Skip 3 unwanted bits.
         * Section Length - 12 bits.
         * Tells number of bytes following till CRC
         */
        p_s_pmt->u32_sectionLength
            = ((((unsigned int) (**pp_u8_buffer)) & 0x0F) << 8);
        (*pp_u8_buffer)++;
        p_s_pmt->u32_sectionLength |= (**pp_u8_buffer);

        /* Section Length must not exceed 1021 */
        if (p_s_pmt->u32_sectionLength > 1021)
        {
            ERR_PRINT("Packet Error - Section Length exceeds the maximum value\n");
            return -1;
        }
        /* Update the remaining bytes with section length */
        s32_remainingBytes = p_s_pmt->u32_sectionLength;

        (*pp_u8_buffer)++;
        /* Extract the Program number to which this PMT is applicable. (Service Id) */
        p_s_pmt->u32_programNumber = (((unsigned int) (**pp_u8_buffer)) << 8);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
        p_s_pmt->u32_programNumber |= (**pp_u8_buffer);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;

        /* Version Number - 5 bits
         * Increases whenever PMT information changes
         */
        p_s_pmt->u32_versionNumber = ((((unsigned int) (**pp_u8_buffer)) & 0x3E) >> 1);

        /*
         * If current next indicator is set, version number is for current packet
         * else version number is for next packet
         */
        p_s_pmt->u32_currentNextIndicator = (((unsigned int) (**pp_u8_buffer)) & 0x01);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;

        /* Section number - 8 bits
         * Increases with each additional section in PAT
         */
        p_s_pmt->u32_sectionNumber = (**pp_u8_buffer);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;

        /* Last Section Number - 8 bits
         * Maximum number of sections
         */
        p_s_pmt->u32_lastSectionNumber = (**pp_u8_buffer);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;

        /* PCR PID - 13 bits
         * TS Packets containing PCR PID as the packet Id will containg PCR Fields
         */
        p_s_pmt->u32_pcrPid = ((((unsigned int) (**pp_u8_buffer)) & 0x1F) << 8);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
        p_s_pmt->u32_pcrPid |= (**pp_u8_buffer);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;

        /* Program Info Length - 12 bits
         * Gives the number of bytes of the descriptors following
         */
        p_s_pmt->u32_programInfoLength = ((((unsigned int) (**pp_u8_buffer))
            & 0x0F) << 8);
        (*pp_u8_buffer)++;
        s32_remainingBytes --;
        p_s_pmt->u32_programInfoLength |= (**pp_u8_buffer);

        /* WARNING:
         * Temporarily Skipping descriptor()
         */
        WARN_PRINT("Descriptor skipped\n");
        (*pp_u8_buffer) += (p_s_pmt->u32_programInfoLength + 1);
        s32_remainingBytes -= (p_s_pmt->u32_programInfoLength + 1);
        p_s_pmt->u32_numberOfStreams = 0;
        for (s32_i = 0; (s32_remainingBytes > 4); s32_i++)
        {
            /* Stream Type - May be Audio (or) Video (or) Data (or) Private */
            p_s_pmt->a_u32_streamType[s32_i] = (**pp_u8_buffer);
            (*pp_u8_buffer)++; s32_remainingBytes -- ;
            (**pp_u8_buffer) &= 0x1F;

            /* Stream Id - TS Packets with this id will contain corresponding information */
            p_s_pmt->a_u32_elementaryPid[s32_i] = ((**pp_u8_buffer) << 8);
            (*pp_u8_buffer)++; s32_remainingBytes -- ;
            p_s_pmt->a_u32_elementaryPid[s32_i] |= (**pp_u8_buffer);
            (*pp_u8_buffer)++; s32_remainingBytes -- ;

            /* ES Info Length - Gives the number of bytes of descriptors following */
            (**pp_u8_buffer) &= 0x0F;
            s32_esInfoLength =  ((**pp_u8_buffer) << 8);
            (*pp_u8_buffer)++; s32_remainingBytes -- ;
            s32_esInfoLength |= (**pp_u8_buffer);
            /* WARNING:
             * Skipping ES descriptors
             */
            (*pp_u8_buffer) += (s32_esInfoLength + 1); s32_remainingBytes -= (s32_esInfoLength + 1);
            p_s_pmt->u32_numberOfStreams++;
        }

        /* CRC CHECK NOT DONE */
        WARN_PRINT("CRC Check currently not implemented\n");
        p_s_pmt->u32_crc32 = (((unsigned int) (**pp_u8_buffer)) << 24);
        (*pp_u8_buffer)++;
        p_s_pmt->u32_crc32 |= (((unsigned int) (**pp_u8_buffer)) << 16);
        (*pp_u8_buffer)++;
        p_s_pmt->u32_crc32 |= (((unsigned int) (**pp_u8_buffer)) << 8);
        (*pp_u8_buffer)++;
        p_s_pmt->u32_crc32 |= ((unsigned int) (**pp_u8_buffer));
        (*pp_u8_buffer)++;
    }
    else
    {
        ERR_PRINT("Packet data is not at start. This is not a valid PMT packet.\n");
        return -1;
    }
}
#if 0
create_crc_table()
{
    int i, j;
    unsigned int byte, crc, mask;
    static unsigned int table[256];
    /* Set up the table, if necessary. */
    if (table[1] == 0)
    {
        for (byte = 0; byte <= 255; byte++)
        {
            crc = byte;
            for (j = 7; j >= 0; j--)
            { // Do eight times.
                mask = -(crc & 1);
                crc = (crc >> 1) ^ (0xEDB88320 & mask);
            }
            table[byte] = crc;
        }
    }
}

compute_crc()
{
    i = 0;
    crc = 0xFFFFFFFF;
    while (message[i] != 0)
    {
        byte = message[i]; // Get next byte.
        crc = (crc >> 8) ^ table[(crc ^ byte) & 0xFF];
        i = i + 1;
    }
    return ~crc;
}
#endif
