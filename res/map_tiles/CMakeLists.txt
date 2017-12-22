set(MAP_TILE_ASSETS
  map_tile_sheet.png
  )

foreach(ASSET_FILE ${MAP_TILE_ASSETS})
  if (CMAKE_CXX_FLAGS_DEBUG)
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/res/map_tiles/${ASSET_FILE} COPYONLY)
  else()
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/res/map_tiles/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
