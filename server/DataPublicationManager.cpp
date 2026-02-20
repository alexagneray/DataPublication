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



void DataPublicationManager::Run() noexcept
{
    LoadUserInfoFile();
}
