#include "Session.h"

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

const int MAX_HISTORY_SIZE = 100;

bool Session::IsAuthentified() const
{
    return m_bAuthentified;
}

bool Session::IsConnected() const
{
    return m_bConnected;
}

Session::Session(const std::string& strUser) :
    m_strUniqueHash(strUser),
    m_bAuthentified(false),
    m_bConnected(false),
    m_QueryHistory(MAX_HISTORY_SIZE)
{
    std::stringstream ss;
    ss << strUser << std::chrono::system_clock::now().time_since_epoch().count();
    std::string strInput = ss.str();
    
    CryptoPP::SHA256 hash;
    CryptoPP::StringSource(strInput, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(m_strUniqueHash)
            )
        )
    );
}

void Session::AddQuery(const QueryPacket &&packet)
{
    m_QueryQueue.push(std::make_shared<QueryPacket>(std::move(packet)));
}

void Session::AddHistory(const QueryPacketHistory &&history)
{
    m_QueryHistory.push_back(std::move(history));
}

std::optional<std::shared_ptr<QueryPacket>> Session::GetNextQuery()
{
    if (m_QueryQueue.empty())
    {
        return std::nullopt;
    }
    auto packet = m_QueryQueue.front();
    m_QueryQueue.pop();
    return packet;
}

int Session::GetQueryHistorySize() const
{
    return m_QueryHistory.size();
}

int Session::GetQueryQueueSize() const
{
    return m_QueryQueue.size(); 
}

void Session::SetConnected(bool connected)
{
    m_bConnected = connected;
}

void Session::SetAuthentified(bool authentified)
{
    m_bAuthentified = authentified;
}
