#include "cutility.h"

static const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";


string CUtility::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = static_cast<unsigned char>(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
            char_array_4[2] = static_cast<unsigned char>(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i <4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = static_cast<unsigned char>((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = static_cast<unsigned char>((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}

string CUtility::RSAEncrypt(string data) {
    const char* pubkey = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC2v3F2OIZWpbI05cc4pwGY/jnw\nlCZMdo5zMKSq1MxNoTh3hXhm5txkRt4ZQFqdS485zxissUz4ukAebOguolXUrtXE\nI1lxJEDd4CmidTdiK1zxE6vEN955uZQkSF7hBJ6EvoLzNom/Vcnn66zqS506e7wH\nKIDKDJb4K8yHbSqHKQIDAQAB\n-----END PUBLIC KEY-----\n";

    string strRet = "";
    BIO* bio = BIO_new(BIO_s_mem());
    BIO_puts(bio, pubkey);
    RSA* rsa = nullptr;
    EVP_PKEY* evp_key = nullptr;
    evp_key = PEM_read_bio_PUBKEY(bio, &evp_key, nullptr, nullptr);
    rsa = EVP_PKEY_get1_RSA(evp_key);
    if (!rsa) {
        return "";
    }

    int nLen = RSA_size(rsa);
    char* pEncode = new char[nLen + 1];
    int ret = RSA_public_encrypt(static_cast<int>(data.length()), reinterpret_cast<const unsigned char*>(data.c_str()),
        reinterpret_cast<unsigned char*>(pEncode), rsa, RSA_PKCS1_PADDING);
    if (ret >= 0){
        strRet = base64_encode(reinterpret_cast<unsigned char*>(pEncode), static_cast<unsigned int>(nLen));
        //cout << "\n\n" << strRet  << endl << endl << endl;
    }
    delete[] pEncode;
    RSA_free(rsa);
    BIO_free(bio);

    CRYPTO_cleanup_all_ex_data();
    return strRet;
}
