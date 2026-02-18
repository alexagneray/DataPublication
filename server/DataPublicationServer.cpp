#include "DataPublicationServer.h"

DataPublicationError DataPublicationServer::AddDataList(const std::string &strPublisher, const std::string &strDlName) noexcept
{
    auto it = m_dlData.find(strDlName);
    
    if(it != m_dlData.end())
    {
        return DataPublicationError::AlreadyExists;
    }
    
    auto retData = m_dlData.emplace(std::make_pair(strDlName, std::map<std::string, VarType>()));

    if(!retData.second)
    {
        return DataPublicationError::AddingIssue;
    }

    auto retInfo = m_dlInfo.emplace(std::make_pair(strDlName, Info()));

    if(!retInfo.second)
    {
        return DataPublicationError::AddingIssue;
    }

    Info& info = (retInfo.first)->second;
    info._lstPublishers.push_back(strPublisher);

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationServer::RemoveDataList(const std::string &strDlName) noexcept
{
    auto it = m_dlData.find(strDlName);

    if(it == m_dlData.end())
    {
        return DataPublicationError::NotFound;
    }

    m_dlData.erase(it);

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationServer::AddDataToList(const std::string &strDlName, const std::string &strDataName, const VarType &data) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationError::NotFound;
    }

    std::map<std::string, VarType>& dl = it->second;
    auto itData = dl.find(strDataName);
    if(itData != dl.end())
    {
        return DataPublicationError::AlreadyExists;
    }

    auto newElement = dl.emplace(std::make_pair(strDataName, data));
    if(!newElement.second)
    {
        return DataPublicationError::AddingIssue;
    }

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationServer::RemoveDataFromList(const std::string &strDlName, const std::string &strDataName) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationError::NotFound;
    }

    std::map<std::string, VarType>& dataMap = it->second;

    auto itData = dataMap.find(strDataName);
    if(itData == dataMap.end())
    {
        return DataPublicationError::NotFound;
    }

    dataMap.erase(itData);

    return DataPublicationError::Success;
}
