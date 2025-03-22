cmake_minimum_required(VERSION 3.10)
project(d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исходные файлы
file(GLOB SOURCES simple.cpp)


find_package(VTK REQUIRED COMPONENTS CommonColor CommonCore FiltersSources RenderingCore IOXML)
include(${VTK_USE_FILE})


add_executable(d ${SOURCES} ${HEADERS})


add_library(vtk SHARED IMPORTED)
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/mnt/d/User/Documents/cpp/ondulator/lib/libgmsh.so.4.13"
    INTERFACE_INCLUDE_DIRECTORIES "/mnt/d/User/Documents/cpp/ondulator/include"
)
set(GMSH_LIBRARY gmsh)


target_link_libraries(${PROJECT_NAME} PUBLIC ${VTK_LIBRARIES} ${GMSH_LIBRARY})


vtk_module_autoinit(
  TARGETS d
  MODULES ${VTK_LIBRARIES}
)
