set(CONFIG_FILES
  gfx_config
  atlas_config
  )

foreach(ASSET_FILE ${CONFIG_FILES})
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/cfg/${ASSET_FILE} COPYONLY)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/cfg/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
