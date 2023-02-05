#include "spdlog/spdlog.h"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "lib/broker/MessageBroker.hpp"
#include "lib/config.hpp"
#include "server/Server.hpp"
#include "server/Enet.hpp"

static void configure(std::shared_ptr<BundleAtlas> &bundleAtlas) {
    ENET::init();
    ResourcesFinder::root(RESOURCES_FOLDER);
    bundleAtlas->registerBundle(DEFAULT_BUNDLE);
}

static void start(std::shared_ptr<BundleAtlas> &bundleAtlas) {
    MessageBroker<WorldEvent, GameEvent> broker;
    auto topic = broker.createTopic(WORLD_EVENT_TOPIC);
    Pool pool(3, 3);

    World world(topic, bundleAtlas);
    pool.addJob([&]() {
        Server server(
                topic,
                7777
        );
        server.start();
    });
    world.start();
    pool.shutdown();
}

int main() {
    spdlog::set_level(spdlog::level::info); // Set global log level to debug
    auto bundleAtlas = std::make_shared<BundleAtlas>();
    configure(bundleAtlas);
    start(bundleAtlas);
    return 0;
}
