/// Inventaire.cpp
// (C) 2026 maplefoxo
// Purpose : 
//
#include <pch.h>

#include "Inventaire.h"
#include "const.h"

Inventaire* Inventaire::inv = nullptr;

Inventaire& Inventaire::get() {
	if (inv == nullptr) 
		inv = new Inventaire();

	return *inv;
}

void Inventaire::destroy() {
	if (inv != nullptr) {
		delete inv;
		inv = nullptr;
	}
}

unsigned int Inventaire::getNumGarnitures() const {
	return _garnitures.size();
}

GarnitureRegistre & Inventaire::getGarniture(size_t index) {
	return _garnitures.at(index);
}

vector<GarnitureRegistre>::iterator Inventaire::garnitureBegin() {
	return _garnitures.begin();
}
vector<GarnitureRegistre>::iterator Inventaire::garnitureEnd() {
	return _garnitures.end();
}

void Inventaire::enregistrerGarniture(GarnitureRegistre && garniture) {
	_garnitures.push_back(std::move(garniture));
}

unsigned int Inventaire::getNumYogourts() const {
	return _yogourts.size();
}

YogourtRegistre & Inventaire::getYogourt(size_t index) {
	return _yogourts.at(index);
}

vector<YogourtRegistre>::iterator Inventaire::yogourtBegin() {
	return _yogourts.begin();
}
vector<YogourtRegistre>::iterator Inventaire::yogourtEnd() {
	return _yogourts.end();
}

void Inventaire::enregistrerYogourt(YogourtRegistre && yogourt) {
	_yogourts.push_back(std::move(yogourt));
}

Inventaire::Inventaire() {
	enregistrerGarniture(GarnitureRegistre("fruits",	QTE_FRUIT,		PRIX_FRUIT));
	enregistrerGarniture(GarnitureRegistre("granola",	QTE_GRANOLA,	PRIX_GRANOLA));
	enregistrerGarniture(GarnitureRegistre("chocolat",	QTE_CHOCOLAT,	PRIX_CHOCOLAT));
	enregistrerGarniture(GarnitureRegistre("miel",		QTE_MIEL,		PRIX_MIEL));

	enregistrerYogourt(YogourtRegistre("nature",		PRIX_NATURE));
	enregistrerYogourt(YogourtRegistre("grec",			PRIX_GREC));
}
