#include "CJpegHelper.h"   


CJpegHelper::~CJpegHelper(void)
{
    delete[]buffer;
}

int CJpegHelper::ReadImage()
{
    FILE* filejpeg;
    errno_t err = fopen_s(&filejpeg, file, "rb");
    if (err)
    {
        printf("%s:%i \n", file, err);
        return -1;
    }
    fseek(filejpeg, 0, SEEK_END);
    length = ftell(filejpeg);
    buffer = new unsigned char[length];
    fseek(filejpeg, 0, SEEK_SET);
    fread(buffer, length, 1, filejpeg);
    fclose(filejpeg);
    return GetSize(buffer, length);
}

int CJpegHelper::GetSize(unsigned char* buffer, long length)
{
    const unsigned char* EndPos = buffer + length;
    unsigned char* bufferTmp = buffer;
    unsigned char high;
    unsigned char low = 0xff;
    int result = -1;
    int pos = 0;
    if (*buffer++ != 0xff || *buffer++ != 0xd8)
    {
        return result;
    }
    while (EndPos > buffer && low != 0xDA)
    {
        do
        {
            high = *buffer++;
        } while (high != 0xff);
        do
        {
            low = *buffer++;
        } while (low == 0xff);
        switch (low)
        {
        case 0x00:
        case 0x01:
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
            break;
        case 0xC0:
            bufferTmp = buffer;
            pos = (*buffer++) << 8;
            pos += *buffer++;
            buffer++; 
            height = (*buffer++) << 8;
            height += *buffer++;
            weidth = (*buffer++) << 8;
            weidth += *buffer;
            result = 0;
            break;
        case 0xE0: 
            bufferTmp = buffer;
            pos = (*buffer++) << 8;
            pos += *buffer++;
            buffer = buffer + 7;       
            break;
        default:
            bufferTmp = buffer;
            pos = (*buffer++) << 8;
            pos += *buffer++;
            break;
        }
        buffer = bufferTmp + pos;
    }
    return result;
}