#pragma once

#include <DataPublication.h>
#include <boost/circular_buffer.hpp>
#include <queue>
#include <chrono>
#include <optional>
#include <string>

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
    std::queue<std::shared_ptr<QueryPacket>> m_QueryQueue;
    boost::circular_buffer<QueryPacketHistory> m_QueryHistory;
    private:
        std::string m_strUniqueHash; 
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