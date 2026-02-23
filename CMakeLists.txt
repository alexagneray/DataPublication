cmake_minimum_required(VERSION 3.16)
project(transdata)
enable_testing()

# Répertoire utilisé pour les tests temporaires
if(EXISTS tmp)
  add_subdirectory(tmp)
endif()

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS unit_test_framework json)
find_path(CRYPTOPP_INCLUDE cryptopp/cryptlib.h /usr/include /usr/local/include /opt/homebrew/include)
find_library(CRYPTOPP_LIB cryptopp /usr/lib /usr/local/lib /opt/homebrew/lib)
if(NOT CRYPTOPP_INCLUDE OR NOT CRYPTOPP_LIB)
    message(FATAL_ERROR "Crypto++ library is not found!")
endif()

add_library(DataPublicationCore SHARED server/DataPublicationCore.cpp)
target_include_directories(DataPublicationCore PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(DataPublicationCore PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationCore)

add_library(DataPublicationManager SHARED server/DataPublicationManager.cpp server/UserInfoParser.cpp server/AESEncoder.cpp)
target_include_directories(DataPublicationCore PRIVATE ${Boost_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE})
target_compile_definitions(DataPublicationCore PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationCore Boost::json ${CRYPTOPP_LIB})

add_library(DataPublicationNetwork SHARED server/DataPublicationNetwork.cpp)
target_include_directories(DataPublicationNetwork PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(DataPublicationNetwork PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationNetwork Boost::json)

# Tests Unitaires
add_executable(test_publication_core server/test/test_publication_core.cpp)
target_include_directories(test_publication_core PRIVATE ${Boost_INCLUDE_DIRS} server)
target_compile_definitions(test_publication_core PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_publication_core PRIVATE DataPublicationCore Boost::unit_test_framework)
add_test(NAME test_publication_core COMMAND test_publication_core) 

add_executable(test_publication_manager server/test/test_publication_manager.cpp)
target_include_directories(test_publication_manager PRIVATE ${Boost_INCLUDE_DIRS} server ${CRYPTOPP_INCLUDE})
target_compile_definitions(test_publication_manager PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_publication_manager PRIVATE DataPublicationManager Boost::unit_test_framework Boost::json ${CRYPTOPP_LIB})
add_test(NAME test_publication_manager COMMAND test_publication_manager) 

add_executable(test_userinfo_parser server/test/test_userinfo_parser.cpp server/UserInfoParser.cpp)
target_include_directories(test_userinfo_parser PRIVATE ${Boost_INCLUDE_DIRS} server)
target_compile_definitions(test_userinfo_parser PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(test_userinfo_parser PRIVATE Boost::unit_test_framework Boost::json)
add_test(NAME test_userinfo_parser COMMAND test_userinfo_parser)