#include "Notifier.h"

Notifier::Notifier(GarnitureRegistre& gi, std::function<void(std::string)>& abonne) : 
gi_(&gi)
{abonnes_.push_back(abonne);}

Notifier::Notifier(YogourtRegistre& yi, std::function<void(std::string)>& abonne) : 
yi_(&yi)
{abonnes_.push_back(abonne);}

Notifier::~Notifier() {}

void Notifier::notifier() {
    if (gi_) {
        if (!(gi_->getQte()) && !etaitVide_) {
            etaitVide_ = true;
            for (auto&& abonne : abonnes_) {
                abonne("[Notif Abonne] Rupture de stock pour " + gi_->_nom);
            }
        } else if (gi_->getQte() && etaitVide_) {   
            etaitVide_ = false;
            for (auto&& abonne : abonnes_) {
                abonne("[Notif Abonne] " + gi_->_nom +  " est de retour");
            }
        }
        return;
    }
    if (!etaitVide_) {
        etaitVide_ = true;
        for (auto&& abonne : abonnes_) {
            abonne("[Notif Abonne] Rupture de stock pour " + yi_->_nom);
        }
    }
    
    
}


std::string Notifier::getAbonnement() {
    if (gi_) 
        return gi_->_nom;

    return yi_->_nom;
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

