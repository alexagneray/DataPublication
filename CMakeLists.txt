cmake_minimum_required(VERSION 3.16)
project(transdata)
enable_testing()

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS unit_test_framework json)


add_library(DataPublicationCore server/DataPublicationServer.cpp)
target_include_directories(DataPublicationCore PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(DataPublicationCore PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationCore Boost::json)

# Tests Unitaires
add_executable(test_publication_server server/test/test_publication_server.cpp)
target_include_directories(test_publication_server PRIVATE ${Boost_INCLUDE_DIRS} server)
target_compile_definitions(test_publication_server PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_publication_server PRIVATE DataPublicationCore Boost::unit_test_framework)
add_test(NAME test_publication_server COMMAND test_publication_server) 