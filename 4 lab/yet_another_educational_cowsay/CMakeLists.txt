cmake_minimum_required(VERSION 3.10)
project(cowsay)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исходные файлы
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(cowsay ${SOURCES} ${HEADERS})

# Указываем директорию заголовочных файлов
include_directories(include)