find_package(OpenSSL REQUIRED)

add_library(DataPublicationNetwork SHARED DataPublicationNetwork.cpp)
target_include_directories(DataPublicationNetwork PRIVATE ${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS})
target_compile_definitions(DataPublicationNetwork PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationNetwork Boost::json OpenSSL::SSL)