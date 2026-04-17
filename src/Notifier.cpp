#include "Notifier.h"
#include <algorithm>

Notifier::Notifier(GarnitureRegistre& gi, const std::function<void(std::string)>& abonne)
    : gi_(gi), etaitVide_(gi.getQte() == 0)
{
    abonnes_.push_back(abonne);
}

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

void Notifier::addAbonne(const std::function<void(std::string)>& abonne) {
    abonnes_.push_back(abonne);
}

void Notifier::removeAbonne(const std::function<void(std::string)>&) {
    abonnes_.clear();
}

bool Notifier::contains(const std::function<void(std::string)>&) {
    return !abonnes_.empty();
}

