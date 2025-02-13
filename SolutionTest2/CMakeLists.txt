cmake_minimum_required(VERSION 3.26)
project(Solution2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/Lib/include)

set(SOLUTION main.cpp)

add_executable(${PROJECT_NAME} ${SOLUTION})

target_link_libraries(${PROJECT_NAME} PRIVATE Lib)