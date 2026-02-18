#include "DataPublicationCore.h"

#include <vector>

DataPublicationError DataPublicationCore::AddDataList(const std::string &strPublisher, const std::string &strDlName) noexcept
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
    info._setPublishers.insert(strPublisher);

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationCore::RemoveDataList(const std::string &strDlName) noexcept
{
    auto it = m_dlData.find(strDlName);

    if(it == m_dlData.end())
    {
        return DataPublicationError::NotFound;
    }

    m_dlData.erase(it);

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationCore::AddDataToList(const std::string &strDlName, const std::string &strDataName, const VarType &data) noexcept
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

DataPublicationError DataPublicationCore::RemoveDataFromList(const std::string &strDlName, const std::string &strDataName) noexcept
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

DataPublicationError DataPublicationCore::UpdateData(const std::string &strDlName, const std::string &strDataName, const VarType &data) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationError::NotFound;
    }

    

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationCore::Subscribe(const std::string &strSubscriber, const std::string &strDlName) noexcept
{
    auto it = m_dlInfo.find(strDlName);
    if(it == m_dlInfo.end())
    {
        return DataPublicationError::NotFound;
    }

    Info& info = it->second;
    auto ret = info._setSubscribers.insert(strSubscriber);

    if(!ret.second)
    {
        return DataPublicationError::AlreadyExists;
    }

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationCore::Unsubscribe(const std::string &strSubscriber, const std::string &strDlName) noexcept
{
    auto it = m_dlInfo.find(strDlName);
    if(it == m_dlInfo.end())
    {
        return DataPublicationError::NotFound;
    }

    Info& info = it->second;

    size_t ret = info._setSubscribers.erase(strSubscriber);
    if(!ret)
    {
        return DataPublicationError::NotFound;
    }

    return DataPublicationError::Success;
}

DataPublicationError DataPublicationCore::GetPublication(const std::string &strSubscriber, std::map<std::string, std::map<std::string, VarType>> &publication) noexcept
{
    std::vector<std::string> vecSubscriptions;

    for(const std::pair<std::string, Info>& info : m_dlInfo)
    {
        if(info.second._setSubscribers.contains(strSubscriber))
        {
            vecSubscriptions.push_back(info.first);
        }
    }

    for(const std::string& dlName: vecSubscriptions)
    {
        publication.emplace(std::make_pair(dlName, std::map<std::string, VarType>(m_dlData.at(dlName))));
    }

    return DataPublicationError::Success;
}
