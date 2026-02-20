#include "DataPublicationManager.h"
#include <boost/json.hpp>
#include <fstream>
#include <sstream>

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
    parser.ConvertJsonArrayToUserInfo(arrUserInfo, m_lstUserInfo);


    return true;
}

bool DataPublicationManager::SaveUserInfoFile() const
{
    boost::json::array arr;
    UserInfoParser parser;
    parser.ConvertUserInfoToJsonArray(m_lstUserInfo, arr);

    std::ofstream ofs;
    ofs.open("_userinfo.json");

    if(ofs.fail())
    {
        return false;
    }

    std::string strUserInfo = boost::json::serialize(arr);
    ofs << strUserInfo;
    ofs.close();

    return true;
}

DataPublicationManagerError DataPublicationManager::AddUser(const std::string &name, const std::string &passwd) noexcept
{
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
