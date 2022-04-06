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
        src/application/Application.cpp
        include/application/Application.hpp
        src/application/ApplicationException.cpp
        include/application/ApplicationException.hpp
        src/application/renderer/ARenderer.cpp
        include/application/ARenderer.hpp
        src/application/renderer/Renderer.cpp
        include/application/renderer/Renderer.hpp
        include/lib/utils/Provider.hpp
        include/application/renderer/Shader.hpp
        src/application/renderer/Shader.cpp
        src/lib/utils/ResourcesManager.cpp
        include/lib/utils/ResourcesManager.hpp
        include/lib/stb_image.h
        include/lib/stb_image_write.h
        src/lib/stb_image.c
        include/lib/containers/Flat3DArray.hpp
        include/lib/containers/Flat2DArray.hpp
        include/application/renderer/Camera.hpp
        src/application/renderer/Camera.cpp
        include/lib/interfaces/Observer.hpp
        include/lib/interfaces/Observable.hpp
        src/server/Server.cpp
        include/server/Server.hpp
        src/world/World.cpp
        include/world/World.hpp
        src/application/renderer/RenderingTracker.cpp
        include/application/renderer/RenderingTracker.hpp
        src/lib/Pool.cpp
        include/lib/Pool.hpp
        src/application/renderer/containers/Vertex.cpp
        include/application/renderer/containers/Vertex.hpp
        src/application/renderer/containers/Quad.cpp
        include/application/renderer/containers/Quad.hpp
        src/application/renderer/containers/QuadBuffer.cpp
        include/application/renderer/containers/QuadBuffer.hpp
        include/lib/containers/TQueue.hpp
        src/application/renderer/Mesher.cpp
        include/application/renderer/Mesher.hpp)

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
include_directories(lib/glm)
