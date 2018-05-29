cmake_minimum_required(VERSION 3.3)
include(ExternalProject)

project(cmake_libsodium)

set(LIBSODIUM_SOURCE_DIR "${CMAKE_BINARY_DIR}/libsodium-src")
set(LIBSODIUM_BINARY_DIR "${CMAKE_BINARY_DIR}/libsodium-build")

ExternalProject_Add(libsodium
  URL https://download.libsodium.org/libsodium/releases/LATEST.tar.gz
  CONFIGURE_COMMAND ${LIBSODIUM_SOURCE_DIR}/configure --prefix=${CMAKE_BINARY_DIR}
  BUILD_COMMAND     "make"
  SOURCE_DIR        "${LIBSODIUM_SOURCE_DIR}"
	BINARY_DIR        "${LIBSODIUM_BINARY_DIR}"
	)

set(LIBSODIUM_INCLUDE_DIRS ${LIBSODIUM_SOURCE_DIR}/src/libsodium/include CACHE INTERNAL "")

add_executable(cmake_libsodium main.cpp)

target_include_directories(cmake_libsodium
	PUBLIC
  ${LIBSODIUM_INCLUDE_DIRS}
	)

target_link_libraries(cmake_libsodium ${CMAKE_BINARY_DIR}/lib/libsodium.a)
add_dependencies(cmake_libsodium libsodium)
