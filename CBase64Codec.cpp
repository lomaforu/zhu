#include "CBase64Codec.h"

#include <iostream>
#include <fstream>
#include <malloc.h>
#include <cstring>

using namespace std;


static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                        "abcdefghijklmnopqrstuvwxyz"
                                        "0123456789+/";

static inline bool is_base64(const char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const char *bytes_to_encode,
                          unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                    ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                    ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = (char_array_3[2] & 0x3f);

            for (i = 0; i < 4; ++i) {
                ret += base64_chars[char_array_4[i]];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; ++j) {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
                ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
                ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = (char_array_3[2] & 0x3f);

        for (i = 0; i < 4; ++i) {
            ret += base64_chars[char_array_4[i]];
        }

        while (i++ < 3) {
            ret += '=';
        }
    }

    return ret;
}

std::string base64_decode(std::string const &encoded_string)
{
    int in_len = (int)encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;

    unsigned char char_array_4[4],char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') &&
           is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_];
        in_++;

        if (i == 4) {
            for (i = 0; i < 4; ++i) {
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            }

            char_array_3[0] = (char_array_4[0] << 2) +
                    ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) +
                    ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +
                    char_array_4[3];

            for (i = 0; i < 3; ++i) {
                ret += char_array_3[i];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; ++j) {
            char_array_4[j] = 0;
        }

        for (j = 0; j < 4; ++j) {
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        }

        char_array_3[0] = (char_array_4[0] << 2) +
                ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) +
                ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +
                char_array_4[3];

        for (i = 0; i < 3; ++i) {
            ret += char_array_3[i];
        }
    }

    return ret;
}


const std::string CBase64Codec::Base64EncodeMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "abcdefghijklmnopqrstuvwxyz"
                                    "0123456789+/";

void CBase64Codec::Byte3To4(const unsigned char (&buffer_3)[3], unsigned char (&buffer_4)[4])
{
    buffer_4[0] = (buffer_3[0] & 0xfc) >> 2;
    buffer_4[1] = ((buffer_3[0] & 0x03) << 4) + ((buffer_3[1] & 0xf0) >> 4);
    buffer_4[2] = ((buffer_3[1] & 0x0f) << 2) + ((buffer_3[2] & 0xc0) >> 6);
    buffer_4[3] = (buffer_3[2] & 0x3f);
}

void CBase64Codec::Byte4To3(unsigned char (&buffer_4)[4], unsigned char (&buffer_3)[3])
{
    for (int i = 0; i < 4; ++i) {
        buffer_4[i] = Base64EncodeMap.find(buffer_4[i]);
    }

    buffer_3[0] = (buffer_4[0] << 2) +
            ((buffer_4[1] & 0x30) >> 4);
    buffer_3[1] = ((buffer_4[1] & 0xf) << 4) +
            ((buffer_4[2] & 0x3c) >> 2);
    buffer_3[2] = ((buffer_4[2] & 0x3) << 6) +
            buffer_4[3];
}

string CBase64Codec::Encode(const char *szData, unsigned int nLen)
{
    std::string sResult = "";

    if (nLen != 0) {
        unsigned char buffer_3[3] = {0};
        unsigned char buffer_4[4] = {0};

        int i = 0;
        int j = 0;
        while (nLen--) {
            buffer_3[i++] = *(szData++);

            if (i == 3) {
                Byte3To4(buffer_3, buffer_4);

                for (i = 0; i < 4; ++i) {
                    sResult += Base64EncodeMap[buffer_4[i]];
                }

                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; ++j) {
                buffer_3[j] = '\0';
            }

            Byte3To4(buffer_3, buffer_4);

            for (i = 0; i < 4; ++i) {
                sResult += Base64EncodeMap[buffer_4[i]];
            }

            while (i++ < 3) {
                sResult += '=';
            }
        }
    }

    return sResult;
}

string CBase64Codec::Decode(const string &sEncodeText)
{
    string sResult = "";

    int nLen = (int)sEncodeText.size();
    int i = 0;
    int j = 0;
    int nIdx = 0;

    unsigned char buffer_4[4],buffer_3[3];

    while (nLen-- && (sEncodeText[nIdx] != '=') &&
           is_base64(sEncodeText[nIdx])) {
        buffer_4[i++] = sEncodeText[nIdx];
        nIdx++;

        if (i == 4) {
            Byte4To3(buffer_4, buffer_3);

            for (i = 0; i < 3; ++i) {
                sResult += buffer_3[i];
            }

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; ++j) {
            buffer_4[j] = 0;
        }

        Byte4To3(buffer_4, buffer_3);

        for (i = 0; i < 3; ++i) {
            sResult += buffer_3[i];
        }
    }

    return sResult;
}


void testBase64()
{
    string fileName = "//home//zyd//workfile//qt//build-QtConsole-Desktop_Qt_5_13_2_GCC_64bit-Debug//test.jpg";

    fstream f;
    f.open(fileName, ios::in | ios::binary);
    f.seekg(0, std::ios_base::end);
    std::streampos sp = f.tellg();

    int size = sp;

    char *buffer = (char *)malloc(sizeof(char) * size);
    f.seekg(0, std::ios_base::beg);
    f.read(buffer, size);

    cout << "file size:" << size << endl;

    string imgBase64 = CBase64Codec::Encode(buffer, size);
    cout << "img base64 encode size:" << imgBase64.size() << endl;

    string imgDecode64 = CBase64Codec::Decode(imgBase64);
    cout << "img decode size:" << imgDecode64.size() << endl;

    const char *p = imgDecode64.c_str();
    std::ofstream fout("./result.jpg",ios::out | ios::binary);

    if (!fout) {
        cout << "error" << endl;
    }
    else {
        cout << "Success!" << endl;
        fout.write(p, size);
    }

    f.close();
}
