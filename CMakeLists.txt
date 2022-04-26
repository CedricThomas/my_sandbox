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
        src/application/game/renderer/ARenderer.cpp
        include/application/game/renderer/ARenderer.hpp
        src/application/game/renderer/voxel/VoxelRenderer.cpp
        include/application/game/renderer/voxel/VoxelRenderer.hpp
        include/lib/Provider.hpp
        include/application/game/renderer/Shader.hpp
        src/application/game/renderer/Shader.cpp
        src/lib/resources/ResourcesFinder.cpp
        include/lib/resources/ResourcesFinder.hpp
        include/lib/stb_image.h
        include/lib/stb_image_write.h
        src/lib/stb_image.c
        include/lib/containers/Flat3DArray.hpp
        include/lib/containers/Flat2DArray.hpp
        include/application/game/Camera.hpp
        src/application/game/Camera.cpp
        include/lib/interfaces/Observer.hpp
        include/lib/interfaces/Observable.hpp
        src/server/Server.cpp
        include/server/Server.hpp
        src/world/World.cpp
        include/world/World.hpp
        src/application/game/renderer/RenderingTracker.cpp
        include/application/game/renderer/RenderingTracker.hpp
        src/lib/Pool.cpp
        include/lib/Pool.hpp
        src/application/game/renderer/voxel/containers/Vertex.cpp
        include/application/game/renderer/voxel/containers/Vertex.hpp
        src/application/game/renderer/voxel/containers/Quad.cpp
        include/application/game/renderer/voxel/containers/Quad.hpp
        src/application/game/renderer/voxel/containers/QuadBuffer.cpp
        include/application/game/renderer/voxel/containers/QuadBuffer.hpp
        include/lib/containers/TQueue.hpp
        src/application/game/renderer/voxel/Mesher.cpp
        include/application/game/renderer/voxel/Mesher.hpp
        src/application/game/textures/TextureAtlas.cpp
        include/application/game/texture/TextureAtlas.hpp
        include/lib/resources/ResourceNotFound.hpp
        include/lib/resources/Resource.hpp src/world/blocks/BlockTemplate.cpp
        include/world/blocks/BlockTemplate.hpp
        include/bundling/DefaultBlockBundle.hpp
        include/lib/containers/PairHash.hpp
        src/bundling/Bundle.cpp
        include/bundling/Bundle.hpp
        src/bundling/BundleAtlas.cpp
        include/bundling/BundleAtlas.hpp
        src/application/game/textures/Texture.cpp
        include/application/game/texture/Texture.hpp
        src/application/game/renderer/skybox/SkyboxRenderer.cpp
        include/application/game/renderer/skybox/SkyboxRenderer.hpp
        src/application/game/Game.cpp
        include/application/game/Game.hpp
)

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
