cmake_minimum_required(VERSION 3.13.4)
project(llvm-funcblockcount)

# Add the location of LLVMConfig.cmake to CMake search paths (so that
# find_package can locate it)
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/llvm-13/lib/cmake/llvm/")

# find_package(LLVM 11.0.0 REQUIRED CONFIG) instead.
find_package(LLVM REQUIRED CONFIG)
if(NOT "13" VERSION_LESS "${LLVM_VERSION_MAJOR}")
    message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM-13")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: /usr/lib/llvm-13")

message("LLVM STATUS:
    Definition ${LLVM_DEFINITIONS}
    Includes ${LLVM_INCLUDE_DIRS}
    Libraries ${LLVM_LIBRARY_DIRS}")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

#===============================================================================
# 3. ADD THE TARGET
#===============================================================================
add_library(SamplePass SHARED SamplePass.cpp)

# Allow undefined symbols in shared objects on Darwin (this is the default
# behaviour on Linux)
target_link_libraries(SamplePass
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")
