#pragma once

#include <exception>
#include <cstring>

class InvalidFormatException: public std::exception{

    private:
        char *message;

    public:
        InvalidFormatException(const char *);
        const char *what() const throw();
    
};