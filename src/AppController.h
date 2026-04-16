#pragma once
#include "CommandYogourt.h"
#include "Abonnement.h"
#include "ui/UIManager.h"
#include <functional>
#include <unordered_map>
#include <string>

class AppController {
public:
    AppController();
    ~AppController();

    void run();

private:
    Abonnement     abonnement_;
    CommandYogourt commande_;

    // Abonnements yogourts (Notifier ne supporte que GarnitureRegistre)
    std::unordered_map<std::string, std::function<void(std::string)>> yogourtAbonnes_;
    std::unordered_map<std::string, bool>                             yogourtEtaitVide_;

    void afficherStatut() const;
    void afficherAide()   const;

    void traiterCommande(const CommandInput& input);

    void traiterSub(const std::string& article);
    void traiterUnsub(const std::string& article);
    void traiterSubs() const;
    void verifierAbonnementsYogourt();

    static std::function<void(std::string)> notifCallback();
};
