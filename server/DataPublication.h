#include <string>
#include <boost/json.hpp>

enum class ServerPermission : int
{
    ReadOnly,
    ReadWrite,
    Admin
};

enum class ServerQuery : int
{
    PublishData,
    SubscribeData,
    UnsubscribeData,
    Authenticate,
    Disconnect
};

struct QueryPacket
{
    ServerQuery command;
    boost::json::object payload;
};

enum class QueryResult
{
    Success,
    Failure,
    Unauthorized,
    NotFound
};
struct QueryResponse
{
    QueryResult result;
    boost::json::object payload;
};

struct QueryPacketHistory
{
    QueryPacket packet;
    std::chrono::system_clock::time_point ts;
    QueryResponse response;
};