cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(SecondaryFS VERSION 1.0)

# 指定C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含目录
include_directories(includes)

# 添加源代码文件
add_executable(SecondaryFS
    main.cpp
    BufferSubSystem/BufferManager.cpp
    DiskSubSystem/DiskManager.cpp
    FileSubSystem/File.cpp
    FileSubSystem/FileManager.cpp
    FileSubSystem/FileSystem.cpp
    FileSubSystem/INode.cpp
    FileSubSystem/OpenFileManager.cpp
    Kenel/Kernel.cpp
    Kenel/Space.cpp
    Kenel/State.cpp
)