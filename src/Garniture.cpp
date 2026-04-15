#include "Garniture.h"

Garniture::Garniture(typeGarniture type, double prix) : typeGarniture_(type), prix_(prix) {}

Garniture::~Garniture() {}

double Garniture::getPrice() {
    return prix_;
}



