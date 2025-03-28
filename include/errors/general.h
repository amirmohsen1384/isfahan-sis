#ifndef GENERAL_H
#define GENERAL_H

#include <exception>

class NullEntityException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The entity is null.";
    }
};

class DuplicateEntityException : public std::exception {
    inline const char* what() const noexcept override {
        return "There's already another entity with this identifier.";
    }
};

#endif // GENERAL_H

