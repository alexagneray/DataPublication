#define BOOST_TEST_MODULE PublicationManager Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <DataPublicationManager.h>

#define FILE_CONTENT "[{\"name\":\"alex\",\"passwd\":\"1234\"}]"

BOOST_AUTO_TEST_CASE(test_userinfo_load_save)
{

    DataPublicationManager mgr; 

    mgr.AddUser("Alex", "Alex1234");
    mgr.AddUser("Olivier", "Olivier1234");

    bool ret = mgr.SaveUserInfoFile();
    BOOST_TEST_INFO("Sauvegarde du fichier _userinfo");
    BOOST_CHECK(ret);

    ret = mgr.LoadUserInfoFile();
    BOOST_TEST_INFO("Chargement du fichier _userinfo");
    BOOST_CHECK(ret);

    ret = mgr.SaveUserInfoFile();
    BOOST_TEST_INFO("(2) Sauvegarde du fichier _userinfo");
    BOOST_CHECK(ret);

    ret = mgr.LoadUserInfoFile();
    BOOST_TEST_INFO("(2) Chargement du fichier _userinfo");
    BOOST_CHECK(ret);
}