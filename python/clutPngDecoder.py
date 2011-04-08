#!/usr/bin/python


def decodeClutData(clutData):
    defaultClutSize = 128
    dataPosition = 0
    clutType = clutData[dataPosition] & 0x80
    depth = (clutData[dataPosition] & 0x60 ) >> 5
    regionFlag = clutData[dataPosition] & 0x10
    startEndFlag = clutData[dataPosition] & 0x8
    dataPosition += 1
    if regionFlag:
        dataPosition += 8
    if startEndFlag:
        if depth is 0:
            startIndex = clutData[dataPosition] >> 4
            endIndex = clutData[dataPosition] & 0xF
        else if depth is 1: 
            startIndex = clutData[dataPosition]
            dataPosition += 1
            endIndex = clutData[dataPosition]
        else if depth is 2: 
            startIndex = clutData[dataPosition] >> 4
            endIndex = clutData[dataPosition] & 0xF

    for x in range(startIndex, endIndex):
        if clutType is 0:
        else:

    int start_index=-1, end_index=-1;
    if(start_end_flag) {
        switch(depth) {

        case 0:
        {
            unsigned char start_end_index;
            start_end_index = data[iDataPos++];
            start_index = start_end_index >> 4;
            end_index = (start_end_index  & 0xF);
        }
        break;

        case 1:
        {
            start_index = data[iDataPos++];
            end_index  = data[iDataPos++];
        }
        break;

        case 2:
        {
            unsigned short start_end_index;
            start_end_index = *((unsigned short*)(data + iDataPos));
            iDataPos += 2;
            start_index = start_end_index;
            start_end_index = *((unsigned short*)(data + iDataPos));
            iDataPos += 2;
            end_index = start_end_index;
        }
        break;

        default:
        {
            // wired case;
            return;
        }
        break;

        } // end of switch
    }

    if(start_index > end_index)
        return;

    if(start_index > 128 )
        return;

    int clut_size = end_index + 1;
    if(clut_size < 128) {
        clut_size = 128;
    }

    doc->resizeCLUTTable(clut_size);

    int iCount = start_index;
    int error = 1;
    int iDataSize = m_data->size();
    int iColorInData = (iDataSize - iDataPos)/4;
    int iRequiredColors = (end_index - start_index + 1);
    if( iColorInData != iRequiredColors )
        return;

    while(iCount <= end_index )
    {
        ARIBColor clutColor;
        if(clut_type)
        {
            clutColor.R = data[iDataPos++];
            clutColor.G = data[iDataPos++];
            clutColor.B = data[iDataPos++];
        }
        else
        {
            unsigned char y,cb,cr;
            y = data[iDataPos++];
            cb = data[iDataPos++];
            cr = data[iDataPos++];

            int r1,g1,b1;
            convertYCrCbToRGb(y, cb, cr, r1, g1, b1);

            clutColor.R=r1;
            clutColor.G=g1;
            clutColor.B=b1;
        }

        clutColor.A = data[iDataPos++];
        doc->setCLUTColor(iCount, &clutColor);
        iCount++;
    }


def decodeClutFile(filePath):
    with open(filePath, "rb") as f:
        f.seek(0, 2)
        fileSize = f.tell()
        f.seek(0, 0)
        clutData = f.read()
        decodeClutData(clutData)        
