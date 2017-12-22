set(UNIT_ASSETS
  infantry_map_red.png
  )

foreach(ASSET_FILE ${UNIT_ASSETS})
  if (CMAKE_CXX_FLAGS_DEBUG)
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/res/units/${ASSET_FILE} COPYONLY)
  else()
    configure_file(${ASSET_FILE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/res/units/${ASSET_FILE} COPYONLY)
  endif()
endforeach(ASSET_FILE)
