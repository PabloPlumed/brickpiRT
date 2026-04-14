#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "brickpi3_motors::brickpi3_motors" for configuration ""
set_property(TARGET brickpi3_motors::brickpi3_motors APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(brickpi3_motors::brickpi3_motors PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbrickpi3_motors.so"
  IMPORTED_SONAME_NOCONFIG "libbrickpi3_motors.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS brickpi3_motors::brickpi3_motors )
list(APPEND _IMPORT_CHECK_FILES_FOR_brickpi3_motors::brickpi3_motors "${_IMPORT_PREFIX}/lib/libbrickpi3_motors.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
