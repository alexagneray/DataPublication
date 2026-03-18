#include <queue>
#include <mutex>
#include "DataPublication.h"

class QueryManager
{
    private:
    std::queue<QueryPacket> m_quQuery;
    std::queue<QueryResponse> m_quResponse;
    std::mutex m_mutQuery;
    std::mutex m_mutResponse;
public:
    void EnqueueQuery(const QueryPacket& packet);
    bool GetNextQuery(QueryPacket& packet);
    void EnqueueResponse(const QueryResponse& response);
    bool GetNextResponse(QueryResponse& response);   
};

extern QueryManager QueryManagerInstance;