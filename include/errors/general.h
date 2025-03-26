#ifndef GENERAL_H
#define GENERAL_H

#include <exception>

class NullEntityException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The entity is null.";
    }
};

#endif // GENERAL_H

