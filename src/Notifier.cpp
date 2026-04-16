#include "Notifier.h"

Notifier::Notifier(GarnitureInventaire& gi, std::function<void(std::string)>& abonne) : 
gi_(gi)
{abonnes_.push_back(abonne);}

Notifier::~Notifier() {}

void Notifier::notifier() {
    if (gi_.isEmpty() && !gi_.wasEmpty()) {
        for (auto&& abonne : abonnes_) {
            abonne("[Notif Abonne] Rupture de stock pour " + gi_.getNom());
        }
    } else if (!gi_.isEmpty() && gi_.wasEmpty())
    {
        for (auto&& abonne : abonnes_) {
            abonne("[Notif Abonne] " + gi_.getNom() +  " est de retour");
        }
    }
    
}


std::string Notifier::getAbonnement() {
    return gi_.getNom();
}


void Notifier::addAbonne(std::function<void(std::string)>& abonne) {
    abonnes_.push_back(abonne);
}

void Notifier::removeAbonne(std::function<void(std::string)>& abonne) {
    auto it = std::remove(abonnes_.begin(), abonnes_.end(), abonne);
    abonnes_.erase(it, abonnes_.end());
}

bool Notifier::contains(std::function<void(std::string)>& abonne) {
    return std::find(abonnes_.begin(), abonnes_.end(), abonne) != abonnes_.end();
}

