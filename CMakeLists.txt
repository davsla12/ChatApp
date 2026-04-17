cmake_minimum_required(VERSION 3.16)
project(ClientServerProject)

set(CMAKE_CXX_STANDARD 17)

# =====================
# CLIENT
# =====================
add_executable(client
    client/client.cpp
    client/server.cpp
)

# =====================
# SERVER
# =====================
add_executable(server
    server/server.cpp
)
find_library(ENET_LIBRARY enet)

target_include_directories(client PRIVATE ${ENET_INCLUDE_DIR})
target_link_libraries(client PRIVATE ${ENET_LIBRARY})

target_include_directories(server PRIVATE ${ENET_INCLUDE_DIR})
target_link_libraries(server PRIVATE ${ENET_LIBRARY})
