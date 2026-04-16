/// Yogourt.cpp
// (C) 2026 maplefoxo
// Purpose : 
//

#include "Yogourt.h"
#include "Garniture.h"



Yogourt::Yogourt(YogourtRegistre & sorte) : _yogourt(sorte)
{}

void Yogourt::ajouterGarniture(Garniture && garniture) {
	_garnitures.push_back(std::move(garniture));
}

void Yogourt::undo() {
	//TODOOOOOOOO
}

double Yogourt::prixTotal() const {
	double prix = _yogourt._cout;
	prix = std::accumulate(_garnitures.cbegin(), _garnitures.cend(), prix, 
						   [&](double acc, Garniture& garni) {	
								return acc + garni.getCout();
							});

	return prix;
}

const YogourtRegistre& Yogourt::getSorteYogourt() const {
	return _yogourt;
}
