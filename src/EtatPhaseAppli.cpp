#include "EtatPhaseAppli.h"
#include "CommandYogourt.h"
#include "Inventaire.h"
#include "Paiement.h"
#include "helpers.h"
#include "ui/UIManager.h"
#include <cstdio>



static void changerModeImpl(CommandYogourt* c, const std::string& mode) {
    if (mode == "prev") {
        c->setPaiement(std::make_unique<Prevente>());
        UIManager::print("Mode de paiement actif: Prevente (-10%).\n", Couleurs::DEFAULT);
    } else if (mode == "eclair") {
        c->setPaiement(std::make_unique<Eclair>());
        UIManager::print("Mode de paiement actif: Vente eclair (+1.50).\n", Couleurs::DEFAULT);
    } else if (mode == "poly") {
        c->setPaiement(std::make_unique<Poly>());
        UIManager::print("Mode de paiement actif: Coupon Poly (-2.00).\n", Couleurs::DEFAULT);
    }
}

static void voirTotalImpl(CommandYogourt* c) {
    double st = c->getSousTotal();
    UIManager::printf("Sous-total: %.2f CAD\n", Couleurs::CYAN, st);
    if (c->getPaiement()->estPayable()) {
        double total = c->getPaiement()->calculerTotal(st);
        UIManager::printf("Total avec %s: %.2f CAD\n", Couleurs::CYAN,
                          c->getPaiement()->getNom().c_str(), total);
    }
}

static void voirStockImpl(CommandYogourt* c) {
    Inventaire& inv = c->getInventaire();
    UIManager::print("Stocks:\n", Couleurs::CYAN);
    for (auto it = inv.yogourtBegin(); it != inv.yogourtEnd(); ++it)
        UIManager::printf("  %s: %d\n", Couleurs::DEFAULT, it->_nom.c_str(), (int)it->getQte());
    for (auto it = inv.garnitureBegin(); it != inv.garnitureEnd(); ++it)
        UIManager::printf("  %s: %d\n", Couleurs::DEFAULT, it->_nom.c_str(), (int)it->getQte());
}



void EtatPhaseAppli::TerminerCommande() {
    UIManager::print("La commande doit etre preparee avant d'etre terminee.\n", Couleurs::ROUGE);
}

void EtatPhaseAppli::Payer() {
    UIManager::printf("Paiement refuse: etat Terminee requis (etat actuel: %s).\n",
                      Couleurs::ROUGE, nom_);
}

void EtatPhaseAppli::VoirTotal()  { voirTotalImpl(commande_); }
void EtatPhaseAppli::VoirStock()  { voirStockImpl(commande_); }



void EtatPhaseCommandeInitiale::AjouterYogourt(const std::string& type) {
    auto yt = stringToYogourt(type);
    if (!yt) {
        UIManager::printf("Type de yogourt invalide: '%s'.\n", Couleurs::ROUGE, type.c_str());
        return;
    }
    if ((int)commande_->getYogourts().size() >= MAXYOGOURT) {
        UIManager::printf("Nombre maximum de yogourts (%d) atteint.\n", Couleurs::ROUGE, MAXYOGOURT);
        return;
    }
    Inventaire& inv = commande_->getInventaire();
    if (!inv.yogourtDisponible(yt.value())) {
        UIManager::printf("Stock insuffisant pour %s.\n", Couleurs::ROUGE, type.c_str());
        return;
    }
    inv.retirerYogourt(yt.value());
    commande_->notifyAll();
    commande_->ajouterNouveauYogourt(yt.value());
    commande_->clearRedo(); 
    UIManager::printf("Yogourt %s selectionne.\n", Couleurs::DEFAULT, type.c_str());
}

void EtatPhaseCommandeInitiale::SelectionnerYogourt(unsigned index) {
    if (index < 1 || index > (unsigned)commande_->getYogourts().size()) {
        UIManager::print("Index invalide.\n", Couleurs::ROUGE);
        return;
    }
    commande_->setYogourtActif((int)index - 1);
}

void EtatPhaseCommandeInitiale::AjouterGarniture() {
    if (!commande_->getYogourtActif()) {
        UIManager::print("Aucun yogourt actif. Ajoutez d'abord un yogourt.\n", Couleurs::ROUGE);
        return;
    }

    static const typeGarniture ordre[] = {
        typeGarniture::FRUIT, typeGarniture::GRANOLA,
        typeGarniture::MIEL,  typeGarniture::CHOCOLAT
    };

    while (true) {
        Inventaire& inv  = commande_->getInventaire();
        int actifIdx     = commande_->getIndexActif() + 1;

        UIManager::print("\nMenu Garnitures\n", Couleurs::CYAN);
        UIManager::printf("  Yogourt actif: #%d\n", Couleurs::DEFAULT, actifIdx);
        int i = 1;
        for (auto gt : ordre) {
            UIManager::printf("  %d -> %-8s (%d en stock)\n", Couleurs::DEFAULT,
                              i, garnitureToString(gt), inv.getStockGarniture(gt));
            i++;
        }
        UIManager::print("  q -> retour menu principal\n", Couleurs::DEFAULT);
        UIManager::print("Choix garniture: ", Couleurs::MAUVE);

        auto input = UIManager::scanf();

        if (input.command == "q") {
            UIManager::print("Retour au menu principal.\n", Couleurs::CYAN);
            return;
        }

        try {
            int choix = std::stoi(input.command);
            if (choix < 1 || choix > 4) continue;
            typeGarniture gt = ordre[choix - 1];
            if (!inv.garnitureDisponible(gt)) {
                UIManager::printf("Stock insuffisant pour la garniture '%s'.\n",
                                  Couleurs::ROUGE, garnitureToString(gt));
                continue;
            }
            Garniture g = inv.retirerGarniture(gt);
            commande_->getYogourtActif()->ajouterGarniture(gt, std::move(g));
            commande_->clearRedo();
            commande_->notifyAll(); 
            UIManager::printf("Garniture '%s' ajoutee.\n", Couleurs::DEFAULT, garnitureToString(gt));
        } catch (...) {}
    }
}

