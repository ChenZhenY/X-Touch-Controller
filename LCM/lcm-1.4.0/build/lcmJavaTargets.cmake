cmake_minimum_required(VERSION 2.8)
cmake_policy(PUSH)
cmake_policy(VERSION 2.8)

#----------------------------------------------------------------
# Generated CMake Java target import file.
#----------------------------------------------------------------

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget lcm-java)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  else()
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
endforeach()
if("%${_targetsDefined}" STREQUAL "%${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR
    "Some (but not all) targets in this export set were already defined.\n"
    "Targets Defined: ${_targetsDefined}\n"
    "Targets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)

# Create imported target lcm-java
add_library(lcm-java IMPORTED STATIC)
set_target_properties(lcm-java PROPERTIES
  IMPORTED_LOCATION "/home/urop/lcm-1.4.0/build/lcm-java/lcm.jar"
  JAR_FILE "/home/urop/lcm-1.4.0/build/lcm-java/lcm.jar")

cmake_policy(POP)
