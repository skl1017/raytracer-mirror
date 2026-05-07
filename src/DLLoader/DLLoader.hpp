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
#include <map>
#include <iostream>

class DLLoader {
public:
    DLLoader() {}

    void open(const std::string &path)
    {
        if (_libs.find(path) != _libs.end())
            return;
        _libs.emplace(path, std::unique_ptr<void, decltype(&close_handle)>(dlopen(path.c_str(), RTLD_LAZY), &close_handle));
        if (!_libs.at(path))
            throw DLLoaderException();
    }

    void *sym(const std::string &path, const std::string &symbol) const
    {
        if (_libs.find(path) == _libs.end()){
            throw DLLoaderException();
        }

        void *result = dlsym(_libs.at(path).get(), symbol.c_str());
        if (!result)
            throw DLLoaderException();
        return result;
    }

    class DLLoaderException : public std::exception {
        public:
            const char *what() const noexcept override { return dlerror(); }
    };
private:
    static void close_handle(void *handle) { dlclose(handle); }
    std::map<std::string, std::unique_ptr<void, decltype(&close_handle)>> _libs;
};
