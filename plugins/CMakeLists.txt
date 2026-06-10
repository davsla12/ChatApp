cmake_minimum_required(VERSION 3.16)
project(ClientServerProject)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -g ) #-fsanitize=address)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)

add_library(MF
    ../MF/String.cpp
)

target_include_directories(MF PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

add_library(commands SHARED
    commands/commands.cpp
)
target_link_libraries(commands PRIVATE MF)

add_library(msg SHARED
    msg/init.cpp
    msg/commands.cpp
)
target_link_libraries(msg PRIVATE MF)
