cmake_minimum_required(VERSION 3.8)
project(test_data_store)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE Debug)

# Include the 'include' folder that contains headers
include_directories(../src/include)
include_directories(../src)

find_package(Boost 1.58.0 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Find SQLite3
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)
include_directories(${SQLITE3_INCLUDE_DIRS})

# Create the executable
add_executable(test_data_store test_data_store.cpp)
target_link_libraries(test_data_store ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${SQLITE3_LIBRARIES})
