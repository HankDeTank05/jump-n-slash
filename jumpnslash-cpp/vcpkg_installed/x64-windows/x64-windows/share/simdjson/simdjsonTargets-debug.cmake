#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "simdjson::simdjson" for configuration "Debug"
set_property(TARGET simdjson::simdjson APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(simdjson::simdjson PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/simdjson.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/simdjson.dll"
  )

list(APPEND _cmake_import_check_targets simdjson::simdjson )
list(APPEND _cmake_import_check_files_for_simdjson::simdjson "${_IMPORT_PREFIX}/debug/lib/simdjson.lib" "${_IMPORT_PREFIX}/debug/bin/simdjson.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
