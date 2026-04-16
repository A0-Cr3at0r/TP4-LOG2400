#pragma once
#include "Garniture.h"
#include <functional>



class Notifier
{

public:
    Notifier(GarnitureRegistre& gi, std::function<void(std::string)>& abonne);
    ~Notifier();

    void notifier();
    std::string getAbonnement();
    void addAbonne(std::function<void(std::string)>& abonne);
    void removeAbonne(std::function<void(std::string)>& abonne);
    bool contains(std::function<void(std::string)>& abonne);

private: 
    GarnitureRegistre& gi_;
    YogourtRegistre& yi_;
    std::vector<std::function<void(std::string)>> abonnes_;
    bool etaitVide_ = true;
};



