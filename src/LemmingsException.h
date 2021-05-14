//
// Created by hawk on 14.05.21.
//

#ifndef LEMMINGS_LEMMINGSEXCEPTION_H
#define LEMMINGS_LEMMINGSEXCEPTION_H

#include <exception>
#include <string>

class LemmingsException : public std::exception {
public:
    explicit LemmingsException(std::string  errorMsg, int errorNo = 0);

    [[nodiscard]] const char * what() const noexcept override {
        return _error_msg.c_str();
    }
    [[nodiscard]] int number()const {return _error_number;}
private:
    std::string _error_msg;
    int _error_number;
};


#endif //LEMMINGS_LEMMINGSEXCEPTION_H
