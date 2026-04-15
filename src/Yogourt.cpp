#include "Yogourt.h"

Yogourt::Yogourt(typeYoGourt type) : type_(type) {}

Yogourt::~Yogourt() {}

void Yogourt::ajouterGarniture(Garniture garniture) {
    garnitures_.push_back(std::make_unique<Garniture>(std::move(garniture)));
}

void Yogourt::undo() {
    garnitures_.pop_back();
}

double Yogourt::prixTotal() {
    double total = type_ == typeYoGourt::GREC ? PRIX_GREC : PRIX_NATURE;
    for (auto& ptr : garnitures_) {
        total += ptr->getPrice();
    }
    return total;
}

