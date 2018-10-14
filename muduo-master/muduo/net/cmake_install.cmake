# Install script for directory: /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/lib/libmuduo_net.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/lib/libmuduo_net_cpp11.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/net" TYPE FILE FILES
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/Buffer.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/Callbacks.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/Channel.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/Endian.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/EventLoop.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/EventLoopThread.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/EventLoopThreadPool.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/InetAddress.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/TcpClient.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/TcpConnection.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/TcpServer.h"
    "/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/TimerId.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/http/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/inspect/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/muduo/net/tests/cmake_install.cmake")

endif()

