cmake_minimum_required(VERSION 3.8)
project(test_file_store)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE Debug)

# Include the 'include' folder that contains headers
include_directories(../src/include)
# include_directories(src)

find_package(Boost 1.58.0 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Add the source files
# file(GLOB SOURCES "src/*.cpp")
# list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")  # Remove main.cpp from the source list

# Create the executable
add_executable(test_file_store test_file_store.cpp)
target_link_libraries(test_file_store ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
