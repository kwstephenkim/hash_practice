cmake_minimum_required(VERSION 3.16)
project(hash_impl)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(src)

add_compile_options("-Wall" "-g3" "-ggdb" "-O0" "-fsanitize=address")
add_link_options("-fsanitize=address")

add_library(
  custom_hash SHARED
  src/custom_hash.cc
  )

add_executable(
  test_main
  tests/test_hash.cc
  tests/test_main.cc
  )

target_link_libraries(
  test_main
  custom_hash
  gtest_main
  )

include(GoogleTest)
gtest_discover_tests(test_main)

