cmake_minimum_required(VERSION 3.8)
project(electerm_sync_app)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_BUILD_TYPE Debug)

# include(FetchContent)
# FetchContent_Declare(
#   catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        devel  # Use the latest version from the 'devel' branch (3.x)
# )
# FetchContent_MakeAvailable(catch2)

# Include the 'include' folder that contains headers
include_directories(src/include)
# include_directories(src)

find_package(Boost 1.58.0 COMPONENTS filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Add the source files
file(GLOB SOURCES "src/*.cpp")
# list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")  # Remove main.cpp from the source list

# Create the executable
add_executable(electerm_sync_app src/main.cpp)
target_link_libraries(electerm_sync_app ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
