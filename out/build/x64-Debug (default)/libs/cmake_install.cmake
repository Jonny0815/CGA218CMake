# Install script for directory: D:/HDA/ShaderEntwicklung/Abgabe/libs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/HDA/ShaderEntwicklung/Abgabe/out/install/x64-Debug (default)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/HDA/ShaderEntwicklung/Abgabe/out/build/x64-Debug (default)/libs/glm-master/cmake_install.cmake")
  include("D:/HDA/ShaderEntwicklung/Abgabe/out/build/x64-Debug (default)/libs/glfw-3.2.1/cmake_install.cmake")
  include("D:/HDA/ShaderEntwicklung/Abgabe/out/build/x64-Debug (default)/libs/glew-2.1.0/build/cmake/cmake_install.cmake")
  include("D:/HDA/ShaderEntwicklung/Abgabe/out/build/x64-Debug (default)/libs/stb/cmake_install.cmake")

endif()

