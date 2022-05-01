#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "lib/broker/MessageBroker.hpp"
#include "application/game/Events.hpp"
#include "lib/config.hpp"

static void configure(std::shared_ptr<BundleAtlas> &bundleAtlas) {
    ResourcesFinder::root(RESOURCES_FOLDER);
    bundleAtlas->registerBundle(DEFAULT_BUNDLE);
}

static void start(std::shared_ptr<BundleAtlas> &bundleAtlas) {
    MessageBroker<WorldEvent, GameEvent> broker;
    auto topic = broker.createTopic(WORLD_EVENT_TOPIC);
//    Pool pool(1, 2);
}

int main() {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    auto bundleAtlas = std::make_shared<BundleAtlas>();
    configure(bundleAtlas);
    start(bundleAtlas);
    return 0;
}
