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

add_subdirectory(cfg)
