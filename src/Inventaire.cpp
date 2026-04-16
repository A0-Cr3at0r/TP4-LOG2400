#include <pch.h>
#include "Inventaire.h"
#include "const.h"
#include "ui/UIManager.h"

Inventaire* Inventaire::inv = nullptr;

Inventaire& Inventaire::get() {
    if (inv == nullptr)
        inv = new Inventaire();
    return *inv;
}

void Inventaire::destroy() {
    if (inv != nullptr) { delete inv; inv = nullptr; }
}

unsigned int Inventaire::getNumGarnitures() const { return _garnitures.size(); }
GarnitureRegistre& Inventaire::getGarniture(size_t i) { return _garnitures.at(i); }
vector<GarnitureRegistre>::iterator Inventaire::garnitureBegin() { return _garnitures.begin(); }
vector<GarnitureRegistre>::iterator Inventaire::garnitureEnd()   { return _garnitures.end(); }
void Inventaire::enregistrerGarniture(GarnitureRegistre&& g) { _garnitures.push_back(std::move(g)); }

unsigned int Inventaire::getNumYogourts() const { return _yogourts.size(); }
YogourtRegistre& Inventaire::getYogourt(size_t i) { return _yogourts.at(i); }
vector<YogourtRegistre>::iterator Inventaire::yogourtBegin() { return _yogourts.begin(); }
vector<YogourtRegistre>::iterator Inventaire::yogourtEnd()   { return _yogourts.end(); }
void Inventaire::enregistrerYogourt(YogourtRegistre&& y) { _yogourts.push_back(std::move(y)); }



bool Inventaire::yogourtDisponible(typeYoGourt type) const {
    return _yogourts[static_cast<size_t>(type)].getQte() > 0;
}

int Inventaire::getStockYogourt(typeYoGourt type) const {
    return static_cast<int>(_yogourts[static_cast<size_t>(type)].getQte());
}

void Inventaire::retirerYogourt(typeYoGourt type) {
    _yogourts[static_cast<size_t>(type)].decQte();
}



bool Inventaire::garnitureDisponible(typeGarniture type) const {
    return _garnitures[static_cast<size_t>(type)].getQte() > 0;
}

int Inventaire::getStockGarniture(typeGarniture type) const {
    return static_cast<int>(_garnitures[static_cast<size_t>(type)].getQte());
}

Garniture Inventaire::retirerGarniture(typeGarniture type) {
    return _garnitures[static_cast<size_t>(type)].decQte();
}

void Inventaire::ajouterGarniture(typeGarniture type) {
    _garnitures[static_cast<size_t>(type)].incQte();
}


Inventaire::Inventaire() {
    enregistrerYogourt(YogourtRegistre("nature",  PRIX_NATURE,  QTE_NATURE));
    enregistrerYogourt(YogourtRegistre("grec",    PRIX_GREC,    QTE_GREC));

    enregistrerGarniture(GarnitureRegistre("fruits",   QTE_FRUIT,    PRIX_FRUIT));
    enregistrerGarniture(GarnitureRegistre("granola",  QTE_GRANOLA,  PRIX_GRANOLA));
    enregistrerGarniture(GarnitureRegistre("miel",     QTE_MIEL,     PRIX_MIEL));
    enregistrerGarniture(GarnitureRegistre("chocolat", QTE_CHOCOLAT, PRIX_CHOCOLAT));
}
