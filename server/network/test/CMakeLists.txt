# add_executable(datapublicationclient datapublicationclient.cpp)
# target_include_directories(datapublicationclient PRIVATE ${Boost_INCLUDE_DIRS} ..)
# target_compile_definitions(datapublicationclient PRIVATE "BOOST_TEST_DYN_LINK=1")
# target_link_libraries(datapublicationclient PRIVATE Boost::unit_test_framework Boost::json OpenSSL::SSL Boost::program_options)


# add_executable(datapublicationserver datapublicationserver.cpp)
# target_include_directories(datapublicationserver PRIVATE ${Boost_INCLUDE_DIRS} ..)
# target_compile_definitions(datapublicationserver PRIVATE "BOOST_TEST_DYN_LINK=1")
# target_link_libraries(datapublicationserver PRIVATE Boost::unit_test_framework Boost::json DataPublicationNetwork Boost::program_options)

add_executable(test_datapublicationnetwork_connection test_datapublicationnetwork_connection.cpp)
target_include_directories(test_datapublicationnetwork_connection PRIVATE ${Boost_INCLUDE_DIRS} ..)
target_compile_definitions(test_datapublicationnetwork_connection PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_datapublicationnetwork_connection PRIVATE Boost::unit_test_framework DataPublicationNetwork)
add_test(NAME test_datapublicationnetwork_connection COMMAND test_datapublicationnetwork_connection)