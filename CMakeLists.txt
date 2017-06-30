cmake_minimum_required(VERSION 2.6)
project(adv_wars_clone)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Binary output directories
# Should be updated to work with x86, not just x64
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${adv_wars_clone_SOURCE_DIR}/x64)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${adv_wars_clone_SOURCE_DIR}/x64/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${adv_wars_clone_SOURCE_DIR}/x64/Release)

# SDL2 linking variable
# clang, gcc and msvc settings
# sets debug/optimization flags per build type
MESSAGE( STATUS "CMAKE_CXX_COMPILER_ID : " ${CMAKE_CXX_COMPILER_ID})
if ((${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
  MESSAGE( STATUS "using compiler : " ${CMAKE_CXX_COMPILER_ID})
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

# SDL2 lookup and inclusion
find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARY SDL2_image)
MESSAGE( STATUS "sdl2 lib         : " ${SDL2_LIBRARY})
MESSAGE( STATUS "sdl2_image lib   : " ${SDL2_IMAGE_LIBRARY})

# Header directories
set(SRC_DIR ${adv_wars_clone_SOURCE_DIR}/src)
#set(HEADER_FILES ${SRC_DIR}/map.h ${SRC_DIR}/gfx.h)

include_directories(${SRC_DIR})

add_executable(game src/game.cpp)

target_sources(game
  PRIVATE
    "${SRC_DIR}/data_structs.h"
    "${SRC_DIR}/gfx.h"
    "${SRC_DIR}/gfx.cpp"
    "${SRC_DIR}/map.h"
    "${SRC_DIR}/map.cpp"
    "${SRC_DIR}/util.h"
    "${SRC_DIR}/util.cpp"
    "${SRC_DIR}/component.h"
    "${SRC_DIR}/component.cpp"
)

target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG} CONFIGURATIONS Debug)
install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} CONFIGURATIONS Release)
