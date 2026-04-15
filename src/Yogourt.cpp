#include "Yogourt.h"

Yogourt::Yogourt(bool isGrec) : isGrec_(isGrec) {}

Yogourt::~Yogourt() {}

void Yogourt::ajouterGarniture(Garniture garniture) {
    garnitures_.push_back(std::make_unique<Garniture>(std::move(garniture)));
}

void Yogourt::undo() {
    garnitures_.pop_back();
}

double Yogourt::prixTotal() {
    double total = isGrec_ ? PRIX_GREC : PRIX_NATURE;
    for (auto& ptr : garnitures_) {
        total += ptr->getPrice();
    }
    return total;
}

