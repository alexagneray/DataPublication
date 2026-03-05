#include <boost/asio.hpp>
#include <iostream>
#include <boost/program_options.hpp>

namespace asio = boost::asio;
namespace po = boost::program_options;

using namespace std;

int main(int argc, char* argv[]) {
    int nPort = -1;
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "datapublicationserver -p [port]")
    ("-p", po::value<int>(), "port number");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("-p")) {
        nPort = vm["-p"].as<int>();
    } else {
        cout << "Port not set.\n";
    }

    asio::io_context io_context;

    // Résolution DNS et connexion
    asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("localhost", std::to_string(nPort));


    // Connexion au serveur
    asio::ip::tcp::socket socket(io_context);
    asio::connect(socket, endpoints);


    std::cout << "Connecté au serveur." << std::endl;


    // Envoie une réponse
    std::string message = "Bonjour depuis le client!\n";
    asio::write(socket, asio::buffer(message));


    std::string rcvBuffer(1024, '\0');
    socket.read_some(asio::buffer(rcvBuffer));

    std::cout << "Réponse du serveur : " << rcvBuffer << std::endl;

    return 0;
}
