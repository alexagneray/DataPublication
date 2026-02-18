#define BOOST_TEST_MODULE DataAdding Test
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