/// Aliment.h
// (C) 2026 maplefoxo
// Purpose : 
//

#pragma once

#include <pch.h>

#include "ui/UIManager.h"

enum class TypeAliment : uint8_t {
	GARNITURE,
	YOGOURT,
};

template<class T_Aliment>
class AlimentRegistre {
public:
	AlimentRegistre(string&& nom, const unsigned int qte_initiale, const double cout) :
		_nom(nom), _qte(qte_initiale), _cout(cout)
	{
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : 0 -> %i\n", Couleurs::DEFAULT, _nom.c_str(), _qte);
	}
	
	unsigned int getQte() {return _qte;}
	void incQte() { 
		auto oldqt = _qte++;
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
	}
	T_Aliment decQte()	{
		auto oldqt = _qte--;
		UIManager::print("[Stock] ", Couleurs::CYAN);
		UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
		return T_Aliment(*this);
	}

	virtual TypeAliment getTypeAliment() = 0;
		
	const 	double		_cout;	
	const 	string		_nom;
	
protected:
	unsigned int 	_qte;
};

template<class T_Registre>
class Aliment {
public:
	friend class T_Registre;

	double getCout() const {source._cout};
	string_view getNom() const {
		return string_view(source._nom);
	}
	TypeAliment getTypeAliment() const {
		return source.getTypeAliment();
	}

	Aliment(const Aliment&) = delete;
	Aliment& operator=(const Aliment&) = delete;
protected:
	Aliment(T_Registre& source) : source(source) {}
	const T_Registre& source;
};

// Garnitures
class GarnitureRegistre : public AlimentRegistre<Garniture> {
	TypeAliment getTypeAliment() override {
		return TypeAliment::GARNITURE;
	}
};
class Garniture : public Aliment<GarnitureRegistre>;


// yogourts
class YogourteRegistre : public AlimentRegistre<Yogourt> {
	TypeAliment getTypeAliment() override {
		return TypeAliment::YOGOURT;
	}
};
class Yogourt : public Aliment<YogourteRegistre> {
	
	void ajouterGarniture(Garniture&& garniture) {
		_garnitures.push_back(std::move(garniture));
	};
	Garniture&& undo() {
		// TODOOOOOOOOOOOOOOOOOO
	};
	double prixTotal() const {
		double prix = _yogourt._cout;
		prix = std::accumulate(_garnitures.cbegin(), _garnitures.cend(), prix, 
						   [&](double acc, Garniture& garni) {	
								return acc + garni.getCout();
							});

		return prix;
	};
private:
    std::vector<Garniture> _garnitures;
};






