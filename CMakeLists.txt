cmake_minimum_required(VERSION 3.23)
project(droidtool C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED On)

add_subdirectory(source/modules/casper3)

add_executable(droidtool)
target_sources(droidtool PRIVATE
        source/main_thread.c
        source/context.c
        source/platform/non_ansi.c
        source/memory/manager_wrap.c
        source/cpu/device.c
        source/abyss/produce.c
        source/collect/bitmap.c
        source/backend/module.c
        source/backend/back_system.c
        source/archive/directory.c
        source/archive/entries_check.c
        source/archive/unit.c)

target_include_directories(droidtool PRIVATE source)
target_include_directories(casper3 PRIVATE source/backend)
install(TARGETS droidtool CONFIGURATIONS Debug RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/runtime)

if (UNIX)
    install(TARGETS casper3 CONFIGURATIONS Debug LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/runtime/modules)
elseif(WIN32)
    install(TARGETS casper3 CONFIGURATIONS Debug RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/runtime/modules)
endif()
