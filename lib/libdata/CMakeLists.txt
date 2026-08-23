add_library(libdata
    data.c
    value.c
)

add_subdirectory(test)

enable_testing()
add_test(libdata_test ./libdata_test)