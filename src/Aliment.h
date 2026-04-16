/// Aliment.h
// (C) 2026 maplefoxo
// Purpose : Template base classes for stock-managed alimentary items

#pragma once

#include <pch.h>
#include "ui/UIManager.h"

enum class TypeAliment : uint8_t {
	GARNITURE,
	YOGOURT,
};

template<typename T_Derived, typename T_Aliment>
class AlimentRegistre {
public:
	AlimentRegistre(string&& nom, unsigned int qte_initiale, double cout)
		: _nom(std::move(nom)), _qte(qte_initiale), _cout(cout)
	{
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : 0 -> %i\n", Couleurs::DEFAULT, _nom.c_str(), _qte);
	}

	unsigned int getQte() const { return _qte; }

	void incQte() {
		auto oldqt = _qte++;
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
	}

	T_Aliment decQte() {
		auto oldqt = _qte--;
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
		return T_Aliment(static_cast<T_Derived&>(*this));
	}

	virtual TypeAliment getTypeAliment() = 0;

	const double _cout;
	const string _nom;

protected:
	unsigned int _qte;
};

template<typename T_Registre>
class Aliment {
public:
	double      getCout() const { return source._cout; }
	string_view getNom()  const { return string_view(source._nom); }
	TypeAliment getTypeAliment() const { return source.getTypeAliment(); }

	Aliment(const Aliment&)            = delete;
	Aliment& operator=(const Aliment&) = delete;
	Aliment(Aliment&&)                 = default;
	Aliment& operator=(Aliment&&)      = delete;

	template<typename, typename> friend class AlimentRegistre;

protected:
	explicit Aliment(T_Registre& source) : source(source) {}
	const T_Registre& source;
};
