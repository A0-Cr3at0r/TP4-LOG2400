#pragma once
#include "const.h"
#include <optional>
#include <string>

inline const char* yogourtToString(typeYoGourt t) {
    switch (t) {
        case typeYoGourt::NATURE: return "nature";
        case typeYoGourt::GREC:   return "grec";
    }
    return "";
}

inline const char* garnitureToString(typeGarniture t) {
    switch (t) {
        case typeGarniture::FRUIT:    return "fruits";
        case typeGarniture::GRANOLA:  return "granola";
        case typeGarniture::MIEL:     return "miel";
        case typeGarniture::CHOCOLAT: return "chocolat";
    }
    return "";
}

inline std::optional<typeYoGourt> stringToYogourt(const std::string& s) {
    if (s == "nature") return typeYoGourt::NATURE;
    if (s == "grec")   return typeYoGourt::GREC;
    return std::nullopt;
}

inline std::optional<typeGarniture> stringToGarniture(const std::string& s) {
    if (s == "fruits")   return typeGarniture::FRUIT;
    if (s == "granola")  return typeGarniture::GRANOLA;
    if (s == "miel")     return typeGarniture::MIEL;
    if (s == "chocolat") return typeGarniture::CHOCOLAT;
    return std::nullopt;
}
