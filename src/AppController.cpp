#include "AppController.h"
#include "EtatPhaseAppli.h"
#include "Inventaire.h"
#include "helpers.h"
#include <cstdio>
#include <optional>

AppController::AppController()
    : commande_(Inventaire::get(), abonnement_)
{
    UIManager::print("Bienvenue sur TonYogourt\n", Couleurs::VERT);
    afficherAide();
}

AppController::~AppController() {
    Inventaire::get().destroy();
}

std::function<void(std::string)> AppController::notifCallback() {
    return [](std::string msg) {
        UIManager::print((msg + "\n").c_str(), Couleurs::ROUGE);
    };
}


void AppController::run() {
    while (!commande_.isTermine()) {
        afficherStatut();
        UIManager::print("Commande: ", Couleurs::MAUVE);
        auto input = UIManager::scanf();

        if (input.command.empty()) continue;

        if (input.command == "q") break;
        if (input.command == "clear" || input.command == "cls") { UIManager::cls(); continue; }
        if (input.command == "h") { afficherAide(); continue; }

        traiterCommande(input);
        abonnement_.notifier();
        verifierAbonnementsYogourt();
    }
}


void AppController::afficherStatut() const {
    // Ligne Phase
    UIManager::print("Phase: ", Couleurs::DEFAULT);
    UIManager::print(commande_.getEtatCourant()->getNom(), Couleurs::JAUNE);
    UIManager::print("\n", Couleurs::DEFAULT);

    // Lignes yogourts
    const auto& yogourts = commande_.getYogourts();
    if (yogourts.empty()) {
        UIManager::print("Yogourts: aucun\n", Couleurs::DEFAULT);
    } else {
        int actifIdx = commande_.getIndexActif();
        for (int i = 0; i < (int)yogourts.size(); i++) {
            const Yogourt& y = yogourts[i];
            bool estActif    = (i == actifIdx);

            // "Yogourt #N (actif): " ou "Yogourt #N: "
            if (estActif)
                UIManager::printf("Yogourt #%d (actif): ", Couleurs::DEFAULT, i + 1);
            else
                UIManager::printf("Yogourt #%d: ", Couleurs::DEFAULT, i + 1);

            // "Yogourt grec + chocolat + fruits"
            UIManager::printf("Yogourt %s", Couleurs::DEFAULT, y.getSorteYogourt()._nom.c_str());
            for (typeGarniture t : y.getTypes())
                UIManager::printf(" + %s", Couleurs::DEFAULT, garnitureToString(t));

            UIManager::printf(" | Prix: %.2f CAD\n", Couleurs::DEFAULT, y.prixTotal());
        }
    }

    UIManager::printf("Sous-total commande: %.2f CAD\n", Couleurs::DEFAULT, commande_.getSousTotal());

    Paiement* p = commande_.getPaiement();
    if (!p->estPayable()) {
        UIManager::print("Paiement: Aucune | ", Couleurs::DEFAULT);
        UIManager::print("choisir un mode de paiement", Couleurs::JAUNE);
        UIManager::print(" | ", Couleurs::DEFAULT);
        UIManager::print("non payable\n", Couleurs::ROUGE);
    } else {
        double total = p->calculerTotal(commande_.getSousTotal());
        UIManager::printf("Paiement: %s | Total projete: %.2f CAD | ",
                          Couleurs::DEFAULT, p->getNom().c_str(), total);
        if (commande_.isTermine())
            UIManager::print("payable\n", Couleurs::VERT);
        else
            UIManager::print("non payable\n", Couleurs::ROUGE);
    }
}


void AppController::afficherAide() const {
    UIManager::print("Commandes:\n", Couleurs::CYAN);
    UIManager::print("  c nature|grec        -> Ajouter un yogourt (max 2)\n",     Couleurs::DEFAULT);
    UIManager::print("  sel 1|2              -> Selectionner le yogourt actif\n",   Couleurs::DEFAULT);
    UIManager::print("  f                    -> Ouvrir menu garnitures du yogourt actif\n", Couleurs::DEFAULT);
    UIManager::print("  u                    -> Annuler derniere garniture du yogourt actif\n", Couleurs::DEFAULT);
    UIManager::print("  r                    -> Refaire derniere garniture du yogourt actif\n", Couleurs::DEFAULT);
    UIManager::print("  p                    -> Preparer la commande\n",            Couleurs::DEFAULT);
    UIManager::print("  t                    -> Terminer la commande\n",            Couleurs::DEFAULT);
    UIManager::print("  mode prev|eclair|poly -> Changer le mode de paiement\n",   Couleurs::DEFAULT);
    UIManager::print("  pay                  -> Finaliser paiement (etat Terminee requis)\n", Couleurs::DEFAULT);
    UIManager::print("  pay prev|eclair|poly -> Alias mode + payer\n",             Couleurs::DEFAULT);
    UIManager::print("  total                -> Afficher sous-total et total projete\n", Couleurs::DEFAULT);
    UIManager::print("  sub article          -> S'abonner aux notifications d'un article\n", Couleurs::DEFAULT);
    UIManager::print("  unsub article        -> Se desabonner d'un article\n",      Couleurs::DEFAULT);
    UIManager::print("  subs                 -> Afficher abonnements actifs\n",     Couleurs::DEFAULT);
    UIManager::print("  clear|cls            -> Nettoyer l'ecran\n",               Couleurs::DEFAULT);
    UIManager::print("  s                    -> Afficher les stocks\n",             Couleurs::DEFAULT);
    UIManager::print("  h                    -> Aide\n",                            Couleurs::DEFAULT);
    UIManager::print("  q                    -> Quitter\n",                         Couleurs::DEFAULT);
}


