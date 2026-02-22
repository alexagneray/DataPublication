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
    std::ifstream ifs(KeyFilename);
    if(!ifs.fail())
    {
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);

        std::basic_string_view<CryptoPP::byte> strKey(key.BytePtr(),key.SizeInBytes());
        std::basic_string_view<CryptoPP::byte> strIv(iv.BytePtr(),iv.SizeInBytes());

        /**
         * TODO : implémenter le chargement d'un fichier de clé d'encodage et fichier userinfo encodé
         */

        // std::basic_string<unsigned char> strKey;
        // std::string strIv;
        ifs >> strKey >> strIv;
        // key.Assign(reinterpret_cast<const CryptoPP::byte*>(strKey.c_str()), strKey.length());

        // encoder.SetKey()
    }
    
    
    ofs << strUserInfo;
    ofs.close();

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
