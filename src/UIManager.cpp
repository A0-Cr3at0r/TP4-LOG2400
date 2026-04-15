#include "UIManager.h"

void UIManager::print(const std::string_view& texte, Couleurs couleur) {
    std::cout << getCharCSeq(couleur) << texte << getCharCSeq(Couleurs::DEFAULT) << std::endl;
}

void UIManager::print(const UIMessage& msg) {
    print(msg.texte, msg.couleur);
}


CommandInput UIManager::scanf() {
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    CommandInput result;

    iss >> result.command;

    std::string arg;
    while (iss >> arg) {
        result.args.push_back(arg);
    }

    return result;
}

void UIManager::cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif 
}