cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE "Release")
   MESSAGE(STATUS ${CMAKE_BUILD_TYPE})
ENDIF()

# Find boost
find_package(Boost REQUIRED system thread)
if (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    add_definitions("-DHAS_BOOST")
else(Boost_FOUND)
        message(FATAL_ERROR "Boost not found")
endif()
# Find bluetooth
find_library(bluetooth_LIBS NAMES bluetooth PATHS /usr/lib/ /usr/lib/x86_64-linux-gnu)
IF(NOT bluetooth_LIBS)
    message(FATAL_ERROR "Could not find bluetooth library. Please install libbluetooth-dev library.")
ENDIF()
SET(REQUIRED_LIBRARIES ${Boost_LIBRARIES} ${bluetooth_LIBS} pthread)

# Compile echo server/client
add_executable(echo_server echoserver.cpp wrapper.cpp)
target_link_libraries(echo_server ${REQUIRED_LIBRARIES})

add_executable(echo_client echoclient.cpp wrapper.cpp)
target_link_libraries(echo_client ${REQUIRED_LIBRARIES})
