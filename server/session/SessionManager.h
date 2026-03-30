#pragma once
#include <memory>
#include <unordered_map>
#include "Session.h"

struct SessionEntry
{
    std::shared_ptr<Session> session;
    std::string sessionId;
};
class SessionManager
{
public:
    SessionManager();
    std::shared_ptr<Session> CreateSession(const std::string& strUser);
    void RemoveSession(const std::string& strUser);
    std::shared_ptr<Session> GetSession(const std::string& strUser);

private:
    std::unordered_map<std::string, std::unique_ptr<SessionEntry>> m_Sessions;
};

extern SessionManager SessionManagerInstance;