void EtatPhaseCommandeInitiale::Annuler() {
    Yogourt* actif = commande_->getYogourtActif();
    if (!actif || !actif->hasGarnitures()) {
        UIManager::print("Aucune garniture a annuler.\n", Couleurs::DEFAULT);
        return;
    }
    typeGarniture type = actif->undo();
    commande_->getInventaire().ajouterGarniture(type);
    commande_->setRedoGarniture(type);
    commande_->notifyAll();
    UIManager::print("Derniere garniture annulee.\n", Couleurs::DEFAULT);
}

void EtatPhaseCommandeInitiale::Reappliquer() {
    if (!commande_->hasRedo()) {
        UIManager::print("Aucune garniture a refaire.\n", Couleurs::DEFAULT);
        return;
    }
    typeGarniture type = commande_->getRedoGarniture();
    Inventaire& inv    = commande_->getInventaire();
    if (!inv.garnitureDisponible(type)) {
        UIManager::printf("'%s' hors stock, impossible de refaire.\n",
                          Couleurs::ROUGE, garnitureToString(type));
        commande_->clearRedo();
        return;
    }
    Garniture g = inv.retirerGarniture(type);
    commande_->getYogourtActif()->ajouterGarniture(type, std::move(g));
    commande_->clearRedo();
    commande_->notifyAll(); 
    UIManager::print("Garniture retablie.\n", Couleurs::DEFAULT);
}

void EtatPhaseCommandeInitiale::PreparerCommande() {
    if (commande_->getYogourts().empty()) {
        UIManager::print("Impossible de preparer sans yogourt.\n", Couleurs::ROUGE);
        return;
    }
    UIManager::print("Preparation en cours ...\n", Couleurs::DEFAULT);
    commande_->setState(commande_->getEtatPreparation());
}

void EtatPhaseCommandeInitiale::ChangerModePaiement(const std::string& mode) {
    changerModeImpl(commande_, mode);
}

void EtatPhaseCommandeInitiale::VoirTotal()  { voirTotalImpl(commande_); }
void EtatPhaseCommandeInitiale::VoirStock()  { voirStockImpl(commande_); }




void EtatPhaseCommandePreparation::AjouterYogourt(const std::string&) {
    UIManager::print("Commande en preparation: impossible de modifier les yogourts.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::SelectionnerYogourt(unsigned) {
    UIManager::print("Commande en preparation: impossible de modifier les yogourts.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::AjouterGarniture() {
    UIManager::print("Commande en preparation: impossible d'ajouter des garnitures.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::Annuler() {
    UIManager::print("Commande en preparation: annulation verrouillee.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::Reappliquer() {
    UIManager::print("Commande en preparation: annulation verrouillee.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::PreparerCommande() {
    UIManager::print("Commande deja en preparation.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandePreparation::ChangerModePaiement(const std::string& mode) {
    changerModeImpl(commande_, mode);
}

void EtatPhaseCommandePreparation::TerminerCommande() {
    UIManager::print("Commande terminee.\n", Couleurs::DEFAULT);
    commande_->setState(commande_->getEtatTerminee());
}

void EtatPhaseCommandePreparation::VoirTotal() { voirTotalImpl(commande_); }
void EtatPhaseCommandePreparation::VoirStock() { voirStockImpl(commande_); }




void EtatPhaseCommandeTerminee::AjouterYogourt(const std::string&) {
    UIManager::print("Commande terminee: impossible de modifier le yogourt.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::SelectionnerYogourt(unsigned) {
    UIManager::print("Commande terminee: impossible de modifier le yogourt.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::AjouterGarniture() {
    UIManager::print("Commande terminee: impossible d'ajouter des garnitures.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::Annuler() {
    UIManager::print("Commande terminee: annulation impossible.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::Reappliquer() {
    UIManager::print("Commande terminee: annulation impossible.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::PreparerCommande() {
    UIManager::print("Commande deja terminee.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::TerminerCommande() {
    UIManager::print("Commande deja terminee.\n", Couleurs::ROUGE);
}

void EtatPhaseCommandeTerminee::ChangerModePaiement(const std::string& mode) {
    changerModeImpl(commande_, mode);
}

void EtatPhaseCommandeTerminee::Payer() {
    if (!commande_->getPaiement()->estPayable()) {
        UIManager::print("Paiement refuse: choisissez d'abord un mode (mode prev|eclair|poly).\n",
                         Couleurs::ROUGE);
        return;
    }
    double st    = commande_->getSousTotal();
    double total = commande_->getPaiement()->calculerTotal(st);
    UIManager::printf("Paiement accepte (%s) | Montant: %.2f CAD\n", Couleurs::VERT,
                      commande_->getPaiement()->getNom().c_str(), total);
    UIManager::print("Merci pour votre achat. A bientot!\n", Couleurs::VERT);
    commande_->setTermine(true);
}

void EtatPhaseCommandeTerminee::VoirTotal() { voirTotalImpl(commande_); }
void EtatPhaseCommandeTerminee::VoirStock() { voirStockImpl(commande_); }
