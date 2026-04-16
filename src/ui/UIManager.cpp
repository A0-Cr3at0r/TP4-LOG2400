/// UIManager.cpp
// (C) 2026 maplefoxo
// Purpose : 
// 
#include <pch.h>

#include <cstdio>
#include <iostream>
#include <iosfwd>

#include "UIManager.h"


void UIManager::print(const std::string_view& texte,Couleurs couleur) {
	std::fputs(UIManager::getCharCSeq(couleur), stdout);
	std::fputs(texte.data(), stdout);
	std::fputs(UIManager::getCharCSeq(Couleurs::DEFAULT), stdout);
}

void UIManager::cls() {
	printf("\x1b[1;1H\x1b[2J");
}

void UIManager::print(const UIMessage& msg) {
	UIManager::print(msg.texte, msg.couleur);
}

void UIManager::printf(const std::string_view & texte,Couleurs couleur) {
	UIManager::print(texte, couleur);
}

void UIManager::printf(const UIMessage & msg) {
	UIManager::print(msg);
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

constexpr const char* UIManager::getCharCSeq(const Couleurs clr) {
	const char* clr2seq[] = {
		"\x1b[0m",
		"\x1b[0m\x1b[31m",
		"\x1b[0m\x1b[32m",
		"\x1b[0m\x1b[33m",
		"\x1b[0m\x1b[34m",
		"\x1b[0m\x1b[35m",
		"\x1b[0m\x1b[36m",
		"\x1b[0m\x1b[37m",
		"\x1b[0m",
	};
	return clr2seq[static_cast<std::underlying_type<Couleurs>::type>(clr)];
}
