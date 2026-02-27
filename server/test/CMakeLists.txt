# Tests Unitaires
add_executable(test_publication_core test_publication_core.cpp)
target_include_directories(test_publication_core PRIVATE ${Boost_INCLUDE_DIRS} ..)
target_compile_definitions(test_publication_core PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_publication_core PRIVATE DataPublicationCore Boost::unit_test_framework)
add_test(NAME test_publication_core COMMAND test_publication_core) 

add_executable(test_publication_manager test_publication_manager.cpp)
target_include_directories(test_publication_manager PRIVATE ${Boost_INCLUDE_DIRS} .. ${CRYPTOPP_INCLUDE})
target_compile_definitions(test_publication_manager PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_publication_manager PRIVATE DataPublicationManager Boost::unit_test_framework)
add_test(NAME test_publication_manager COMMAND test_publication_manager) 

add_executable(test_userinfo_parser test_userinfo_parser.cpp ../UserInfoParser.cpp)
target_include_directories(test_userinfo_parser PRIVATE ${Boost_INCLUDE_DIRS} ..)
target_compile_definitions(test_userinfo_parser PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_userinfo_parser PRIVATE Boost::unit_test_framework Boost::json)
add_test(NAME test_userinfo_parser COMMAND test_userinfo_parser)

add_executable(test_datapublication_session test_datapublication_session.cpp ../DataPublicationSession.cpp)
target_include_directories(test_datapublication_session PRIVATE ${Boost_INCLUDE_DIRS} ..)
target_compile_definitions(test_datapublication_session PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_datapublication_session PRIVATE DataPublicationSession Boost::unit_test_framework)
add_test(NAME test_datapublication_session COMMAND test_datapublication_session)