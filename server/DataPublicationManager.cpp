#include "DataPublicationManager.h"
#include "AESEncoder.h"
#include <boost/json.hpp>
#include <fstream>
#include <sstream>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

const std::string DataPublicationManager::UserInfoFilename = "userinfo.dpmbin";
const std::string DataPublicationManager::KeyFilename = "key.dpmbin";
const std::string DataPublicationManager::IvFilename = "iv.dpmbin";

bool DataPublicationManager::LoadUserInfoFile()
{

    // 1 - Chargement contenu userinfo
    std::ifstream ifs;
    ifs.open("_userinfo.json");
    if(ifs.fail())
    {
        return false;
    }

    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    std::string strFileContent = ss.str();
    ss.str("");
    ss.clear();

    // 2 - Chargement IV
    ifs.open(IvFilename);
    if(ifs.fail())
    {
        return false;
    }

    ss << ifs.rdbuf();
    ifs.close();
    std::string strIvFileContent = ss.str();
    ss.str("");
    ss.clear();
    
    // 3 - Chargement clé
    ifs.open(KeyFilename);
    if(ifs.fail())
    {
        return false;
    }
    ss << ifs.rdbuf();
    ifs.close();
    std::string strKeyFileContent = ss.str();
    ss.str("");
    ss.clear();

    // 4 - Conversion IV
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    memcpy(iv.BytePtr(), strIvFileContent.c_str(), CryptoPP::AES::BLOCKSIZE);

    // 5 - Conversion key
    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
    memcpy(key.BytePtr(), strKeyFileContent.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    // 6 - Décodage contenu du fichier userfile
    AESEncoder encoder;
    encoder.SetIv(iv);
    encoder.SetKey(key);
    std::string strFilePlainText;
    encoder.Decode(strFileContent, strFilePlainText);


    // 7 - Conversion du contenu de userfile en objet JSON
    boost::json::array arrUserInfo;
    try
    {
        arrUserInfo = boost::json::parse(strFilePlainText).as_array();
    }
    catch(const std::exception& e)
    {
        return false;
    }


    // 8 - Chargement dans lstUserInfo
    UserInfoParser parser;
    std::lock_guard lockUserInfo(m_mutUserInfo);
    m_lstUserInfo.clear();
    parser.ConvertJsonArrayToUserInfo(arrUserInfo, m_lstUserInfo);

    return true;
}

bool DataPublicationManager::SaveUserInfoFile()
{
    boost::json::array arr;
    UserInfoParser parser;

    // 1 - Conversion UserInfo -> objet JSON
    std::unique_lock lockUserInfo(m_mutUserInfo);
    parser.ConvertUserInfoToJsonArray(m_lstUserInfo, arr);
    lockUserInfo.unlock();

    std::ofstream ofs;
    ofs.open("_userinfo.json");

    if(ofs.fail())
    {
        return false;
    }

    std::string strUserInfo = boost::json::serialize(arr);

    AESEncoder encoder;
    std::string strEncoded;
    std::ifstream ifs(KeyFilename);

    // 2 - Génération d'une clé
    encoder.RegenKey();
    const CryptoPP::SecByteBlock& key = encoder.GetKey();
    std::ofstream ofsKey(KeyFilename);
    if(ofsKey.fail())
    {
        return false;
    }
    ofsKey.write(reinterpret_cast<const char*>(key.BytePtr()), key.SizeInBytes());
    if(ofsKey.fail())
    {
        return false;
    }

    // 3 - Génération nouvel IV + AES
    encoder.RegenIv();
    encoder.Encode(strUserInfo, strEncoded);


    ofs << strEncoded;

    const CryptoPP::SecByteBlock& iv = encoder.GetIv();
    std::ofstream ofsIv(IvFilename);

    if(ofsIv.fail())
    {
        return false;
    }

    ofsIv.write(reinterpret_cast<const char*>(iv.BytePtr()), iv.SizeInBytes());

    if(ofsIv.fail())
    {
        return false;
    }

    return true;
}

DataPublicationManagerError DataPublicationManager::AddUser(const std::string &name, const std::string &passwd) noexcept
{
    std::lock_guard lockUserInfo(m_mutUserInfo);
    auto it = std::find_if(m_lstUserInfo.begin(),
                m_lstUserInfo.end(),
                [&name](UserInfo& info) {return info._name==name;});
    if(it != m_lstUserInfo.end())
    {
        return DataPublicationManagerError::AlreadyExists;
    }

    UserInfo& newUser = m_lstUserInfo.emplace_back();
    newUser._name = name;
    newUser._passwd = passwd;
    
    
    return DataPublicationManagerError::Success;
}

DataPublicationManagerError DataPublicationManager::RemoveUser(const std::string &name) noexcept
{
    std::lock_guard lockUserInfo(m_mutUserInfo);
    auto it = std::find_if(m_lstUserInfo.begin(),
                m_lstUserInfo.end(),
                [&name](UserInfo& info) {return info._name==name;});
    if(it == m_lstUserInfo.end())
    {
        return DataPublicationManagerError::NotFound;
    }

    m_lstUserInfo.erase(it);

    return DataPublicationManagerError::Success;
}

DataPublicationManagerError DataPublicationManager::UpdatePassword(const std::string &name, const std::string &passwd) noexcept
{
    std::lock_guard lockUserInfo(m_mutUserInfo);
    auto it = std::find_if(m_lstUserInfo.begin(),
                m_lstUserInfo.end(),
                [&name](UserInfo& info) {return info._name==name;});
    if(it == m_lstUserInfo.end())
    {
        return DataPublicationManagerError::NotFound;
    }

    it->_passwd = passwd;

    return DataPublicationManagerError::Success;
}

bool DataPublicationManager::UserExists(const std::string &name) noexcept
{
    std::lock_guard lockUserInfo(m_mutUserInfo);
    auto it = std::find_if(m_lstUserInfo.begin(),
                m_lstUserInfo.end(),
                [&name](UserInfo& info) {return info._name==name;});
    return it != m_lstUserInfo.end();
}

bool DataPublicationManager::CheckPassword(const std::string &name, const std::string &passwd) noexcept
{
    std::lock_guard lockUserInfo(m_mutUserInfo);
    auto it = std::find_if(m_lstUserInfo.begin(),
                m_lstUserInfo.end(),
                [&name](UserInfo& info) {return info._name==name;});
    if(it == m_lstUserInfo.end())
    {
        return false;
    }
    return it->_passwd == passwd;
}

void DataPublicationManager::Run() noexcept
{
    LoadUserInfoFile();
}
