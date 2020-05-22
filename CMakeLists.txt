cmake_minimum_required(VERSION 3.10)
project(SCZR-project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/Consumer)
add_subdirectory(src/Producer)
add_subdirectory(src/Others)

# Consumer
add_executable(Consumer-app src/Consumer/main.cpp)
target_link_libraries(Consumer-app consumer-lib others-lib)
target_include_directories(Consumer-app PRIVATE src/Consumer)

# Producer
add_executable(Producer-app src/Producer/main.cpp)
target_link_libraries(Producer-app producer-lib others-lib)
target_include_directories(Producer-app PRIVATE src/Consumer)

add_compile_options(
        #        -Werror
        -Wall
        -Wextra
        -Wpedantic
        #
        #        -Wcast-align
        #        -Wcast-qual
        #        -Wconversion
        #        -Wctor-dtor-privacy
        #        -Wenum-compare
        #        -Wfloat-equal
        #        -Wnon-virtual-dtor
        #        -Wold-style-cast
        #        -Woverloaded-virtual
        #        -Wredundant-decls
        #        -Wsign-conversion
        #        -Wsign-promo
)