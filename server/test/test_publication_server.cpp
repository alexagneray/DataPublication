#define BOOST_TEST_MODULE DataAdding Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>

#include <DataPublicationServer.h>

BOOST_AUTO_TEST_CASE(test_data_list)
{
    DataPublicationServer server;
    DataPublicationError err;
    err = server.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1 alors qu'elle existe déjà.");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = server.RemoveDataList("Liste2");
    BOOST_TEST_INFO("Suppression de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.RemoveDataList("Liste1");
    BOOST_TEST_INFO("Suppression de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

}


BOOST_AUTO_TEST_CASE(test_publish_data)
{
    DataPublicationServer server;
    DataPublicationError err;

    err = server.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Insertion de Pi dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Deuxième insertion de Pi dans Liste1 (déjà ajouté).");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = server.AddDataToList("Liste2","Pi", 3.14);
    BOOST_TEST_INFO("Ajout de Pi dans Liste2 (liste inconnue).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.RemoveDataFromList("Liste2","Pi");
    BOOST_TEST_INFO("Suppression de Pi de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.RemoveDataFromList("Liste1","Tau");
    BOOST_TEST_INFO("Suppression de Tau (inexistant) de Liste1.");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.RemoveDataFromList("Liste1","Pi");
    BOOST_TEST_INFO("Suppression de Pi de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);
}


BOOST_AUTO_TEST_CASE(test_subscriber)
{
    DataPublicationServer server;
    DataPublicationError err;

    err = server.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Insertion de Pi dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.AddDataToList("Liste1","Tau",6.28);
    BOOST_TEST_INFO("Insertion de Tau dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.Subscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Inscription d'Olivier à Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = server.Subscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Deuxieme inscription d'Olivier à Liste1 (déjà inscrit).");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = server.Subscribe("Olivier","Liste2");
    BOOST_TEST_INFO("Deuxieme inscription d'Olivier à Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    std::map<std::string, std::map<std::string, DataPublicationServer::VarType>> publication; 
    err = server.GetPublication("Olivier",publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier.");
    BOOST_CHECK(err == DataPublicationError::Success);

    auto itPublication = publication.find("Liste1");
    BOOST_TEST_INFO("Vérification présence de Liste1");
    BOOST_CHECK(itPublication != publication.end());

    std::map<std::string, DataPublicationServer::VarType>& data = itPublication->second;
    auto itData = data.find("Pi");
    BOOST_TEST_INFO("Vérification présence de Pi dans Liste1");
    BOOST_CHECK(itData != data.end());

    BOOST_TEST_INFO("Vérification valeur de Pi");
    double fPi;
    BOOST_CHECK_NO_THROW(fPi = std::get<double>(itData->second));
    BOOST_CHECK(fPi == 3.14);

    itData = data.find("Tau");
    BOOST_TEST_INFO("Vérification présence de Tau dans Liste1");
    BOOST_CHECK(itData != data.end());

    BOOST_TEST_INFO("Vérification valeur de Tau");
    double fTau;
    BOOST_CHECK_NO_THROW(fTau = std::get<double>(itData->second));
    BOOST_CHECK(fTau == 6.28);

    err = server.Unsubscribe("Clément","Liste1");
    BOOST_TEST_INFO("Désincription de Clément de Liste1 (non inscrit).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.Unsubscribe("Olivier","Liste2");
    BOOST_TEST_INFO("Désincription de Clément de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = server.Unsubscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Désincription d'Olivier de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);


    publication.clear();
    err = server.GetPublication("Olivier",publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier (après désinscription de Liste1).");
    BOOST_CHECK(err == DataPublicationError::Success);
    BOOST_CHECK(publication.empty());


}