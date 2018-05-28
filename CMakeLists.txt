cmake_minimum_required(VERSION 2.8.8)
project(bignumber)

# включаем отладочную информацию: -g
# включаем C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -O2")

# заводим констранты, которые будем использовать в поддиректориях
set(LIB_NAME "${PROJECT_NAME}_lib")
set(BIN_NAME "${PROJECT_NAME}")
set(TESTS_NAME "${PROJECT_NAME}_tests")

# статическая библиотека
add_library(${LIB_NAME} STATIC
        big.cpp
        )
set_target_properties(${LIB_NAME} PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
        INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
        )

# исполняемый файл
add_executable(${PROJECT_NAME}
        main.cpp
        )
target_link_libraries(${PROJECT_NAME}
        ${LIB_NAME}
        )
