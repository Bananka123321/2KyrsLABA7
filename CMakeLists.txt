cmake_minimum_required(VERSION 3.10.0)
project(LAB7 VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS filesystem system program_options)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(LAB7 src/main.cpp src/Duplicates.cpp src/FileHash.cpp src/FileScanner.cpp src/Parser.cpp)

target_link_libraries(LAB7 ${Boost_LIBRARIES} ZLIB::ZLIB OpenSSL::Crypto)

set(CPACK_PACKAGE_NAME "LAB7")

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
endif()

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ivan Obuhov <vanushabrend@gmail.com>")
endif()

install(TARGETS LAB7 DESTINATION bin)
include(CPack)