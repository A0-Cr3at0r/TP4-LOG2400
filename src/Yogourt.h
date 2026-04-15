#include "Garniture.h"
#include <vector>
#include <memory>

class Yogourt {
public:
    Yogourt(typeYoGourt type);
    ~Yogourt();

    void ajouterGarniture(Garniture garniture);
    void undo();
    double prixTotal();

private: 
    typeYoGourt type_;
    std::vector<std::unique_ptr<Garniture>> garnitures_;

};

