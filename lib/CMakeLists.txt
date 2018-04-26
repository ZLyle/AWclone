set(LIB_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/include/ecs/component.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/ecs/config.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/ecs/core.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/ecs/entity.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/ecs/manager.hpp

  ${CMAKE_CURRENT_LIST_DIR}/include/gfx/atlas.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/gfx/config.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/gfx/core.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/gfx/sdl_wrapper.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/gfx/texture_map.hpp

  ${CMAKE_CURRENT_LIST_DIR}/include/util/lexical.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/util/timer.hpp
  )

add_library(lib INTERFACE)

target_include_directories(lib INTERFACE include/)

statically_link_target_to_sdl(lib INTERFACE)
