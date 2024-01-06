cmake_minimum_required(VERSION 3.16)
project(a)
#set(BLA_VENDOR OpenBLAS)

find_package(BLAS REQUIRED)

if (BLAS_FOUND)
    message(STATUS "OpenBLAS found: LIB ${BLAS_LIBRARIES}")
endif ()


add_executable(a project3.c)

target_link_libraries(a ${BLAS_LIBRARIES})