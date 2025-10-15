cmake_minimum_required(VERSION 3.16)
project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
  set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/windows)
else()
  set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib/linux)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(COPY ${LIB_DIR}/libleveldb.a DESTINATION ${CMAKE_BINARY_DIR}/lib)
file(COPY ${LIB_DIR}/libraylib.a DESTINATION ${CMAKE_BINARY_DIR}/lib)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

set(RAYLIB "${CMAKE_BINARY_DIR}/lib/libraylib.a")
set(LEVELDB "${CMAKE_BINARY_DIR}/lib/libleveldb.a")

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(game ${SRC_FILES})

target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(game PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
  target_link_libraries(game PRIVATE
    ${RAYLIB}
    ${LEVELDB}
    opengl32
    gdi32
    winmm
  )
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(game PRIVATE "-static" "-static-libgcc" "-static-libstdc++")
  endif()
else()
  target_compile_options(game PRIVATE -fno-pie)
  target_link_options(game PRIVATE -no-pie)
  target_link_libraries(game PRIVATE
    ${RAYLIB}
    m
    dl
    pthread
    GL
    rt
    X11
    ${LEVELDB}
  )
endif()
