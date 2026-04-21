/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once

#include <string>
#include <memory>
#include <dlfcn.h>

template<typename T>
class DLLoader {
public:
    DLLoader(const std::string &path) : _lib(path), _handle(nullptr, close_handle) {};

    void open()
    {
        if (_handle)
            return;
        if (!_handle)
            _handle = std::unique_ptr<void, decltype(&close_handle)>(dlopen(_lib.c_str(), RTLD_LAZY));
        if (!_handle)
            throw DLLoaderException();
    }

    void *sym(const std::string &symbol) const
    {
        if (!_handle)
            return nullptr;

        void *result = dlsym(_handle.get(), symbol.c_str());
        if (!result)
            throw DLLoaderException();
        return result;
    }

    std::unique_ptr<T> getInstance(std::string &create)
    {
        return std::unique_ptr<T>(this->sym(create));
    }

    class DLLoaderException : public std::exception {
        public:
            const char *what() const noexcept override { return dlerror(); }
    };
private:
    static void close_handle(void *handle) { dlclose(handle); }
    std::string _lib;
    std::unique_ptr<void, decltype(&close_handle)> _handle;
};
