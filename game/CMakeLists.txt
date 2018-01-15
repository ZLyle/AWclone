add_executable(game
  src/game.cpp

  src/map/board.hpp
  src/map/board.cpp

  src/ecs_ext/location_comp.hpp
  src/ecs_ext/location_system.hpp
  src/ecs_ext/sprite_comp.hpp
  src/ecs_ext/sprite_system.hpp
  src/ecs_ext/tile.hpp
  src/ecs_ext/tile_manager.hpp
  )

target_link_libraries(game PRIVATE lib)


set(CONFIG_FILES
  gfx_config
  )

foreach(ASSET_FILE ${CONFIG_FILES})
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/${ASSET_FILE} COPYONLY)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
