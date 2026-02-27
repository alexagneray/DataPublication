find_package(Boost REQUIRED COMPONENTS unit_test_framework json program_options)
find_path(CRYPTOPP_INCLUDE cryptopp/cryptlib.h /usr/include /usr/local/include /opt/homebrew/include)
find_library(CRYPTOPP_LIB cryptopp /usr/lib /usr/local/lib /opt/homebrew/lib)
if(NOT CRYPTOPP_INCLUDE OR NOT CRYPTOPP_LIB)
    message(FATAL_ERROR "Crypto++ library is not found!")
endif()

add_library(DataPublicationCore SHARED DataPublicationCore.cpp)
target_include_directories(DataPublicationCore PUBLIC ${Boost_INCLUDE_DIRS})
target_compile_definitions(DataPublicationCore PUBLIC "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationCore PUBLIC Boost::json)

add_library(DataPublicationManager SHARED DataPublicationManager.cpp UserInfoParser.cpp AESEncoder.cpp)
target_include_directories(DataPublicationManager PUBLIC ${Boost_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE})
target_compile_definitions(DataPublicationManager PUBLIC "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationManager PUBLIC Boost::json ${CRYPTOPP_LIB})

add_subdirectory(network)
add_subdirectory(test)