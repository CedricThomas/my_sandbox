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
    while (true) {
        hasEvent = _worldEventTopic->tryPull(event);
        if (!hasEvent) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        Move *move;
        switch (static_cast<GameEventType>(event.data->getType())) {
            case GameEventType::MOVE:
                spdlog::info("Received move event");
                move = dynamic_cast<Move *>(event.data.get());
                auto newPosition = glm::vec2(move->position.x / CHUNK_GAP, move->position.y / CHUNK_GAP);
                if (newPosition != oldPosition) {
                    spdlog::info("Moving from ({},{}) to ({},{})", oldPosition.x, oldPosition.y, newPosition.x, newPosition.y);
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
        }
    }
}
