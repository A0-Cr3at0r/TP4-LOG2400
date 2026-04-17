#pragma once
#include "Garniture.h"
#include <functional>



class Notifier
{

public:
    Notifier(GarnitureRegistre& gi, const std::function<void(std::string)>& abonne);
    ~Notifier();

    void notifier();
    std::string getAbonnement();
    void addAbonne(const std::function<void(std::string)>& abonne);
    void removeAbonne(const std::function<void(std::string)>& abonne);
    bool contains(const std::function<void(std::string)>& abonne);

private:
    GarnitureRegistre& gi_;
    std::vector<std::function<void(std::string)>> abonnes_;
    bool etaitVide_;
};



