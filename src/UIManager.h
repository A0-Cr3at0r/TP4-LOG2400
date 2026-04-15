#pragma once
#include <string>
#include <string_view>
#include <iostream>
#include <format>
#include <sstream>
#include <vector>

enum class Couleurs : unsigned char {
    DEFAULT,
    ROUGE,
    VERT,
    JAUNE,
    BLEU,
    MAUVE,
    CYAN,
    BLANC,

    NUM_COULEURS
};

struct CommandInput {
    std::string command;
    std::vector<std::string> args;
};

struct UIMessage {
    std::string texte;
    Couleurs couleur = Couleurs::DEFAULT;
};

class UIManager {
public:
    static void print(const std::string_view& texte, Couleurs couleur = Couleurs::DEFAULT);
    static void print(const UIMessage& msg);

    template<typename... Args>
    static void printf(const std::string_view& texte, Couleurs couleur, Args&&... args);

    template<typename... Args>
    static void printf(const UIMessage& msg, Args&&... args);

    static CommandInput scanf();
    static void cls();

private:
    UIManager() = delete;
    static const char* getCharCSeq(Couleurs clr);
};

template<typename... Args>
void UIManager::printf(const std::string_view& texte, Couleurs couleur, Args&&... args) {
    std::string formatted = std::format(texte, std::forward<Args>(args)...);
    print(formatted, couleur);
}

template<typename... Args>
void UIManager::printf(const UIMessage& msg, Args&&... args) {
    printf(msg.texte, msg.couleur, std::forward<Args>(args)...);
}