cmake_minimum_required(VERSION 3.16)

FILE(GLOB SOURCES ./src/*.cpp)

FILE(GLOB HEADERS ./headers/*.h)

add_executable(
    SortingAlgorithms
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(
    SortingAlgorithms
    PRIVATE
    ./headers/
)

target_link_libraries(SortingAlgorithms
    PRIVATE
    GL
    imgui
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

target_compile_definitions(SortingAlgorithms
    PRIVATE
    RSC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/rsc/"
)