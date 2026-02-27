#include <DataPublication.h>
#include <boost/circular_buffer.hpp>
#include <queue>
#include <chrono>
#include <optional>

class DataPublicationSession
{
    
    std::queue<QueryPacket> m_QueryQueue;
    boost::circular_buffer<QueryPacketHistory> m_QueryHistory;
    private:
        bool m_bAuthentified;
        bool m_bConnected;
        bool IsAuthentified() const;
        bool IsConnected() const;

    public:
        DataPublicationSession();
        void AddQuery(const QueryPacket&& packet);
        void AddHistory(const QueryPacketHistory&& history);
        std::optional<QueryPacket> GetNextQuery();
        int GetQueryHistorySize() const;
        int GetQueryQueueSize() const;

        void SetConnected(bool connected);
        void SetAuthentified(bool authentified);
};