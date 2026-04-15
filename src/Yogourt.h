#include "Garniture.h"
#include <vector>
#include <memory>

class Yogourt {
public:
    Yogourt(bool isGrec);
    ~Yogourt();

    void ajouterGarniture(Garniture garniture);
    void undo();
    double prixTotal();

private: 
    bool isGrec_;
    std::vector<std::unique_ptr<Garniture>> garnitures_;

};

