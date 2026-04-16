#include "Abonnement.h"
#include <algorithm>

Abonnement::Abonnement() {}

Abonnement::~Abonnement() {}

void Abonnement::sub(GarnitureRegistre& gi, const std::function<void(std::string)>& abonne) {
    abonnements_.push_back(std::make_unique<Notifier>(gi, abonne));
}

void Abonnement::unsub(const std::function<void(std::string)>&, std::string nom) {
    abonnements_.erase(
        std::remove_if(abonnements_.begin(), abonnements_.end(),
            [&nom](const std::unique_ptr<Notifier>& n) { return n->getAbonnement() == nom; }),
        abonnements_.end()
    );
}

void Abonnement::subs(const std::function<void(std::string)>& abonne) const {
    for (auto& notifier : abonnements_) {
        abonne(notifier->getAbonnement());
    }
}

void Abonnement::notifier() {
    for (auto& notifier : abonnements_) {
        notifier->notifier();
    }
}
