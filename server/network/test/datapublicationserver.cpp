#define VERBOSE

#include <DataPublicationNetwork.h>
#include <boost/program_options.hpp>
#include <iostream>



namespace po = boost::program_options;
using namespace std;
int main(int argc, char* argv[])
{
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

    DataPublicationNetwork::Listen(nPort);

    // Keep the main thread alive to allow the server to run
    std::this_thread::sleep_for(std::chrono::seconds(60));

    return 0;
}