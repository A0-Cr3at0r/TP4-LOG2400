#include "GarnitureInventaire.h"

GarnitureInventaire::GarnitureInventaire(typeGarniture typeGarniture, double prix, int qte) :
    Garniture(typeGarniture, prix), quantite_(qte)
{}

GarnitureInventaire::~GarnitureInventaire()
{}

bool GarnitureInventaire::isEmpty() {
    return quantite_ == 0;
}

bool GarnitureInventaire::isGarniture(typeGarniture type) {
    return typeGarniture_ == type;
}

Garniture GarnitureInventaire::retirerGarniture() {
    quantite_--;
    return Garniture(typeGarniture_, prix_);
}

void GarnitureInventaire::ajouterGarniture() {
    quantite_++;
}
