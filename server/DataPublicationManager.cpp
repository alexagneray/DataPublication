#include "DataPublicationManager.h"
#include <boost/json.hpp>
#include <fstream>
#include <sstream>

bool DataPublicationManager::LoadUserInfoFile()
{
    /**
     * TODO : chargement du fichier json pour update m_lstUserInfo
     */
    std::ifstream ifs;
    ifs.open("_userinfo.json");

    if(ifs.fail())
    {
        return false;
    }

    boost::json::array arrUserInfo;
    
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string strFileContent = ss.str();

    try
    {
        arrUserInfo = boost::json::parse(strFileContent).as_array();
    }
    catch(const std::exception& e)
    {
        return false;
    }


    return true;
}

bool DataPublicationManager::SaveUserInfoFile() const
{
    /**
     * TODO : enregistrement de m_lstUserInfo dans un fichier json
     */
    return false;
}



void DataPublicationManager::Run() noexcept
{
    LoadUserInfoFile();
}
