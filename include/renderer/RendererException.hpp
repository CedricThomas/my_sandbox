//
// Created by arzad on 16/01/2022.
//

#ifndef APP_RENDEREREXCEPTION_HPP
#define APP_RENDEREREXCEPTION_HPP


#include <exception>
#include <string>

class RendererException: std::exception {
public:
    explicit RendererException(std::string reason);
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
private:
    std::string _reason;
};


#endif //APP_RENDEREREXCEPTION_HPP
