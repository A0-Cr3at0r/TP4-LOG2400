#include "Inventaire.h"

Inventaire::Inventaire()
{
    for (const auto& [cle, valeur] : PRIX_GARNITURES) {
        auto [prix, qte] = valeur;
        auto ptr = std::make_unique<GarnitureInventaire> (cle, prix, qte);
        inventaires_.push_back(std::move(ptr));  
    }
}

Inventaire::~Inventaire()
{}

Garniture Inventaire::retirerGarniture(typeGarniture type) {
    for (auto& ptr : inventaires_) {
        if (ptr->isGarniture(type)) {
            return ptr->retirerGarniture();
        }
    };
}

void Inventaire::ajouterGarniture(typeGarniture type) {
    for (auto& ptr : inventaires_) {
        if (ptr->isGarniture(type)) {
            ptr->ajouterGarniture();
            return;
        }
    };
}

