#define BOOST_TEST_MODULE UserInfoParser Test
// #define BOOST_TEST_LOG_LEVEL all
// #define BOOST_TEST_LOG_FORMAT detailed
// #define BOOST_TEST_SHOW_PROGRESS yes
#include <boost/test/unit_test.hpp>

#include <UserInfoParser.h>
#include <array>


BOOST_AUTO_TEST_CASE(test_userinfo_parse)
{
    UserInfoParser parser;
    std::list<UserInfo> lstUserInfo;

    std::array<UserInfo, 3> infos{
        UserInfo{"Alex", "Alex1234"},
        UserInfo{"Olivier", "Olivier1234"},
        UserInfo{"Clément", "Clément1234"}
    };

    std::for_each(infos.begin(), infos.end(), [&lstUserInfo] (UserInfo& info) {lstUserInfo.emplace_back(info);});

    boost::json::array arr;
    parser.ConvertUserInfoToJsonArray(lstUserInfo, arr);

    BOOST_TEST_INFO("Taille du tableau JSON");
    BOOST_CHECK(arr.size() == 3);
    for(int i=0;i<infos.size();i++)
    {
        try{
            boost::json::value& valUser = arr.at(i);
            boost::json::object& objUser = valUser.as_object();
            BOOST_TEST_INFO("Présence du champ name");
            BOOST_CHECK_NO_THROW(objUser.at("name"));
            BOOST_TEST_INFO("Présence du champ passwd");
            BOOST_CHECK_NO_THROW(objUser.at("passwd"));
        }
        catch(boost::system::system_error& e)
        {
            BOOST_TEST_INFO("Exception levée par at(i) ou as_object");
            BOOST_CHECK(false);
        }

    }
    

    std::list<UserInfo> lstUserInfo2;
    parser.ConvertJsonArrayToUserInfo(arr, lstUserInfo2);

    BOOST_TEST_INFO("Taille de la liste de UserInfo");
    BOOST_CHECK(lstUserInfo2.size() == 3);

    int i = 0;
    for(auto& user: lstUserInfo2)
    {
        BOOST_TEST_INFO("Vérification champ name");
        BOOST_CHECK(!user._name.compare(infos[i]._name));
        BOOST_TEST_INFO("Vérification champ passwd");
        BOOST_CHECK(!user._passwd.compare(infos[i]._passwd));
        i++;
    }
}