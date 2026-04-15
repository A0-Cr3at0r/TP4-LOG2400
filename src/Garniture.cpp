/// Garniture.coo
// (C) 2026 maplefoxo
// Purpose : 
//


#include "Garniture.h"

GarnitureRegistre::GarnitureRegistre(string& nom ,unsigned int qte_initiale,double cout) :
	_nom(nom), _qte(qte_initiale), _cout(cout)
{}

unsigned int GarnitureRegistre::getQte() {
	return _qte;
}
void GarnitureRegistre::incQte() { ++_qte; }

Garniture GarnitureRegistre::decQte() {
	 --_qte;
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
