cmake_minimum_required(VERSION 3.16)
project(ClientServerProject)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -g -O0)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)

# =====================
# CLIENT
# =====================
add_executable(client
    client/client.cpp
    client/server.cpp
    client/Scanes/Log.cpp
    client/Scanes/Input.cpp
)

# =====================
# SERVER
# =====================
add_executable(server
    server/server.cpp
    server/plugins.cpp
    server/helpers.cpp
    server/users.cpp
    server/commands.cpp
)

find_library(ENET_LIBRARY enet)
find_package(Curses REQUIRED)
add_library(MF
    MF/screen.cpp
    MF/Random.cpp
    MF/sprites.cpp
    MF/String.cpp
)

target_include_directories(client PRIVATE ${ENET_INCLUDE_DIR})
target_include_directories(MF PUBLIC
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(client PRIVATE ${ENET_LIBRARY} MF ${CURSES_LIBRARIES})

target_include_directories(server PRIVATE ${ENET_INCLUDE_DIR})
target_include_directories(MF PUBLIC
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(server PRIVATE ${ENET_LIBRARY} MF ${CURSES_LIBRARIES})
