#define BOOST_TEST_MODULE DATAPUBLICATION_SESSION Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>
#include <boost/json.hpp>
#include <SessionManager.h>



BOOST_AUTO_TEST_CASE(session_test)
{
    auto session = SessionManagerInstance.CreateSession("Alex");
    boost::json::object payload;

    payload["username"] = "test_user";
    payload["password"] = "test_pass";

    session->AddQuery(QueryPacket{ServerQuery::Authenticate, std::move(payload)});

    BOOST_TEST_INFO("Vérifie que la session a une requête dans la file d'attente");
    BOOST_CHECK(session->GetQueryQueueSize() == 1);
    auto queryOpt = session->GetNextQuery();
    BOOST_TEST_INFO("Vérifie que la session a récupéré une requête de la file d'attente");
    BOOST_CHECK(queryOpt.has_value());
    std::shared_ptr<QueryPacket> query = queryOpt.value();
    BOOST_TEST_INFO("Vérifie que la requête récupérée est une requête d'authentification");
    BOOST_CHECK(query->command == ServerQuery::Authenticate);
    BOOST_TEST_INFO("Vérifie que la requête d'authentification a un username");
    BOOST_CHECK(query->payload["username"] == "test_user");
    BOOST_TEST_INFO("Vérifie que la requête d'authentification a un password");
    BOOST_CHECK(query->payload["password"] == "test_pass");     
    BOOST_TEST_INFO("Vérifie que la file d'attente de la session est maintenant vide"); 
    BOOST_CHECK(session->GetQueryQueueSize() == 0);

    // QueryResponse response{QueryResult::Success, boost::json::object{}};
    // QueryPacketHistory history{std::move(query), std::chrono::system_clock::now(), std::move(response)};

    // session.AddHistory(std::move(history));
    // BOOST_TEST_INFO("Vérifie que la session a une requête dans l'historique");
    // BOOST_CHECK(session.GetQueryHistorySize() == 1);
    


}
