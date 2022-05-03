cmake_minimum_required(VERSION 3.13)  # CMake version check
project(app)                          # Create project "app"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)


set(PROTOCOL_SRC
        include/world/Events.hpp
        include/application/game/Events.hpp
)

set(BUNDLING_SRC
        include/bundling/DefaultBlockBundle.hpp

        src/bundling/Bundle.cpp
        include/bundling/Bundle.hpp

        src/bundling/BundleAtlas.cpp
        include/bundling/BundleAtlas.hpp
)

set(WORLD_SRC
        src/world/World.cpp
        include/world/World.hpp
        src/world/blocks/BlockTemplate.cpp
        include/world/blocks/BlockTemplate.hpp
)

set(APPLICATION_SRC
        src/application/Application.cpp
        include/application/Application.hpp

        src/application/ApplicationException.cpp
        include/application/ApplicationException.hpp

        src/application/game/renderer/ARenderer.cpp
        include/application/game/renderer/ARenderer.hpp

        src/application/game/renderer/voxel/VoxelRenderer.cpp
        include/application/game/renderer/voxel/VoxelRenderer.hpp

        include/application/game/renderer/Shader.hpp
        src/application/game/renderer/Shader.cpp

        include/application/game/Camera.hpp
        src/application/game/Camera.cpp

        src/application/game/renderer/RenderingTracker.cpp
        include/application/game/renderer/RenderingTracker.hpp

        src/application/game/renderer/voxel/containers/Vertex.cpp
        include/application/game/renderer/voxel/containers/Vertex.hpp

        src/application/game/renderer/voxel/containers/Quad.cpp
        include/application/game/renderer/voxel/containers/Quad.hpp

        src/application/game/renderer/voxel/containers/QuadBuffer.cpp
        include/application/game/renderer/voxel/containers/QuadBuffer.hpp

        src/application/game/renderer/voxel/Mesher.cpp
        include/application/game/renderer/voxel/Mesher.hpp

        src/application/game/textures/TextureAtlas.cpp
        include/application/game/texture/TextureAtlas.hpp

        src/application/game/textures/Texture.cpp
        include/application/game/texture/Texture.hpp

        src/application/game/renderer/skybox/SkyboxRenderer.cpp
        include/application/game/renderer/skybox/SkyboxRenderer.hpp

        src/application/game/Game.cpp
        include/application/game/Game.hpp

        include/application/game/AGame.hpp
        src/application/game/AGame.cpp
)

set(GRAPHIC_LIB_SRC
        include/lib/graphics/khrplatform.h

        include/lib/graphics/glad.h
        src/lib/graphics/glad.c

        include/lib/graphics/stb_image.h
        include/lib/graphics/stb_image_write.h
        src/lib/graphics/stb_image.c
)

set(SERVER_SRC
        src/server/Enet.cpp
        include/server/Enet.hpp

        src/server/Server.cpp
        include/server/Server.hpp

        src/server/Client.cpp
        include/server/Client.hpp
)

set(COMMON_LIB_SRC
        include/lib/config.hpp

        include/lib/enet.h

        src/lib/Pool.cpp
        include/lib/Pool.hpp

        include/lib/containers/PairHash.hpp
        include/lib/containers/concurrentqueue.h
        include/lib/containers/Flat3DArray.hpp

        include/lib/broker/MessageBroker.hpp
        include/lib/broker/Topic.hpp
        include/lib/broker/AsyncSubscription.hpp
        include/lib/broker/SyncSubscription.hpp
        include/lib/broker/ASubscription.hpp

        src/lib/resources/ResourcesFinder.cpp
        include/lib/resources/ResourcesFinder.hpp
        include/lib/resources/Resource.hpp
        include/lib/resources/ResourceNotFound.hpp
)

set(APPLICATION_SRC
        ${PROTOCOL_SRC}
        ${BUNDLING_SRC}
        ${WORLD_SRC}
        ${APPLICATION_SRC}
        ${GRAPHIC_LIB_SRC}
        ${SERVER_SRC}
        ${COMMON_LIB_SRC}
        src/app.cpp
        include/lib/broker/ASubscription.hpp)

set(SERVER_SRC
        ${PROTOCOL_SRC}
        ${BUNDLING_SRC}
        ${WORLD_SRC}
        ${SERVER_SRC}
        ${COMMON_LIB_SRC}
        src/server.cpp
)

# Setup OPENGL
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw-3.3.6)
include_directories(lib/glfw-3.3.6/include)
find_package(OpenGL REQUIRED)

# Setup log library
add_subdirectory(lib/spdlog)
include_directories(lib/spdlog/include)

# Setup GLM library
include_directories(lib/glm)

# Declaring the targets
add_executable(app ${APPLICATION_SRC})
target_link_libraries(app glfw)
target_link_libraries(app OpenGL::GL)
target_link_libraries(app spdlog::spdlog)


add_executable(server ${SERVER_SRC})
target_link_libraries(server spdlog::spdlog)
