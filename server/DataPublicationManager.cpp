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
    std::ifstream ifs;
    ifs.open("_userinfo.json");

    if(ifs.fail())
    {
        return false;
    }

    boost::json::array arrUserInfo;
    
    std::stringstream ss;
    ss << ifs.rdbuf();

    ifs.close();

    std::string strFileContent = ss.str();

    try
    {
        arrUserInfo = boost::json::parse(strFileContent).as_array();
    }
    catch(const std::exception& e)
    {
        return false;
    }

    UserInfoParser parser;

    std::lock_guard lockUserInfo(m_mutUserInfo);
    parser.ConvertJsonArrayToUserInfo(arrUserInfo, m_lstUserInfo);

    return true;
}

bool DataPublicationManager::SaveUserInfoFile()
{
    boost::json::array arr;
    UserInfoParser parser;

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

    if(ifs.fail())
    {
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
    }
    else
    {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        std::string strKey;
        ifs >> strKey;
        if(ifs.fail())
        {
            return false;
        }
        if(strKey.size() != CryptoPP::AES::DEFAULT_KEYLENGTH)
        {
            return false;
        }
        memcpy(key.BytePtr(), strKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
        encoder.SetKey(key);
    }

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

void DataPublicationManager::Run() noexcept
{
    LoadUserInfoFile();
}
