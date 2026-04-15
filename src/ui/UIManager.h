/// UIManager.h
// (C) 2026 maplefoxo
// Purpose : 
// 
#pragma once

#include "pch.h"

const static enum class Couleurs : unsigned char {
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

struct UIMessage {
	std::string texte;
	Couleurs couleur = Couleurs::DEFAULT;
};

struct CommandInput {
    std::string command;
    std::vector<std::string> args;
};


class UIManager {
public:
	static void print(const std::string_view& texte, Couleurs couleur = Couleurs::DEFAULT);
	static void cls();
	static void print(const UIMessage& msg);
	static void printf(const std::string_view& texte, Couleurs couleur = Couleurs::DEFAULT);
	static void printf(const UIMessage& msg);
	template<typename... Args> 
	static void printf(const std::string_view& texte, Couleurs couleur = Couleurs::DEFAULT, Args... args);
	template<typename... Args>
	static void printf(const UIMessage& msg, Args... args);
	
	static CommandInput scanf()
private:
	UIManager() = delete;
	static constexpr const char* getCharCSeq(const Couleurs clr);
};


template<typename ...Args>
inline void UIManager::printf(const std::string_view & texte,Couleurs couleur,Args ...args) {
	std::fputs(UIManager::getCharCSeq(couleur), stdout);
	std::printf(texte.data(), args...);
}

template<typename ...Args>
inline void UIManager::printf(const UIMessage & msg,Args ...args) {
	UIManager::printf(msg.texte, msg.couleur, args...);
}