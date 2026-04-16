#pragma once
//#include "GarnitureInventaire.h"
#include <functional>
#include <vector>
#include <string>


class Notifier
{

public:
//    Notifier(GarnitureInventaire& gi, std::function<void(std::string)>& abonne);
    ~Notifier();

    void notifier();
    std::string getAbonnement();
    void addAbonne(std::function<void(std::string)>& abonne);
    void removeAbonne(std::function<void(std::string)>& abonne);
    bool contains(std::function<void(std::string)>& abonne);

private: 
//    GarnitureInventaire& gi_;
    std::vector<std::function<void(std::string)>> abonnes_;
};



