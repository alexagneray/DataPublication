#define BOOST_TEST_MODULE DataAdding Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>

#include <DataPublicationCore.h>

BOOST_AUTO_TEST_CASE(test_data_list)
{
    DataPublicationCore core;
    DataPublicationError err;
    err = core.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1 alors qu'elle existe déjà.");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = core.RemoveDataList("Liste2");
    BOOST_TEST_INFO("Suppression de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.RemoveDataList("Liste1");
    BOOST_TEST_INFO("Suppression de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

}


BOOST_AUTO_TEST_CASE(test_publish_data)
{
    DataPublicationCore core;
    DataPublicationError err;

    err = core.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Insertion de Pi dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Deuxième insertion de Pi dans Liste1 (déjà ajouté).");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = core.AddDataToList("Liste2","Pi", 3.14);
    BOOST_TEST_INFO("Ajout de Pi dans Liste2 (liste inconnue).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.RemoveDataFromList("Liste2","Pi");
    BOOST_TEST_INFO("Suppression de Pi de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.RemoveDataFromList("Liste1","Tau");
    BOOST_TEST_INFO("Suppression de Tau (inexistant) de Liste1.");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.RemoveDataFromList("Liste1","Pi");
    BOOST_TEST_INFO("Suppression de Pi de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);
}


BOOST_AUTO_TEST_CASE(test_subscriber)
{
    DataPublicationCore core;
    DataPublicationError err;

    err = core.AddDataList("Alex","Liste1");
    BOOST_TEST_INFO("Insertion de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Liste1","Pi",3.14);
    BOOST_TEST_INFO("Insertion de Pi dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Liste1","Tau",6.28);
    BOOST_TEST_INFO("Insertion de Tau dans Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.Subscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Inscription d'Olivier à Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.Subscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Deuxieme inscription d'Olivier à Liste1 (déjà inscrit).");
    BOOST_CHECK(err == DataPublicationError::AlreadyExists);

    err = core.Subscribe("Olivier","Liste2");
    BOOST_TEST_INFO("Deuxieme inscription d'Olivier à Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    std::map<std::string, std::map<std::string, DataPublicationCore::VarType>> publication; 
    err = core.GetPublication("Olivier",publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier.");
    BOOST_CHECK(err == DataPublicationError::Success);

    auto itPublication = publication.find("Liste1");
    BOOST_TEST_INFO("Vérification présence de Liste1");
    BOOST_CHECK(itPublication != publication.end());

    std::map<std::string, DataPublicationCore::VarType>& data = itPublication->second;
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

    err = core.Unsubscribe("Clément","Liste1");
    BOOST_TEST_INFO("Désincription de Clément de Liste1 (non inscrit).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.Unsubscribe("Olivier","Liste2");
    BOOST_TEST_INFO("Désincription de Clément de Liste2 (inexistante).");
    BOOST_CHECK(err == DataPublicationError::NotFound);

    err = core.Unsubscribe("Olivier","Liste1");
    BOOST_TEST_INFO("Désincription d'Olivier de Liste1.");
    BOOST_CHECK(err == DataPublicationError::Success);


    publication.clear();
    err = core.GetPublication("Olivier",publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier (après désinscription de Liste1).");
    BOOST_CHECK(err == DataPublicationError::Success);
    BOOST_CHECK(publication.empty());
}


BOOST_AUTO_TEST_CASE(test_update_data)
{
    DataPublicationCore core;
    DataPublicationError err;

    err = core.AddDataList("Alex","Coefficient");
    BOOST_TEST_INFO("Insertion de Coefficient.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Coefficient","a",1.12);
    BOOST_TEST_INFO("Insertion de a dans Coefficient.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.AddDataToList("Coefficient","b",5.47);
    BOOST_TEST_INFO("Insertion de b dans Coefficient.");
    BOOST_CHECK(err == DataPublicationError::Success);

    err = core.Subscribe("Olivier", "Coefficient");
    BOOST_TEST_INFO("Inscription d'Olivier à la liste Coefficient");
    BOOST_CHECK(err == DataPublicationError::Success);

    std::map<std::string, std::map<std::string, DataPublicationCore::VarType>> publication;
    err = core.GetPublication("Olivier", publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier avant update");
    BOOST_CHECK(err == DataPublicationError::Success);

    auto itPublication = publication.find("Coefficient");
    BOOST_TEST_INFO("Vérification présence de Coefficient");
    BOOST_CHECK(itPublication != publication.end());

    std::map<std::string, DataPublicationCore::VarType>& data = itPublication->second;
    auto itData = data.find("a");
    BOOST_TEST_INFO("Vérification présence de a dans Coefficient");
    BOOST_CHECK(itData != data.end());

    BOOST_TEST_INFO("Vérification du type de a");
    BOOST_CHECK_NO_THROW(std::get<double>(itData->second));
    BOOST_TEST_INFO("Vérification de la valeur de a");
    BOOST_CHECK(std::get<double>(itData->second) == 1.12);

    itData = data.find("b");
    BOOST_TEST_INFO("Vérification présence de b dans Coefficient");
    BOOST_CHECK(itData != data.end());

    BOOST_TEST_INFO("Vérification du type de b");
    BOOST_CHECK_NO_THROW(std::get<double>(itData->second));
    BOOST_TEST_INFO("Vérification de la valeur de b");
    BOOST_CHECK(std::get<double>(itData->second) == 5.47);


    core.UpdateData("Coefficient", "a", 6.2);
    publication.clear();
    err = core.GetPublication("Olivier", publication);
    BOOST_TEST_INFO("Récupération de la publication d'Olivier après update");
    BOOST_CHECK(err == DataPublicationError::Success);

    itPublication = publication.find("Coefficient");
    BOOST_TEST_INFO("Vérification présence de Coefficient");
    BOOST_CHECK(itPublication != publication.end());

    std::map<std::string, DataPublicationCore::VarType>& data2 = itPublication->second;
    itData = data2.find("a");
    BOOST_TEST_INFO("Vérification présence de a dans Coefficient");
    BOOST_CHECK(itData != data2.end());

    BOOST_TEST_INFO("Vérification du type de a");
    BOOST_CHECK_NO_THROW(std::get<double>(itData->second));
    BOOST_TEST_INFO("Vérification de la valeur de a (valeur erronée)");
    BOOST_CHECK(std::get<double>(itData->second) != 1.12);
    BOOST_TEST_INFO("Vérification de la valeur de a (valeur OK)");
    BOOST_CHECK(std::get<double>(itData->second) == 6.2);

}