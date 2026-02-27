#include "DataPublicationNetwork.h"
#include <thread>
#include <boost/asio.hpp>

#ifdef VERBOSE
#include <iostream>
#endif

namespace asio = boost::asio;
namespace ssl = asio::ssl;

static std::unique_ptr<std::thread> s_pThreadListen;
static std::unique_ptr<boost::asio::io_context> s_pIoContext;

static void DataPublicationClientHandler(asio::ip::tcp::socket socket)
{
    try {

        char data[1024];
        size_t length = socket.read_some(asio::buffer(data));

        #ifdef VERBOSE
        std::cout << "Received data: " << std::string(data, length) << std::endl;
        #endif 
        
        std::string response = "Data received";
        asio::write(socket, asio::buffer(response));
    }
    catch (std::exception& e) {
        return;
    }
}

static void DataPublicationListen(int nPort)
{
    s_pIoContext = std::make_unique<boost::asio::io_context>();

    asio::ip::tcp::acceptor acceptor(*s_pIoContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), nPort));

    while (true) {
        asio::ip::tcp::socket socket(*s_pIoContext);
        acceptor.accept(socket);

        #ifdef VERBOSE
        std::cout << "Client connected: " << socket.remote_endpoint() << std::endl;
        #endif

        std::thread(DataPublicationClientHandler, std::move(socket)).detach();
    }
}



void DataPublicationNetwork::Listen(int nPort)
{
    std::thread(DataPublicationListen, nPort).detach();
}
