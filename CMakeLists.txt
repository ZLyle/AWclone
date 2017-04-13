cmake_minimum_required(VERSION 2.6)
project(adv_wars_clone)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Binary output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${adv_wars_clone_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${adv_wars_clone_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${adv_wars_clone_SOURCE_DIR}/bin/release)

# SDL2 linking variable
set(SDL_LINKER_FLAGS "-lSDL2 -lSDL2_image")
# clang, gcc and msvc settings
# sets debug/optimization flags per build type
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -pedantic ${SDL_LINKER_FLAGS}")
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
find_library(SDL2 SDL2/SDL.h)
find_library(SDL2_image SDL2/SDL_image.h)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Header directories
set(SRC_DIR ${adv_wars_clone_SOURCE_DIR}/src)
#set(HEADER_FILES ${SRC_DIR}/map.h ${SRC_DIR}/gfx.h)
include_directories(${SRC_DIR})


add_executable(game src/game.cpp)

target_sources(game
  PRIVATE
    "${SRC_DIR}/gfx.h"
    "${SRC_DIR}/gfx.cpp"
    "${SRC_DIR}/map.h"
    "${SRC_DIR}/map.cpp"
)

#target_link_libraries(game ${SDL2_LIBRARY}, ${SDL2_IMAGE_LIBRARY})
install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG} CONFIGURATIONS Debug)
install(TARGETS game RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} CONFIGURATIONS Release)
