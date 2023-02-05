//
// Created by arzad on 23/02/2022.
//

#include <utility>
#include "world/World.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "protocol/world/LoadChunk.hpp"
#include "protocol/world/UnloadChunk.hpp"
#include "protocol/game/Types.hpp"
#include "protocol/game/Move.hpp"
#include "protocol/game/Join.hpp"
#include "application/game/renderer/voxel/Mesher.hpp"

World::World(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldEventTopic, std::shared_ptr<BundleAtlas> bundleAtlas)
        : _worldEventTopic(std::move(worldEventTopic)), _bundleAtlas(std::move(bundleAtlas)) {}

[[noreturn]] void World::start() {
    Message<GameEvent> event;
    bool hasEvent;
    auto radius = 2;

    Flat3DArray<BlockTemplateBundledID> chunkData(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT / 10; y++) {
            for (auto z = 0; z < CHUNK_WIDTH; z++) {
                if ((x + y + z) % 2 == 0) {
                    continue;
                }
                if (y == CHUNK_HEIGHT / 10 - 1) {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 2));
                } else if (y < CHUNK_HEIGHT / 10 - 5) {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 3));
                } else {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 1));
                }
            }
        }
    }

    glm::vec2 oldPosition = glm::vec2(0, 0);
    glm::vec2 newPosition = glm::vec2(0, 0);
    while (true) {
        hasEvent = _worldEventTopic->tryPull(event);
        if (!hasEvent) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
    
        Move *move;
        Join *join;
        switch (static_cast<GameEventType>(event.data->getType())) {
            case GameEventType::MOVE:
                spdlog::debug("Received move event");
                move = dynamic_cast<Move *>(event.data.get());
                newPosition = glm::vec2((int)(move->position.x / CHUNK_GAP), (int)(move->position.z / CHUNK_GAP));
                if (newPosition != oldPosition) {
                    spdlog::info("MOVED TO ({},{})", newPosition.x, newPosition.y);
                    _worldEventTopic->publishToSubcriber(
                            event.origin,
                            std::make_shared<LoadChunk>(
                                    newPosition,
                                    chunkData
                            )
                    );
                    oldPosition = newPosition;
                }
                break;
            case GameEventType::JOIN:
                join = dynamic_cast<Join *>(event.data.get());
                oldPosition = glm::vec2((int)(join->position.x / CHUNK_GAP), (int)(join->position.z / CHUNK_GAP));
                spdlog::info("JOINED ({},{})", join->position.x, join->position.y);
                _worldEventTopic->publishToSubcriber(
                        event.origin,
                        std::make_shared<LoadChunk>(
                                oldPosition,
                                chunkData
                        )
                );
                break;
        }
    }
}
