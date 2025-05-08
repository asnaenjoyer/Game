project(Game)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(vendor)
target_link_libraries(MyAPI)