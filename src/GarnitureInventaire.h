#include "Garniture.h"

class GarnitureInventaire : public Garniture
{

public:
    GarnitureInventaire(typeGarniture typeGarniture, double prix, int qte);
    ~GarnitureInventaire();

    bool isEmpty();
    bool isGarniture(typeGarniture type);

    Garniture retirerGarniture();
    void ajouterGarniture();
private:
    int quantite_;
};



