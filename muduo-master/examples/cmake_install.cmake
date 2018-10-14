# Install script for directory: /usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/ace/ttcp/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/asio/chat/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/asio/tutorial/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/fastcgi/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/filetransfer/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/hub/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/idleconnection/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/maxconnection/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/memcached/client/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/memcached/server/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/multiplexer/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/netty/discard/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/netty/echo/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/netty/uptime/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/pingpong/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/roundtrip/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/shorturl/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/simple/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/socks4a/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/sudoku/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/twisted/finger/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/wordcount/cmake_install.cmake")
  include("/usrdata/usingdata/找工作/边找工作边准备/知识点总结/TCP-IP/视频教程/muduo库/muduo-master/examples/zeromq/cmake_install.cmake")

endif()

