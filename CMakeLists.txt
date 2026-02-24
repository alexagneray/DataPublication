cmake_minimum_required(VERSION 3.16)
project(transdata)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

add_subdirectory(server)

# Répertoire utilisé pour les tests temporaires
if(EXISTS tmp)
  add_subdirectory(tmp)
endif()