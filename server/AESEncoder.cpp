#include "AESEncoder.h"
#include <assert.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

using namespace CryptoPP;
AESEncoder::AESEncoder()
{
    AutoSeededRandomPool prng;
    m_key.CleanNew(AES::DEFAULT_KEYLENGTH);
    m_iv.CleanNew(AES::BLOCKSIZE);
    prng.GenerateBlock(m_key, m_key.size());
    prng.GenerateBlock(m_iv, m_iv.size());
}
AESEncoder::AESEncoder(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) : m_key{key},
                                                                                m_iv{iv}
{
}
void AESEncoder::RegenKey()
{
    AutoSeededRandomPool prng;
    m_key.CleanNew(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock(m_key, m_key.size());
}
void AESEncoder::RegenIv()
{
    AutoSeededRandomPool prng;
    m_iv.CleanNew(AES::BLOCKSIZE);
    prng.GenerateBlock(m_iv, m_iv.size());
}
void AESEncoder::SetKey(const CryptoPP::SecByteBlock &key)
{
    m_key = key;

}
void AESEncoder::SetIv(const CryptoPP::SecByteBlock &iv)
{
     m_iv = iv;
}
void AESEncoder::Encode(const std::string &strPlainText, std::string &strEncoded)
{
    if(m_key.empty() || m_iv.empty())
    {
        AutoSeededRandomPool prng;
        m_key.CleanNew(AES::DEFAULT_KEYLENGTH);
        m_iv.CleanNew(AES::BLOCKSIZE);
        prng.GenerateBlock(m_key, m_key.size());
        prng.GenerateBlock(m_iv, m_iv.size());
    }


    try
    {
        CBC_Mode< AES >::Encryption e;
        e.SetKeyWithIV(m_key, m_key.size(), m_iv);

        StringSource s(strPlainText, true, 
            new StreamTransformationFilter(e,
                new StringSink(strEncoded)
            )
        );
    }
    catch(const Exception& e)
    {
        exit(1);
    }
}

void AESEncoder::Decode(const std::string &strEncoded, std::string &strPlainText)
{
    assert(m_key.size() == AES::DEFAULT_KEYLENGTH);
    assert(m_iv.size() == AES::BLOCKSIZE);

    try
    {
        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(m_key, m_key.size(), m_iv);

        StringSource s(strEncoded, true, 
            new StreamTransformationFilter(d,
                new StringSink(strPlainText)
            )
        );
    }
    catch(const Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
