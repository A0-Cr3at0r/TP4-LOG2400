#include "Garniture.h"
#include <string>


class GarnitureInventaire : public Garniture
{

public:
    GarnitureInventaire(typeGarniture typeGarniture, double prix, int qte);
    ~GarnitureInventaire();

    bool isEmpty();
    bool wasEmpty();
    void observer();
    bool isGarniture(typeGarniture type);
    std::string getNom();

    Garniture retirerGarniture();
    void ajouterGarniture();
private:
    int quantite_;
};



