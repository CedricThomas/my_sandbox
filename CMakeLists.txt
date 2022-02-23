cmake_minimum_required(VERSION 3.13)  # CMake version check
project(app)                          # Create project "app"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES
        include/lib/khrplatform.h
        include/lib/glad.h
        src/lib/glad.c
        src/main.cpp
        src/renderer/Renderer.cpp
        include/renderer/Renderer.hpp
        src/renderer/RendererException.cpp
        include/renderer/RendererException.hpp
        src/renderer/RenderableModule.cpp
        include/renderer/RenderableModule.hpp
        src/renderer/modules/TutoModule.cpp
        include/renderer/modules/TutoModule.hpp
        include/lib/utils/Provider.hpp
        include/renderer/tools/Shader.hpp
        src/renderer/tools/Shader.cpp
        src/lib/utils/ResourcesManager.cpp
        include/lib/utils/ResourcesManager.hpp
        include/lib/stb_image.h
        src/lib/stb_image.c
        include/lib/interfaces/FlatArray.hpp
        include/renderer/tools/Camera.hpp
        src/renderer/tools/Camera.cpp
        include/lib/interfaces/Observer.hpp
        include/lib/interfaces/Observable.hpp
        src/server/Server.cpp
        include/server/Server.hpp
        src/world/World.cpp
        include/world/World.hpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(app ${SOURCE_FILES})

# Setup OPENGL
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw-3.3.6)
include_directories(lib/glfw-3.3.6/include)
find_package(OpenGL REQUIRED)

target_link_libraries(app glfw)
target_link_libraries(app OpenGL::GL)

# Setup log library
add_subdirectory(lib/spdlog)
include_directories(lib/spdlog/include)
target_link_libraries(app spdlog::spdlog)

# Setup GLM library
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_LIBRARY_DIRS})
add_definitions(${GLM_DEFINITIONS})
