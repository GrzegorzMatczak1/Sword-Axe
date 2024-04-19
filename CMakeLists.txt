cmake_minimum_required(VERSION 3.5)

project(omegatitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(omegatitled main.cpp
    inventory.h
    inventory_source.cpp
    item.h
    item_source.cpp)

include(GNUInstallDirs)
install(TARGETS omegatitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
