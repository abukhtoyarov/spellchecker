cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(APP_NAME spellchecker)
set(SRC src/main.cpp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${APP_NAME})

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt  # or relative build/conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

add_executable(${APP_NAME} ${SRC})
target_compile_options(${APP_NAME} PUBLIC 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    )

include(GoogleTest)
enable_testing()

add_executable(runUnitTests
    test/distance_test.cpp
    test/bktree_test.cpp
    test/spellchecker_test.cpp
    )

target_compile_options(runUnitTests PUBLIC 
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Werror>
    )
target_link_libraries(runUnitTests gtest gtest_main)
gtest_discover_tests(runUnitTests)
