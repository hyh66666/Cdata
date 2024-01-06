cmake_minimum_required(VERSION 3.16)
project(wsl)
#set(BLA_VENDOR OpenBLAS)

find_package(BLAS REQUIRED)

if (BLAS_FOUND)
    message(STATUS "OpenBLAS found: LIB ${BLAS_LIBRARIES}")
endif ()


add_executable(wsl main.cpp)

target_link_libraries(wsl ${BLAS_LIBRARIES})