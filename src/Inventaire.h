#include "GarnitureInventaire.h"
#include <vector>
#include <memory>

class Inventaire
{

public:
    Inventaire();
    ~Inventaire();

    Garniture retirerGarniture(typeGarniture type);
    void ajouterGarniture(typeGarniture type);

private:
    std::vector<std::unique_ptr<GarnitureInventaire>> inventaires_;
};


