set(UNIT_ASSETS
  infantry_map_red.png
  )

foreach(ASSET_FILE ${UNIT_ASSETS})
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/res/units/${ASSET_FILE} COPYONLY)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/res/units/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
