# CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(finger-test)

# include路径
include_directories(${PROJECT_SOURCE_DIR}/source-lib)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 生成debug版本
SET(CMAKE_BUILD_TYPE "release")
if (CMAKE_BUILD_TYPE STREQUAL debug)
    add_definitions(-D_DEBUG)
endif ()
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -std=c++11")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(${PROJECT_SOURCE_DIR}/source-lib DIR_SRCS)

# 指定生成目标
add_executable(sudoku_solver_basic ${DIR_SRCS} server_basic.cc sudoku.cc)
# 添加链接库
target_link_libraries(sudoku_solver_basic m pthread)

add_executable(sudoku_solver_multiloop ${DIR_SRCS} server_multiloop.cc sudoku.cc)
target_link_libraries(sudoku_solver_multiloop m pthread)

add_executable(sudoku_solver_threadpool ${DIR_SRCS} server_threadpool.cc sudoku.cc)
target_link_libraries(sudoku_solver_threadpool m pthread)

#add_executable(sudoku_solver_hybrid ${DIR_SRCS} server_hybrid.cc sudoku.cc)
#target_link_libraries(sudoku_solver_hybrid m pthread)

#add_executable(sudoku_solver_prod ${DIR_SRCS} server_prod.cc sudoku.cc)
#target_link_libraries(sudoku_solver_prod m pthread)

add_executable(sudoku_client_batch ${DIR_SRCS} batch.cc sudoku.cc)
target_link_libraries(sudoku_client_batch m pthread)

add_executable(sudoku_client_pipeline ${DIR_SRCS} pipeline.cc sudoku.cc)
target_link_libraries(sudoku_client_pipeline m pthread)

add_executable(sudoku_loadtest ${DIR_SRCS} loadtest.cc sudoku.cc)
target_link_libraries(sudoku_loadtest m pthread)
