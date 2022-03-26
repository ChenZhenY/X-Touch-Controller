#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "lcm-static" for configuration ""
set_property(TARGET lcm-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(lcm-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblcm.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS lcm-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_lcm-static "${_IMPORT_PREFIX}/lib/liblcm.a" )

# Import target "lcm" for configuration ""
set_property(TARGET lcm APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(lcm PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblcm.so.1.4.0"
  IMPORTED_SONAME_NOCONFIG "liblcm.so.1"
  )

list(APPEND _IMPORT_CHECK_TARGETS lcm )
list(APPEND _IMPORT_CHECK_FILES_FOR_lcm "${_IMPORT_PREFIX}/lib/liblcm.so.1.4.0" )

# Import target "lcm-gen" for configuration ""
set_property(TARGET lcm-gen APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(lcm-gen PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/lcm-gen"
  )

list(APPEND _IMPORT_CHECK_TARGETS lcm-gen )
list(APPEND _IMPORT_CHECK_FILES_FOR_lcm-gen "${_IMPORT_PREFIX}/bin/lcm-gen" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
