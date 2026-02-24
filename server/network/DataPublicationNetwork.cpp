#include "DataPublicationNetwork.h"
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace asio = boost::asio;
namespace ssl = asio::ssl;

static std::unique_ptr<std::thread> s_pThreadListen;
static std::unique_ptr<boost::asio::io_context> s_pIoContext;
static std::unique_ptr<boost::asio::ssl::context> s_pSslContext;

static void DataPublicationListen()
{
    s_pIoContext = std::make_unique<boost::asio::io_context>();

    // Configuration SSL (certificat + clé privée)
    s_pSslContext = std::make_unique<ssl::context>(ssl::context::tls_server);
    s_pSslContext->use_certificate_file("server.crt", ssl::context::pem);
    s_pSslContext->use_private_key_file("server.key", ssl::context::pem);

    // Accepte les connexions sur le port 8080
    asio::ip::tcp::acceptor acceptor(*s_pIoContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));

    while (true) {
        asio::ip::tcp::socket socket(*s_pIoContext);
        acceptor.accept(socket);

        // Crée une socket SSL à partir de la socket TCP
        ssl::stream<asio::ip::tcp::socket> ssl_socket(std::move(socket), *s_pSslContext);
    }
}

void DataPublicationNetwork::Listen()
{
    std::thread(Listen).detach();
}
