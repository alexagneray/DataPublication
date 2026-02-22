#include <cryptopp/rijndael.h>
#include <string>

class AESEncoder
{
private:
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv;
public:
    AESEncoder();
    AESEncoder(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
    void RegenKey();
    void RegenIv();
    void SetKey(const CryptoPP::SecByteBlock& key);
    void SetIv(const CryptoPP::SecByteBlock& iv);
    const CryptoPP::SecByteBlock GetKey() const;
    const CryptoPP::SecByteBlock GetIv() const;
    void Encode(const std::string& strPlainText, std::string& strEncoded);
    void Decode(const std::string& strEncoded, std::string& strPlainText);
};