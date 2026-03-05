#define BOOST_TEST_MODULE NETWORK_CONNECTION Test

#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>

#include <DataPublicationNetwork.h>

namespace asio = boost::asio;
const int PORT = 9000; 

struct DataPublicationServerFixture
{
    DataPublicationNetwork network;
    DataPublicationServerFixture()
    {
        network.Listen(PORT);
    }
};

BOOST_FIXTURE_TEST_SUITE(server, DataPublicationServerFixture)
BOOST_AUTO_TEST_CASE(test_network_connection)
{
    asio::io_context io_context;

    // Résolution DNS et connexion
    asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("localhost", std::to_string(PORT));


    // Connexion au serveur
    asio::ip::tcp::socket socket(io_context);
    BOOST_CHECK_NO_THROW(asio::connect(socket, endpoints));



    // Envoie une réponse
    std::string message = "Bonjour depuis le client!\n";
    BOOST_CHECK_NO_THROW(asio::write(socket, asio::buffer(message)));


    std::string rcvBuffer(1024, '\0');
    BOOST_CHECK_NO_THROW(socket.read_some(asio::buffer(rcvBuffer)));

    BOOST_CHECK_EQUAL(rcvBuffer.c_str(), "ACK");

}

BOOST_AUTO_TEST_SUITE_END()