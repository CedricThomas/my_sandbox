#include "server/Enet.hpp"
#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "lib/Pool.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "application/game/texture/TextureAtlas.hpp"
#include "application/game/Game.hpp"
#include "lib/broker/MessageBroker.hpp"
#include "lib/config.hpp"
#include "server/Client.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void server(const std::shared_ptr<Topic<WorldEvent, GameEvent>> &worldTopic) {
}

void client(const std::shared_ptr<ASubscription<WorldEvent, GameEvent>> &remoteWorld) {
}

int main() {
    // global variables and configuration
    spdlog::set_level(spdlog::level::debug);   
    ENET::init();
    Pool pool(4, 4);

    MessageBroker<WorldEvent, GameEvent> broker;
    auto worldTopic = broker.createTopic(WORLD_EVENT_TOPIC);
    auto worldTopicSubscription = worldTopic->createAsyncSubscribe(LOCAL_GAME_EVENT_SUBSCRIPTION);

    // pool.addJob([&]() {
    // spdlog::debug("Listening to the game events...");
    // server(worldTopic);
    // });

    // spdlog::debug("Listening to the server events...");
    // client(worldTopicSubscription);
    // pool.shutdown();
}