cmake_minimum_required(VERSION 2.6)

project(adv_wars_clone)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Binary output directories
# Should be updated to work with x86, not just x64
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${adv_wars_clone_SOURCE_DIR}/x64)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${adv_wars_clone_SOURCE_DIR}/x64/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${adv_wars_clone_SOURCE_DIR}/x64/Release)

# SDL2 lookup and inclusion
message(STATUS "Locating SDL2...")
find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARY SDL2_image)
MESSAGE( STATUS "SDL2 lib         : " ${SDL2_LIBRARY})
MESSAGE( STATUS "SDL2_image lib   : " ${SDL2_IMAGE_LIBRARY})

function(statically_link_target_to_sdl TARGET LINK_SCOPE)
  target_link_libraries(${TARGET} ${LINK_SCOPE} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
endfunction()

# clang, gcc and msvc settings
# sets debug/optimization flags per build type
MESSAGE( STATUS "CMAKE_CXX_COMPILER_ID : " ${CMAKE_CXX_COMPILER_ID})
if ((${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
  MESSAGE( STATUS "using compiler : " ${CMAKE_CXX_COMPILER_ID})
  set(CMAKE_CXX_FLAGS "-std=c++17")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-gnu-zero-variadic-macro-arguments")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()


add_subdirectory(lib)
add_subdirectory(game)
add_subdirectory(res)
