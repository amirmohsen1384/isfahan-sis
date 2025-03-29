#ifndef EDUCATION_H
#define EDUCATION_H

#include <exception>
#include "general.h"

class OverlapException : public std::exception
{
    inline const char* what() const noexcept override {
        return "Final exam dates overlap.";
    }
};

class CreditsOutOfBoundException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The count of enrolled credits is out of bounds.";
    }
};

class UserOverflowException : public std::exception
{
    inline const char* what() const noexcept override {
        return "Only one user can enter the application at a time.";
    }
};

class AuthorizationException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The username or password is incorrect.";
    }
};

class OutOfCapacityException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The lesson is out of capacity.";
    }
};


#endif // EDUCATION_H
