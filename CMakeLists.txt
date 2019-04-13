cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(APP_NAME spellchecker)
set(SRC src/main.cpp)

project(${APP_NAME})
add_executable(${APP_NAME} ${SRC})
target_compile_options(${APP_NAME} PUBLIC 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-variable>
    )

enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
add_executable(runUnitTests
    test/distance_test.cpp
    test/bktree_test.cpp
    )

target_compile_options(runUnitTests PUBLIC 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-variable>
    )

target_include_directories(runUnitTests PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(runUnitTests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})

