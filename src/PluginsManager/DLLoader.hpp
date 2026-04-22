/*
** EPITECH PROJECT, 2026
** raytracer-mirror
** File description:
** DLLoader
*/

#pragma once

#include <functional>
#include <string>
#include <memory>
#include <dlfcn.h>

template<typename T>
class DLLoader {
public:
    DLLoader(const std::string &path) : _lib(path), _handle(std::unique_ptr<void, decltype(&close_handle)>(nullptr, &close_handle)) {};

    void open()
    {
        if (_handle)
            return;
        if (!_handle)
            _handle = std::unique_ptr<void, decltype(&close_handle)>(dlopen(_lib.c_str(), RTLD_LAZY), &close_handle);
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

    std::unique_ptr<T> getInstance(const std::string& create)
    {
        std::function<T*()> func = reinterpret_cast<T*(*)()>(this->sym(create));

        if (!func)
            throw DLLoaderException();
        return std::unique_ptr<T>(func());
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
