//
// Created by arzad on 16/01/2022.
//

#include "renderer/RendererException.hpp"

#include <utility>

RendererException::RendererException(std::string reason): _reason(std::move(reason)) {}

const char *RendererException::what() const noexcept {
    return _reason.c_str();
}
