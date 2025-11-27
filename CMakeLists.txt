cmake_minimum_required(VERSION 3.10)
project(MyProgram)

set(CMAKE_CXX_STANDARD 11)

# Determine the platform
if(WIN32)
    # Windows-specific settings for OpenSSL
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
    find_path(OPENSSL_INCLUDE_DIR NAMES openssl/ssl.h HINTS ${OPENSSL_ROOT_DIR}/include)
    find_library(OPENSSL_CRYPTO_LIBRARY NAMES crypto HINTS ${OPENSSL_ROOT_DIR}/lib/VC/x64/MD)
    find_library(OPENSSL_SSL_LIBRARY NAMES ssl HINTS ${OPENSSL_ROOT_DIR}/lib/VC/x64/MD)

    # Windows-specific settings for SQLite
    find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h HINTS "C:/sqlite3")
    find_library(SQLITE3_LIBRARY NAMES sqlite3 HINTS "C:/sqlite3")

elseif(APPLE)
    # macOS-specific settings for OpenSSL
    find_package(OpenSSL REQUIRED)

    # macOS-specific settings for SQLite
    find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h HINTS /usr/local/include)
    find_library(SQLITE3_LIBRARY NAMES sqlite3 HINTS /usr/local/lib)

elseif(UNIX)
    # Linux-specific settings for OpenSSL
    find_package(OpenSSL REQUIRED)

    # Linux-specific settings for SQLite
    find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h HINTS /usr/include)
    find_library(SQLITE3_LIBRARY NAMES sqlite3 HINTS /usr/lib)

else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

# Check if OpenSSL was found
if(NOT OPENSSL_INCLUDE_DIR OR NOT OPENSSL_CRYPTO_LIBRARY OR NOT OPENSSL_SSL_LIBRARY)
    message(FATAL_ERROR "OpenSSL not found!")
endif()

# Check if SQLite3 was found
if(NOT SQLITE3_INCLUDE_DIR OR NOT SQLITE3_LIBRARY)
    message(FATAL_ERROR "SQLite3 not found!")
endif()

# Include directories for OpenSSL and SQLite
include_directories(${OPENSSL_INCLUDE_DIR} ${SQLITE3_INCLUDE_DIR})

# Add executable
add_executable(main main.cpp)

# Link against OpenSSL and SQLite libraries
target_link_libraries(main ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} ${SQLITE3_LIBRARY})
