#include "Yogourt.h"

Yogourt::Yogourt(YogourtRegistre& sorte) : Aliment(sorte) {}

void Yogourt::ajouterGarniture(typeGarniture type, Garniture&& garniture) {
    _types.push_back(type);
    _garnitures.push_back(std::move(garniture));
}

typeGarniture Yogourt::undo() {
    typeGarniture t = _types.back();
    _types.pop_back();
    _garnitures.pop_back();
    return t;
}

bool Yogourt::hasGarnitures() const { return !_garnitures.empty(); }

double Yogourt::prixTotal() const {
    double total = getCout();
    for (const auto& g : _garnitures)
        total += g.getCout();
    return total;
}

const YogourtRegistre& Yogourt::getSorteYogourt() const { return source; }

const std::vector<typeGarniture>& Yogourt::getTypes() const { return _types; }
