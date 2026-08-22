#pragma once

#include <DataPublication.h>
#include <boost/circular_buffer.hpp>
#include <queue>
#include <chrono>
#include <optional>
#include <string>
#include <map>

enum class SessionError
{
    Success,
    AlreadyExists,
    AddingIssue,
    NotFound
};

/**
 * Contient les informations d'une session de publication de données, y compris les requêtes en attente et l'historique des requêtes.
 * Chaque session est associée à un utilsateur unique.
 */
class Session
{
    std::queue<std::shared_ptr<QueryPacketTimed>> m_QueryQueue;
    boost::circular_buffer<QueryPacketHistory> m_QueryHistory;
    std::map<time_t, std::weak_ptr<QueryResponse>> m_lstResponses;
    private:
        std::string m_strUniqueHash; //unused
        std::string m_strUser; 
        bool m_bAuthentified;
        bool m_bConnected;
        bool IsAuthentified() const;
        bool IsConnected() const;

    public:
        Session(const std::string& strUser);
        void AddQuery(const QueryPacket&& packet);
        void AddHistory(const QueryPacketHistory&& history);
        std::optional<std::shared_ptr<QueryPacket>> GetNextQuery();
        int GetQueryHistorySize() const;
        int GetQueryQueueSize() const;
        void SetConnected(bool connected);
        void SetAuthentified(bool authentified);
};