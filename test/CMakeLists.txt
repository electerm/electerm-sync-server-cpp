set(CMAKE_CXX_STANDARD 17)          # Change from 14 to 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.8)
project(electerm_sync_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Include the project's 'src/include' folder that contains Crow headers

include_directories(src/include)

find_package(Boost 1.58.0 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(electerm_sync_app ${SOURCES})


# If you need to link additional libraries, add them in target_link_libraries
target_link_libraries(electerm_sync_app ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
