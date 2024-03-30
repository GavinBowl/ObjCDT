cmake_minimum_required(VERSION 3.20)

project(ObjCDT VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(cmake/CPM.cmake)
include(cmake/depend.cmake)

add_executable(ObjCDT main.cpp
                src/mesh.cpp
                src/surface_mesh.cpp)
                
target_include_directories(ObjCDT PUBLIC include)

target_link_libraries(ObjCDT PUBLIC spdlog::spdlog spdlog::spdlog_header_only
                                    CLI11::CLI11
                                    Eigen3::Eigen
                                    OpenMeshCore OpenMeshTools
                                    CDT)

