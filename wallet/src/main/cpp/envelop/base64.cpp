#include "base64.h"
#include <string.h>


std::string Base64::Encode(const unsigned char* str, int bytes) {
    int num = 0, bin = 0, i;
    std::string _encode_result;
    const unsigned char* current;
    current = str;
    while (bytes > 2) {
        _encode_result += _base64_table[current[0] >> 2];
        _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
        _encode_result += _base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
        _encode_result += _base64_table[current[2] & 0x3f];

        current += 3;
        bytes -= 3;
    }
    if (bytes > 0)
    {
        _encode_result += _base64_table[current[0] >> 2];
        if (bytes % 3 == 1) {
            _encode_result += _base64_table[(current[0] & 0x03) << 4];
            _encode_result += "==";
        }
        else if (bytes % 3 == 2) {
            _encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
            _encode_result += _base64_table[(current[1] & 0x0f) << 2];
            _encode_result += "=";
        }
    }
    return _encode_result;
}


std::string Base64::Decode(const char* str, int length) {

    const char DecodeTable[] =
            {
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-1), static_cast<char>(-1), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-1), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-1), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), 62, static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), 63,
                    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2),  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
                    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2),
                    static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2), static_cast<char>(-2)
            };
    int bin = 0, i = 0, pos = 0;
    std::string _decode_result;
    const char* current = str;
    char ch;
    while ((ch = *current++) != '\0' && length-- > 0)
    {
        if (ch == base64_pad) { 
           
            if (*current != '=' && (i % 4) == 1) {
                return NULL;
            }
            continue;
        }
        ch = DecodeTable[ch];
   
        if (ch < 0) { /* a space or some other separator character, we simply skip over */
            continue;
        }
        switch (i % 4)
        {
        case 0:
            bin = ch << 2;
            break;
        case 1:
            bin |= ch >> 4;
            _decode_result += bin;
            bin = (ch & 0x0f) << 4;
            break;
        case 2:
            bin |= ch >> 2;
            _decode_result += bin;
            bin = (ch & 0x03) << 6;
            break;
        case 3:
            bin |= ch;
            _decode_result += bin;
            break;
        }
        i++;
    }
    return _decode_result;
}

char * toBase64(const char * src,int size){
    Base64 base_;
    std::string base_ret=base_.Encode((const unsigned char *)src, size);
    char * buffer=(char *)malloc(base_ret.size()+1);
    buffer[base_ret.size()]=0;
    memcpy(buffer, base_ret.c_str(), base_ret.size());
    return buffer;

}
char * toBase64(const std::string & str){
    Base64 base_;
    std::string base_ret=base_.Encode((const unsigned char *)str.c_str(), str.size());
    char * buffer=(char *)malloc(base_ret.size()+1);
    buffer[base_ret.size()]=0;
    memcpy(buffer, base_ret.c_str(), base_ret.size());
    return buffer;
}

std::string FromBase64(const char * str,int size){
    Base64 base_;
    std::string ret_=base_.Decode(str, size);
    return ret_;
}

std::string FromBase64(const std::string & str){
    Base64 base_;
    std::string ret_=base_.Decode(str.c_str(), str.size());
    return ret_;
}
