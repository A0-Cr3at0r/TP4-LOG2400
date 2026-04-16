#include "AppliCommande.h"
#include "CommandYogourt.h"
#include "Inventaire.h"
#include "Paiement.h"
#include "const.h"

void AppliCommandeChangerModePaiement::Execute() {
    if (mode_ == "prev") {
        commande_.setPaiement(std::make_unique<Prevente>());
        UIManager::print("Mode de paiement actif: Prevente (-10%).\n", Couleurs::DEFAULT);
    } else if (mode_ == "eclair") {
        commande_.setPaiement(std::make_unique<Eclair>());
        UIManager::print("Mode de paiement actif: Vente eclair (+1.50).\n", Couleurs::DEFAULT);
    } else if (mode_ == "poly") {
        commande_.setPaiement(std::make_unique<Poly>());
        UIManager::print("Mode de paiement actif: Coupon Poly (-2.00).\n", Couleurs::DEFAULT);
    }
}

void AppliCommandeVoirTotal::Execute() {
    double st = commande_.getSousTotal();
    UIManager::printf("Sous-total: %.2f CAD\n", Couleurs::CYAN, st);
    if (commande_.getPaiement()->estPayable()) {
        double total = commande_.getPaiement()->calculerTotal(st);
        UIManager::printf("Total avec %s: %.2f CAD\n", Couleurs::CYAN,
                          commande_.getPaiement()->getNom().c_str(), total);
    }
}

void AppliCommandeVoirStock::Execute() {
    Inventaire& inv = commande_.getInventaire();
    UIManager::print("Stocks:\n", Couleurs::CYAN);
    for (auto it = inv.yogourtBegin(); it != inv.yogourtEnd(); ++it)
        UIManager::printf("  %s: %d\n", Couleurs::DEFAULT, it->_nom.c_str(), (int)it->getQte());
    for (auto it = inv.garnitureBegin(); it != inv.garnitureEnd(); ++it)
        UIManager::printf("  %s: %d\n", Couleurs::DEFAULT, it->_nom.c_str(), (int)it->getQte());
}
