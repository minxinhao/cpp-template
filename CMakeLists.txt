cmake_minimum_required(VERSION 3.5)
project(MyProject CXX)

# 设置编译器为g++
set(CMAKE_CXX_COMPILER g++)

# 设置C++标准为C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找所有数字文件夹
file(GLOB DIRECTORIES "[0-9][0-9]")

# 添加include文件夹路径
include_directories(./include)

# 遍历每个数字文件夹
foreach(DIR ${DIRECTORIES})
  # 获取数字文件夹名称
  get_filename_component(DIR_NAME ${DIR} NAME)

  # 查找数字文件夹下的所有.cc文件
  file(GLOB SOURCES "${DIR}/*.cc")

  # 添加可执行目标
  add_executable(${DIR_NAME} ${SOURCES})
endforeach()

# 遍历test template文件夹
file(GLOB TEST_TEMPLATE "./test_template/*.cc")
foreach(TEST_TARGET ${TEST_TEMPLATE})
  # 获取 .cc 文件的名称（不包含扩展名）
  get_filename_component(TEST_NAME ${TEST_TARGET} NAME_WE)

  # 添加可执行目标
  add_executable(${TEST_NAME} ${TEST_TARGET})

  # 如果是 moveable_objects，则添加链接 HeavyObject.cc
  if(${TEST_NAME} STREQUAL "moveable_objects")
    target_sources(${TEST_NAME} PRIVATE "./test_template/HeavyObject.cc")
  endif()

endforeach()
