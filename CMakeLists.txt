cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME tennis)
project(${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin
     )