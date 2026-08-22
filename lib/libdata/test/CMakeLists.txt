add_executable(libdata_test
    test_data.c
)

target_link_libraries(libdata_test PRIVATE libdata cunit::cunit)

target_include_directories(libdata_test PRIVATE
    ${cunit_SOURCE_DIR}/CUnit
)