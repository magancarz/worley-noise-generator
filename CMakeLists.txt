cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)

project(worley-noise-generator LANGUAGES C CXX)

file(GLOB_RECURSE APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp)
add_executable(worley-noise-generator ${APP_SOURCES})
target_include_directories(worley-noise-generator PUBLIC Include)
target_include_directories(worley-noise-generator PUBLIC ThirdParty)
