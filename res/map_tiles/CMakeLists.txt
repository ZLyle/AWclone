set(MAP_TILE_ASSETS
  map_tile_sheet.png
  )

foreach(ASSET_FILE ${MAP_TILE_ASSETS})
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/res/map_tiles/${ASSET_FILE} COPYONLY)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/res/map_tiles/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
