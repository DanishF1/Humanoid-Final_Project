cmake_minimum_required(VERSION 3.10)
project(app LANGUAGES CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Default ke Release kalau tidak ditentukan
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
 
add_executable(app app.cpp)
 
# json.hpp ada di folder yang sama dengan app.cpp
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
 
target_compile_options(app PRIVATE -Wall -Wextra)
