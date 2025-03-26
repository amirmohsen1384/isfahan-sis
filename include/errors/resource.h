#ifndef RESOURCE_H
#define RESOURCE_H

#include <exception>

class FileNotFoundException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The desired file is not found.";
    }
};

class ReadFileException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The file is not readable.";
    }
};

class WriteFileException : public std::exception
{
    inline const char* what() const noexcept override {
        return "The file is not writable.";
    }
};

#endif // RESOURCE_H
