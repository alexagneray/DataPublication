include(FetchContent)
FetchContent_Declare(
    cunit
    GIT_REPOSITORY https://github.com/tayne3/cunit.git
    GIT_TAG master
)
FetchContent_MakeAvailable(cunit)

add_subdirectory(libcmd)
add_subdirectory(libdata)