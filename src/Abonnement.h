#pragma once
#include "Notifier.h"
#include <memory>

class Abonnement
{
public:
    Abonnement();
    ~Abonnement();

    void sub(GarnitureInventaire& gi, std::function<void(std::string)>& abonne);
    void unsub(std::function<void(std::string)>& abonne, std::string nom);
    void subs(std::function<void(std::string)>& abonne);

private:
    std::vector<std::unique_ptr<Notifier>> abonnements_;
};


