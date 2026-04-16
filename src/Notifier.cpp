#include "Notifier.h"

Notifier::Notifier(GarnitureRegistre& gi, std::function<void(std::string)>& abonne) : 
gi_(gi)
{abonnes_.push_back(abonne);}

Notifier::~Notifier() {}

void Notifier::notifier() {
    if (!(gi_.getQte()) && !etaitVide_) {
        etaitVide_ = true;
        for (auto&& abonne : abonnes_) {
            abonne("[Notif Abonne] Rupture de stock pour '" + gi_._nom + "'.");
        }
    } else if (gi_.getQte() && etaitVide_)
    {
        etaitVide_ = false;
        for (auto&& abonne : abonnes_) {
            abonne("[Notif Abonne] '" + gi_._nom + "' est de retour en stock.");
        }
    }
    
}


std::string Notifier::getAbonnement() {
    return gi_._nom;
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

