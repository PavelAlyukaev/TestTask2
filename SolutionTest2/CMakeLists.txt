cmake_minimum_required(VERSION 3.26)
project(untitled6)

# Установка стандарта C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление директории с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/Lib/include)

# Список исходных файлов
set(SOLUTION main.cpp)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOLUTION})

# Подключение библиотеки Lib
target_link_libraries(${PROJECT_NAME} PRIVATE Lib)