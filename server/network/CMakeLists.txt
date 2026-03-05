find_package(OpenSSL REQUIRED)

add_library(DataPublicationNetwork SHARED DataPublicationNetwork.cpp)
target_include_directories(DataPublicationNetwork PUBLIC ..)
target_compile_definitions(DataPublicationNetwork PUBLIC "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationNetwork OpenSSL::SSL Boost::system)
target_compile_definitions(DataPublicationNetwork PUBLIC VERBOSE)



add_subdirectory(test)