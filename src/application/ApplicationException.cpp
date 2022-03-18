//
// Created by arzad on 16/01/2022.
//

#include "application/ApplicationException.hpp"

#include <utility>

ApplicationException::ApplicationException(std::string reason) : _reason(std::move(reason)) {}

const char *ApplicationException::what() const noexcept {
    return _reason.c_str();
}
