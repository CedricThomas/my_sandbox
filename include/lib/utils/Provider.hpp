//
// Created by arzad on 17/01/2022.
//

#ifndef APP_PROVIDER_HPP
#define APP_PROVIDER_HPP

#include <string>
#include <map>
#include <memory>
#include <functional>
#include <stdexcept>
#include "spdlog/spdlog.h"

enum class ProviderType {
    RENDERING,
    WORLD,
    NETWORK,
};

class Provider {
public:
    Provider(Provider const &) = delete;

    void operator=(Provider const &) = delete;

    static Provider &getInstance(ProviderType type) {
        static std::map<ProviderType, std::unique_ptr<Provider>> _instances;
        if (_instances.find(type) == _instances.end()) {
            _instances.emplace(type, std::unique_ptr<Provider>(new Provider()));
        }
        return *_instances[type].get();
    }

    template<typename T>
    void share(const std::string &key, T *value) {
        if (_store.find(key) != _store.end())
            remove(key);
        _store.insert(std::make_pair(key, value));
    }

    template<typename T>
    void store(const std::string &key, T *value, std::function<void(void const *)> &&deleter) {
        if (_store.find(key) != _store.end())
            remove(key);
        _store.insert(std::make_pair(key, value));
        _deleters.insert(std::make_pair(key, deleter));
    }

    template<typename T>
    void store(const std::string &key, T *value) {
        this->store(key, value, [](void const *data) {
            T const *p = static_cast<T const *>(data);
            delete p;
        });
    }

    template<typename T>
    T *provide(const std::string &key) const {
        try {
            return reinterpret_cast<T *>(_store.at(key));
        } catch (const std::out_of_range &e) {
            spdlog::error("Provider: {}", e.what());
            std::exit(EXIT_FAILURE);
        }
    }

    void remove(const std::string &key) {
        try {
            if (_deleters.find(key) != _deleters.end()) {
                _deleters.at(key)(_store.at(key));
            }
            _store.erase(key);
            _deleters.erase(key);
        } catch (const std::out_of_range &e) {
            spdlog::error("Provider: {}", e.what());
            std::exit(EXIT_FAILURE);
        }
    }

    virtual ~Provider() = default;

private:

    Provider() = default;
    std::map<std::string, void *> _store;
    std::map<std::string, std::function<void(void *)>> _deleters;
};

#endif //APP_PROVIDER_HPP
