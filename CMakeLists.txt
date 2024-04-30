cmake_minimum_required(VERSION 3.5)

project(omg_last_steps LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(omg_last_steps main.cpp
    inventory.h
    inventory_source.cpp
    item.h
    items.h
    rarity.h
    shop.h)

include(GNUInstallDirs)
install(TARGETS omg_last_steps
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
