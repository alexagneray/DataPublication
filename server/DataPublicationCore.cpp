#include "DataPublicationCore.h"

#include <vector>

DataPublicationCoreError DataPublicationCore::AddDataList(const std::string &strPublisher, const std::string &strDlName) noexcept
{
    auto it = m_dlData.find(strDlName);
    
    if(it != m_dlData.end())
    {
        return DataPublicationCoreError::AlreadyExists;
    }
    
    auto retData = m_dlData.emplace(std::make_pair(strDlName, std::map<std::string, VarType>()));

    if(!retData.second)
    {
        return DataPublicationCoreError::AddingIssue;
    }

    auto retInfo = m_dlInfo.emplace(std::make_pair(strDlName, Info()));

    if(!retInfo.second)
    {
        return DataPublicationCoreError::AddingIssue;
    }

    Info& info = (retInfo.first)->second;
    info._setPublishers.insert(strPublisher);

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::RemoveDataList(const std::string &strDlName) noexcept
{
    auto it = m_dlData.find(strDlName);

    if(it == m_dlData.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    m_dlData.erase(it);

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::AddDataToList(const std::string &strDlName, const std::string &strDataName, const VarType &data) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    std::map<std::string, VarType>& dl = it->second;
    auto itData = dl.find(strDataName);
    if(itData != dl.end())
    {
        return DataPublicationCoreError::AlreadyExists;
    }

    auto newElement = dl.emplace(std::make_pair(strDataName, data));
    if(!newElement.second)
    {
        return DataPublicationCoreError::AddingIssue;
    }

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::RemoveDataFromList(const std::string &strDlName, const std::string &strDataName) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    std::map<std::string, VarType>& dataMap = it->second;

    auto itData = dataMap.find(strDataName);
    if(itData == dataMap.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    dataMap.erase(itData);

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::UpdateData(const std::string &strDlName, const std::string &strDataName, const VarType &newData) noexcept
{
    auto it = m_dlData.find(strDlName);
    if(it == m_dlData.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    std::map<std::string, VarType>& mapData = it->second;
    auto itData = mapData.find(strDataName);
    if(itData == mapData.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    VarType& data = itData->second;
    data = newData;

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::Subscribe(const std::string &strSubscriber, const std::string &strDlName) noexcept
{
    auto it = m_dlInfo.find(strDlName);
    if(it == m_dlInfo.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    Info& info = it->second;
    auto ret = info._setSubscribers.insert(strSubscriber);

    if(!ret.second)
    {
        return DataPublicationCoreError::AlreadyExists;
    }

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::Unsubscribe(const std::string &strSubscriber, const std::string &strDlName) noexcept
{
    auto it = m_dlInfo.find(strDlName);
    if(it == m_dlInfo.end())
    {
        return DataPublicationCoreError::NotFound;
    }

    Info& info = it->second;

    size_t ret = info._setSubscribers.erase(strSubscriber);
    if(!ret)
    {
        return DataPublicationCoreError::NotFound;
    }

    return DataPublicationCoreError::Success;
}

DataPublicationCoreError DataPublicationCore::GetPublication(const std::string &strSubscriber, std::map<std::string, std::map<std::string, VarType>> &publication) noexcept
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

    return DataPublicationCoreError::Success;
}

DataPublicationCore DataPublicationCoreInstance;