void AppController::traiterCommande(const CommandInput& input) {
    EtatPhaseAppli* etat = commande_.getEtatCourant();
    const std::string& cmd  = input.command;
    const std::string  arg1 = input.args.empty() ? "" : input.args[0];

    if (cmd == "c") {
        etat->AjouterYogourt(arg1);
    } else if (cmd == "sel") {
        if (!arg1.empty()) {
            try { etat->SelectionnerYogourt((unsigned)std::stoi(arg1)); }
            catch (...) { UIManager::print("Index invalide.\n", Couleurs::ROUGE); }
        }
    } else if (cmd == "f") {
        etat->AjouterGarniture();
    } else if (cmd == "u") {
        etat->Annuler();
    } else if (cmd == "r") {
        etat->Reappliquer();
    } else if (cmd == "p") {
        etat->PreparerCommande();
    } else if (cmd == "t") {
        etat->TerminerCommande();
    } else if (cmd == "mode") {
        etat->ChangerModePaiement(arg1);
    } else if (cmd == "pay") {
        if (!arg1.empty()) etat->ChangerModePaiement(arg1);
        etat->Payer();
    } else if (cmd == "total") {
        etat->VoirTotal();
    } else if (cmd == "s") {
        etat->VoirStock();
    } else if (cmd == "sub") {
        traiterSub(arg1);
    } else if (cmd == "unsub") {
        traiterUnsub(arg1);
    } else if (cmd == "subs") {
        traiterSubs();
    }
}


void AppController::traiterSub(const std::string& article) {
    if (article.empty()) return;

    auto cb = notifCallback();

    Inventaire& inv = commande_.getInventaire();
    for (auto it = inv.garnitureBegin(); it != inv.garnitureEnd(); ++it) {
        if (it->_nom == article) {
            abonnement_.sub(*it, cb);
            UIManager::printf("[Abonnement] Notifications actives pour '%s'.\n",
                              Couleurs::CYAN, article.c_str());
            return;
        }
    }

    for (auto it = inv.yogourtBegin(); it != inv.yogourtEnd(); ++it) {
        if (it->_nom == article) {
            yogourtAbonnes_[article]   = cb;
            yogourtEtaitVide_[article] = (it->getQte() == 0);
            UIManager::printf("[Abonnement] Notifications actives pour '%s'.\n",
                              Couleurs::CYAN, article.c_str());
            return;
        }
    }

    UIManager::printf("Article '%s' inconnu.\n", Couleurs::ROUGE, article.c_str());
}

void AppController::traiterUnsub(const std::string& article) {
    if (article.empty()) return;

    auto ity = yogourtAbonnes_.find(article);
    if (ity != yogourtAbonnes_.end()) {
        yogourtAbonnes_.erase(ity);
        yogourtEtaitVide_.erase(article);
        UIManager::printf("[Abonnement] Desabonne de '%s'.\n", Couleurs::CYAN, article.c_str());
        return;
    }

    auto cb = notifCallback();
    abonnement_.unsub(cb, article);
    UIManager::printf("[Abonnement] Desabonne de '%s'.\n", Couleurs::CYAN, article.c_str());
}

void AppController::traiterSubs() const {
    UIManager::print("Abonnements actifs:\n", Couleurs::CYAN);

    for (const auto& [nom, _] : yogourtAbonnes_)
        UIManager::printf("  - %s\n", Couleurs::DEFAULT, nom.c_str());

    auto cb = [](std::string nom) {
        UIManager::printf("  - %s\n", Couleurs::DEFAULT, nom.c_str());
    };
    std::function<void(std::string)> cbFn = cb;
    const_cast<Abonnement&>(abonnement_).subs(cbFn);
}

void AppController::verifierAbonnementsYogourt() {
    Inventaire& inv = commande_.getInventaire();
    for (auto& [nom, cb] : yogourtAbonnes_) {
        for (auto it = inv.yogourtBegin(); it != inv.yogourtEnd(); ++it) {
            if (it->_nom != nom) continue;
            bool estVide   = (it->getQte() == 0);
            bool& etaitVide = yogourtEtaitVide_[nom];
            if (estVide && !etaitVide) {
                etaitVide = true;
                cb("[Notif Abonne] Rupture de stock pour '" + nom + "'.");
            } else if (!estVide && etaitVide) {
                etaitVide = false;
                cb("[Notif Abonne] '" + nom + "' est de retour en stock.");
            }
            break;
        }
    }
}
