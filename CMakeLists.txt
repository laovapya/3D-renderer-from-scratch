cmake_minimum_required(VERSION 3.15)
project(3D_Renderer)

# Enforce vcpkg 
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(WARNING "CMAKE_TOOLCHAIN_FILE not set. vcpkg integration may fail.")
endif()

# Find packages 
find_package(glfw3 REQUIRED CONFIG)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

# Setup ImGui (Docking Branch)
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)


target_compile_definitions(imgui PRIVATE 
    IMGUI_ENABLE_DOCKING
    IMGUI_ENABLE_VIEWPORTS
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/backends

)

target_link_libraries(imgui PRIVATE glfw)

# Main executable 
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(MyApp ${SOURCES})

# Define shader directory 
target_compile_definitions(MyApp PRIVATE 
    SHADER_DIR="${CMAKE_SOURCE_DIR}/assets/"
)

target_link_libraries(MyApp PRIVATE
    glfw
    glad::glad
    glm::glm
    imgui
)

target_include_directories(MyApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics_Abstraction
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utility
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Interaction
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Rendering
    ${CMAKE_CURRENT_SOURCE_DIR}/src/3D_Objects
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui
    
)

