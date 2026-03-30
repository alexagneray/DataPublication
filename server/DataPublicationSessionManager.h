#include "DataPublicationSession.h"
#include <map>

/**
 * @brief Manager for DataPublicationSession instances, allowing to create and remove sessions based on user identifiers.
 * This class maintains a mapping of user identifiers to their corresponding DataPublicationSession instances, ensuring that each user has a unique session.
 * It provides methods to add and remove sessions, returning appropriate error codes based on the operation's success or failure.
 * The AddSession method checks if a session for the given user already exists and returns an error if it does. 
 * If not, it creates a new session and adds it to the map. 
 * The RemoveSession method checks if a session for the given user exists and removes it if found, returning an error if it does not exist.
 */
class DataPublicationSessionManager
{
private:
    std::map<std::string, DataPublicationSession> m_mapSessions;
public:
    DataPublicationSessionManager();
    ~DataPublicationSessionManager();

    DataPublicationSessionError AddSession(const std::string& strUser);
    DataPublicationSessionError RemoveSession(const std::string& strUser);
    std::weak_ptr<QueryPacket> GetNextQuery(uint32_t& u32ClientID);
};

extern DataPublicationSessionManager g_DataPublicationSessionManagerInstance;