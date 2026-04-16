#include "Paiement.h"

double Paiement::totalProjete() {
    return total_;
}

void Prevente::pay(double montant) {
    total_ = 0.9 * montant;
}
std::string toString() {
    return "Prevente (-10%)";
}

void Eclair::pay(double montant) {
    total_  = montant + 1.5;
}
std::string toString() {
    return "Vente eclair (+1.50)";
}

void Poly::pay(double montant) {
    total_ = montant - 2;
}

std::string toString() {
    return "Coupon Poly (-2.00)";
}

