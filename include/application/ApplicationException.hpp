//
// Created by arzad on 16/01/2022.
//

#ifndef APP_APPLICATIONEXCEPTION_HPP
#define APP_APPLICATIONEXCEPTION_HPP


#include <exception>
#include <string>

class ApplicationException: std::exception {
public:
    explicit ApplicationException(std::string reason);
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
private:
    std::string _reason;
};


#endif //APP_APPLICATIONEXCEPTION_HPP
