#include "QueryManager.h"

void QueryManager::EnqueueQuery(const QueryPacket &packet)
{
    std::lock_guard<std::mutex> lock(m_mutQuery);
    m_quQuery.push(packet);
}

bool QueryManager::GetNextQuery(QueryPacket &packet)
{
    std::lock_guard<std::mutex> lock(m_mutQuery);
    if (m_quQuery.empty())
        return false;
    packet = m_quQuery.front();
    m_quQuery.pop();
    return true;
}

void QueryManager::EnqueueResponse(const QueryResponse &response)
{
    std::lock_guard<std::mutex> lock(m_mutResponse);
    m_quResponse.push(response);
}

bool QueryManager::GetNextResponse(QueryResponse &response)
{
    std::lock_guard<std::mutex> lock(m_mutResponse);
    if (m_quResponse.empty())
        return false;
    response = m_quResponse.front();
    m_quResponse.pop();
    return true;
}

QueryManager QueryManagerInstance;