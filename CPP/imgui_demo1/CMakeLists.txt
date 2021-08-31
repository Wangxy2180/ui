cmake_minimum_required(VERSION 3.10.2)
project(imgui_demo1)

set(CMAKE_CXX_STANDARD 11)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR ../../thirdparty/imgui)


include_directories(
    ${IMGUI_DIR}
    ${OPENGL_INCLUDE_DIR}

)

message(${IMGUI_DIR})

# message(${GLEW})
# message(${glfw3})
# message(${OpenGL})
message(${OPENGL_FOUND})
message(${OPENGL_LIBRARIES})
message(${GLEW_LIBRARIES})







add_executable(${PROJECT_NAME} imgui_demo1.cpp 
${IMGUI_DIR}/imgui.cpp
${IMGUI_DIR}/imgui_demo.cpp
${IMGUI_DIR}/imgui_draw.cpp
${IMGUI_DIR}/imgui_tables.cpp
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
${IMGUI_DIR}/backends/imgui_impl_glfw.cpp)

# pkg-config --static --libs glfw3
target_link_libraries(${PROJECT_NAME} 
${OPENGL_LIBRARIES} 
${GLEW_LIBRARIES} 
glfw
dl)
