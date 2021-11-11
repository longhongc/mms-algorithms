project(mms-algorithms)
cmake_minimum_required(VERSION 3.10)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(MyLibs
    ${PROJECT_SOURCE_DIR}/src/API.cpp
    ${PROJECT_SOURCE_DIR}/src/util.cpp
    ${PROJECT_SOURCE_DIR}/src/map.cpp
    ${PROJECT_SOURCE_DIR}/src/mouse.cpp
)

add_executable(offline_DFS ${PROJECT_SOURCE_DIR}/src/offline_DFS.cpp)
target_link_libraries(offline_DFS MyLibs)

add_executable(online_DFS ${PROJECT_SOURCE_DIR}/src/online_DFS.cpp)
target_link_libraries(online_DFS MyLibs)

install(TARGETS offline_DFS DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS online_DFS DESTINATION ${PROJECT_SOURCE_DIR}/bin)
