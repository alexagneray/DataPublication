#include "DataPublicationSession.h"

bool DataPublicationSession::IsAuthentified() const
{
    return m_bAuthentified;
}

bool DataPublicationSession::IsConnected() const
{
    return m_bConnected;
}

void DataPublicationSession::AddQuery(const QueryPacket &&packet)
{
    m_QueryQueue.push(packet);
}

std::optional<QueryPacket> DataPublicationSession::GetNextQuery()
{
    if (m_QueryQueue.empty())
    {
        return std::nullopt;
    }
    QueryPacket packet = m_QueryQueue.front();
    m_QueryQueue.pop();
    return packet;
}

int DataPublicationSession::GetQueryHistorySize() const
{
    return m_QueryHistory.size();
}

int DataPublicationSession::GetQueryQueueSize() const
{
    return m_QueryQueue.size(); 
}

void DataPublicationSession::SetConnected(bool connected)
{
    m_bConnected = connected;
}

void DataPublicationSession::SetAuthentified(bool authentified)
{
    m_bAuthentified = authentified;
}