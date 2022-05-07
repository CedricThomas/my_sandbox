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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static void configure(std::shared_ptr<BundleAtlas> &bundleAtlas, std::shared_ptr<TextureAtlas> &textureAtlas) {
    auto application = Application::getInstance();

    ResourcesFinder::root(RESOURCES_FOLDER);
    bundleAtlas->registerBundle(DEFAULT_BUNDLE);
    textureAtlas->loadBundleBlockTextures(DEFAULT_BUNDLE);
    textureAtlas->generateAtlas();
    application->configure({
                                   SCR_WIDTH,
                                   SCR_HEIGHT,
                                   "Application",
                           });
    ENET::init();
}

static void start(std::shared_ptr<BundleAtlas> &bundleAtlas, std::shared_ptr<TextureAtlas> &textureAtlas) {
    auto application = Application::getInstance();
    MessageBroker<WorldEvent, GameEvent> broker;
    auto worldTopic = broker.createTopic(WORLD_EVENT_TOPIC);
    auto gameSubscription = broker.createAsyncSubscription(WORLD_EVENT_TOPIC, LOCAL_GAME_EVENT_SUBSCRIPTION);
    Client client(worldTopic, gameSubscription, "127.0.0.1", 7777);
    Pool pool(3, 3);

    application->registerGame(
            std::make_unique<Game>(
                    application,
                    broker.createAsyncSubscription(
                            WORLD_EVENT_TOPIC,
                            LOCAL_GAME_EVENT_SUBSCRIPTION
                    ),
                    bundleAtlas,
                    textureAtlas
            )
    );
    pool.addJob([&]() {
        client.listenGame();
    });

    pool.addJob([&]() {
        client.listenServer();
    });
    application->start();
    pool.shutdown();
}


int main() {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    auto bundleAtlas = std::make_shared<BundleAtlas>();
    auto textureAtlas = std::make_shared<TextureAtlas>();
    configure(bundleAtlas, textureAtlas);
    start(bundleAtlas, textureAtlas);
    return 0;
}
