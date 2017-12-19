set(LIB_HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/include/core.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/gfx.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/data_structs.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/component.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/render_helper.hpp)

add_library(lib INTERFACE)

target_include_directories(lib INTERFACE include/)

statically_link_target_to_sdl(lib INTERFACE)
