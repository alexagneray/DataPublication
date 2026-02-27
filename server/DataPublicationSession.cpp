#include "DataPublicationSession.h"

const int MAX_HISTORY_SIZE = 100;

bool DataPublicationSession::IsAuthentified() const
{
    return m_bAuthentified;
}

bool DataPublicationSession::IsConnected() const
{
    return m_bConnected;
}

DataPublicationSession::DataPublicationSession():
    m_bAuthentified(false),
    m_bConnected(false),
    m_QueryHistory(MAX_HISTORY_SIZE)
{
}

void DataPublicationSession::AddQuery(const QueryPacket &&packet)
{
    m_QueryQueue.push(std::move(packet));
}

void DataPublicationSession::AddHistory(const QueryPacketHistory &&history)
{
    m_QueryHistory.push_back(std::move(history));
}

std::optional<QueryPacket> DataPublicationSession::GetNextQuery()
{
    if (m_QueryQueue.empty())
    {
        return std::nullopt;
    }
    QueryPacket packet = m_QueryQueue.front();
    m_QueryQueue.pop();
    return std::move(packet);
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