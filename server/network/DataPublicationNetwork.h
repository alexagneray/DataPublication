#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
class DataPublicationNetwork
{
    private:
    
    public:
    /**
     * Fonction non bloquante, 
     * initialisation du thread d'écoute.
     */
    static void Listen(int nPort);
};