/// Garniture.coo
// (C) 2026 maplefoxo
// Purpose : 
//

#include "Garniture.h"
#include "ui/UIManager.h"

GarnitureRegistre::GarnitureRegistre(string&& nom ,unsigned int qte_initiale,double cout) :
	_nom(nom), _qte(qte_initiale), _cout(cout)
{
	UIManager::print("[Stock] ", Couleurs::CYAN);
	UIManager::printf("%s : 0 -> %i\n", Couleurs::DEFAULT, _nom.c_str(), _qte);
}

unsigned int GarnitureRegistre::getQte() {
	return _qte;
}
void GarnitureRegistre::incQte() { 
	auto oldqt = _qte++;
	UIManager::print("[Stock] ", Couleurs::CYAN);
	UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
}

Garniture GarnitureRegistre::decQte() {
	auto oldqt = _qte--;
	UIManager::print("[Stock] ", Couleurs::CYAN);
	UIManager::printf("%s : %i -> %i\n", Couleurs::DEFAULT, _nom.c_str(), oldqt, _qte);
	return Garniture(*this);
}

double Garniture::getCout() const
{
	return source._cout;
}

string_view& Garniture::getNom() const
{
	auto s = string_view(source._nom);
	return s;
}

Garniture::Garniture(GarnitureRegistre& source) : source(source)
{}
