#include "DataPublicationSessionManager.h"


DataPublicationSessionManager::DataPublicationSessionManager()
{
}

DataPublicationSessionManager::~DataPublicationSessionManager()
{
}

DataPublicationSessionError DataPublicationSessionManager::AddSession(const std::string& strUser)
{
    auto it = m_mapSessions.find(strUser);

    if(it != m_mapSessions.end())
    {
        return DataPublicationSessionError::AlreadyExists;
    }

    auto newSession = m_mapSessions.emplace(strUser, DataPublicationSession(strUser));
    newSession.first->second.SetClientID(rand());

    return DataPublicationSessionError::Success;
}

DataPublicationSessionError DataPublicationSessionManager::RemoveSession(const std::string& strUser)
{
    auto it = m_mapSessions.find(strUser);

    if(it != m_mapSessions.end())
    {
        m_mapSessions.erase(it);
        return DataPublicationSessionError::Success;
    }

    return DataPublicationSessionError::NotFound;
}

std::weak_ptr<QueryPacket> DataPublicationSessionManager::GetNextQuery(uint32_t& u32ClientID)
{
    /**
     * TODO : implémenter un système de priorités.
     * Pour le moment, on prend simplement les Query dans l'ordre. 
     */
    for(auto& session : m_mapSessions)
    {
        std::optional query = session.second.GetNextQuery();
        if(query.has_value())
        {
            u32ClientID = session.second.GetClientID();
            return query.value();
        }
    }
    return std::weak_ptr<QueryPacket>();
}



DataPublicationSessionManager g_DataPublicationSessionManagerInstance;