#ifndef CUTILITY_H
#define CUTILITY_H

#include "openssl/err.h"
#include "openssl/pem.h"
#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include <string>
using std::string;

class CUtility{
    CUtility(){}
public:
    static string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    static string RSAEncrypt(string data);
};



#endif // CUTILITY_H
