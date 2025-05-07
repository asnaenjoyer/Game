add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC
Image/ImageLoader.cpp
Objects/Cell.cpp
App.cpp
Objects/Grid.cpp
main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)


