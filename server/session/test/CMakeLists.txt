# Tests Unitaires
add_executable(test_session test_session.cpp)
target_include_directories(test_session PRIVATE ${Boost_INCLUDE_DIRS} ..)
target_compile_definitions(test_session PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_session PRIVATE DataPublicationSession Boost::unit_test_framework)
add_test(NAME test_session COMMAND test_session) 