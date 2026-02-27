#define BOOST_TEST_MODULE DATAPUBLICATION_SESSION Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>
#include <boost/json.hpp>
#include <DataPublicationSession.h>



BOOST_AUTO_TEST_CASE(session_test)
{
    DataPublicationSession session;
    boost::json::object payload;

    payload["username"] = "test_user";
    payload["password"] = "test_pass";

    session.AddQuery(QueryPacket{ServerQuery::Authenticate, std::move(payload)});

    BOOST_CHECK(session.GetQueryQueueSize() == 1);
    auto queryOpt = session.GetNextQuery();
    BOOST_CHECK(queryOpt.has_value());
    auto query = queryOpt.value();
    BOOST_CHECK(query.command == ServerQuery::Authenticate);
    BOOST_CHECK(query.payload["username"] == "test_user");
    BOOST_CHECK(query.payload["password"] == "test_pass");      
    BOOST_CHECK(session.GetQueryQueueSize() == 0);

    
}
