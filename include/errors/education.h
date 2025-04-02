#ifndef EDUCATION_H
#define EDUCATION_H

#include <exception>
#include "general.h"

class OverlapException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "Final exam dates overlap.";
    }
};

class CreditsOutOfBoundException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "The count of enrolled credits is out of bounds.";
    }
};

class UserOverflowException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "Only one user can enter the application at a time.";
    }
};

class AuthorizationException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "The username or password is incorrect.";
    }
};

class OutOfCapacityException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "The lesson is out of capacity.";
    }
};

class InvalidIdentifierException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "The identifier is invalid.";
    }
};

class EmptyIdentifierException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered any identifiers.";
    }
};

class EmptyFirstNameException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered the first name!";
    }
};

class EmptyLastNameException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered the last name!";
    }
};

class EmptyUserNameException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered the user name.";
    }
};

class EmptyPasswordException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered your password.";
    }
};

class InvalidPasswordException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have entered an invalid password.";
    }
};

class EmptyLessonNameException : public std::exception
{
public:
    inline const char* what() const noexcept override {
        return "You have not entered the name of the lesson.";
    }
};

class EmptyBranchNumberException : public std::exception
{
    inline const char* what() const noexcept override {
        return "You have not entered the branch number of the lesson.";
    }
};

#endif // EDUCATION_H
