#pragma once
#include <pch.h>
#include "Garniture.h"
#include "Yogourt.h"
#include "const.h"
#include <vector>
#include <memory>

class Inventaire {
public:
    static Inventaire& get();
    void destroy();

    // Accès bas niveau
    unsigned int getNumGarnitures() const;
    GarnitureRegistre& getGarniture(size_t index);
    vector<GarnitureRegistre>::iterator garnitureBegin();
    vector<GarnitureRegistre>::iterator garnitureEnd();
    void enregistrerGarniture(GarnitureRegistre&& garniture);

    unsigned int getNumYogourts() const;
    YogourtRegistre& getYogourt(size_t index);
    vector<YogourtRegistre>::iterator yogourtBegin();
    vector<YogourtRegistre>::iterator yogourtEnd();
    void enregistrerYogourt(YogourtRegistre&& yogourt);

    // Gestion stock par type
    bool      yogourtDisponible(typeYoGourt type) const;
    int       getStockYogourt(typeYoGourt type) const;
    void      retirerYogourt(typeYoGourt type);

    bool      garnitureDisponible(typeGarniture type) const;
    int       getStockGarniture(typeGarniture type) const;
    Garniture retirerGarniture(typeGarniture type);
    void      ajouterGarniture(typeGarniture type);

private:
    static Inventaire* inv;
    Inventaire();
    Inventaire(const Inventaire&) = delete;
    Inventaire& operator=(const Inventaire&) = delete;

    vector<YogourtRegistre>   _yogourts;
    vector<GarnitureRegistre> _garnitures;
};
