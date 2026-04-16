#include "Abonnement.h"

Abonnement::Abonnement() {}

Abonnement::~Abonnement() {}

void Abonnement::sub(GarnitureRegistre& gi, std::function<void(std::string)>& abonne) {
    auto& abonnement = std::make_unique<Notifier>(gi, abonne);
    abonnements_.push_back(abonnement);
}

void Abonnement::sub(YogourtRegistre& yi, std::function<void(std::string)>& abonne) {
    auto& abonnement = std::make_unique<Notifier>(yi, abonne);
    abonnements_.push_back(abonnement);
}

void Abonnement::unsub(std::function<void(std::string)>& abonne, std::string nom) {
    for (auto& notifier : abonnements_) {
        if (notifier->getAbonnement() == nom) {
            notifier->removeAbonne(abonne);
        }
    }
}
void Abonnement::subs(std::function<void(std::string)>& abonne) {
    for (auto& notifier : abonnements_) {
        if (notifier->contains(abonne)) {
            abonne(notifier->getAbonnement());
        } 
    }
    
}

void Abonnement::notifier() {
    for (auto& notifier : abonnements_) {
        notifier->notifier();
    }    
}
