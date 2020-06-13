#ifndef CBASE64CODEC_H
#define CBASE64CODEC_H

#include <string>

class CBase64Codec
{
private:
    CBase64Codec();

    static inline bool IsBase64(const char c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

    static void Byte3To4(const unsigned char (&buffer_3)[3], unsigned char (&buffer_4)[4]);
    static void Byte4To3(unsigned char (&buffer_4)[4], unsigned char (&buffer_3)[3]);

public:
    static std::string Encode(const char *szData,
                              unsigned int nLen);

    static std::string Decode(std::string const &sEncodeText);

private:
    static const std::string Base64EncodeMap;
};

#endif // CBASE64CODEC_H
