cmake_minimum_required(VERSION 3.5)

project(untitled3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled3 main.cpp
    inventory.h
    inventory_source.cpp
    item.h
    item_source.cpp
    expedition_source.cpp
    expedition.h)

include(GNUInstallDirs)
install(TARGETS untitled3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
