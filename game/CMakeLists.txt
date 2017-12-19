add_executable(game
  src/game.cpp
  src/map.hpp
  src/map.cpp
  src/util.hpp)

target_link_libraries(game PRIVATE lib)
