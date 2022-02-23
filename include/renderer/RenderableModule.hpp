//
// Created by arzad on 16/01/2022.
//

#ifndef APP_RENDERABLEMODULE_HPP
#define APP_RENDERABLEMODULE_HPP

#include <string>
#include "lib/utils/Provider.hpp"

class Renderer;

class RenderableModule {
public:
    explicit RenderableModule(std::string name);

    virtual void onInit(const Provider &provider);

    virtual void onInput(const Provider &provider);

    virtual void onRender(const Provider &provider);

    virtual void onCleanup(const Provider &provider);

    const std::string &getName() const;

private:
    std::string _name;
};


#endif //APP_RENDERABLEMODULE_HPP
