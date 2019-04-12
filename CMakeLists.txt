cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(APP_NAME spellchecker)

project(${APP_NAME})

add_executable(${APP_NAME} src/main.cpp)

target_compile_options(${APP_NAME} PUBLIC 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-variable>
    )