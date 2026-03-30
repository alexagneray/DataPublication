add_library(DataPublicationSession SHARED Session.cpp SessionManager.cpp)
target_include_directories(DataPublicationSession PUBLIC ${Boost_INCLUDE_DIRS})
target_compile_definitions(DataPublicationSession PUBLIC "BOOST_TEST_DYN_LINK=1")
target_link_libraries(DataPublicationSession PUBLIC Boost::json ${CRYPTOPP_LIB})

add_subdirectory(test)