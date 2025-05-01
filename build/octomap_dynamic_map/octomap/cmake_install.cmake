# Install script for directory: /home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/sentry/Wolf-Moon/install/octomap_dynamic_map")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/octomap" TYPE FILE FILES
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/AbstractOcTree.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/AbstractOccupancyOcTree.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/ColorOcTree.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/CountingOcTree.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/MCTables.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/MapCollection.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/MapCollection.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/MapNode.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/MapNode.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTree.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeBase.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeBaseImpl.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeBaseImpl.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeDataNode.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeDataNode.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeIterator.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeKey.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeNode.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OcTreeStamped.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OccupancyOcTreeBase.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/OccupancyOcTreeBase.hxx"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/Pointcloud.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/ScanGraph.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/octomap.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/octomap_deprecated.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/octomap_timing.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/octomap_types.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/octomap_utils.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/octomap/math" TYPE FILE FILES
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/math/Pose6D.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/math/Quaternion.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/math/Utils.h"
    "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/include/octomap/math/Vector3.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/octomap" TYPE FILE FILES "/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/octomap/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/sentry/Wolf-Moon/build/octomap_dynamic_map/octomap/share/ament_index/resource_index/packages/octomap")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/octomap" TYPE FILE FILES
    "/home/sentry/Wolf-Moon/build/octomap_dynamic_map/octomap/InstallFiles/octomap-config.cmake"
    "/home/sentry/Wolf-Moon/build/octomap_dynamic_map/octomap/InstallFiles/octomap-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/sentry/Wolf-Moon/build/octomap_dynamic_map/lib/pkgconfig/octomap.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sentry/Wolf-Moon/build/octomap_dynamic_map/octomap/src/math/cmake_install.cmake")
  include("/home/sentry/Wolf-Moon/build/octomap_dynamic_map/octomap/src/cmake_install.cmake")

endif()

