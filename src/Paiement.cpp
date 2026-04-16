#include "Paiement.h"

bool Aucun::estPayable() const {
    return false;
}

std::string Aucun::getNom() const {
    return "Aucune";
}

double Aucun::calculerTotal(double montant) const {
    return montant;
}




bool Prevente::estPayable() const {
    return true;
}

std::string Prevente::getNom() const {
    return "Prevente (-10%)";
}

double Prevente::calculerTotal(double montant) const {
    return 0.9 * montant;
}





bool Eclair::estPayable() const {
    return true;
}

std::string Eclair::getNom() const {
    return "Vente eclair (+1.50)";
}

double Eclair::calculerTotal(double montant) const {
    return montant + 1.5;
}



bool Poly::estPayable() const {
    return true;
}

std::string Poly::getNom() const {
    return "Coupon Poly (-2.00)";
}

double Poly::calculerTotal(double montant) const {
    return montant - 2.0;
}


