# Install script for directory: /home/urop/lcm-1.4.0

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake" TYPE FILE FILES "/home/urop/lcm-1.4.0/build/CMakeFiles/JavaExports/88894d64ce10c054acd18aec9b9e1272bc6131c4d8ff377f5ef803cf013e2faf/lcmJavaTargets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake/lcmTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake/lcmTargets.cmake"
         "/home/urop/lcm-1.4.0/build/CMakeFiles/Export/lib/lcm/cmake/lcmTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake/lcmTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake/lcmTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake" TYPE FILE FILES "/home/urop/lcm-1.4.0/build/CMakeFiles/Export/lib/lcm/cmake/lcmTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake" TYPE FILE FILES "/home/urop/lcm-1.4.0/build/CMakeFiles/Export/lib/lcm/cmake/lcmTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/lcm/cmake" TYPE FILE FILES
    "/home/urop/lcm-1.4.0/build/lcmConfig.cmake"
    "/home/urop/lcm-1.4.0/build/lcmConfigVersion.cmake"
    "/home/urop/lcm-1.4.0/build/lcmUtilities.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/urop/lcm-1.4.0/build/lcm/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/lcmgen/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/lcm-logger/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/liblcm-test/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/docs/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/lcm-java/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/lcm-python/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/test/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/m4macros/cmake_install.cmake")
  include("/home/urop/lcm-1.4.0/build/lcm-pkgconfig/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/urop/lcm-1.4.0/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
