#include "SessionManager.h"

SessionManager::SessionManager()
{
}

std::shared_ptr<Session> SessionManager::CreateSession(const std::string& strUser)
{
    auto it = m_Sessions.find(strUser);
    if (it != m_Sessions.end())
    {
        return it->second->session;
    }
    auto session = std::make_shared<Session>(strUser);
    m_Sessions[strUser] = std::make_unique<SessionEntry>(session);
    return session;
}

void SessionManager::RemoveSession(const std::string& strUser)
{
    m_Sessions.erase(strUser);
}

std::shared_ptr<Session> SessionManager::GetSession(const std::string& strUser)
{
    auto it = m_Sessions.find(strUser);
    if (it != m_Sessions.end())
    {
        return it->second->session;
    }
    return nullptr;
}

SessionManager SessionManagerInstance;

