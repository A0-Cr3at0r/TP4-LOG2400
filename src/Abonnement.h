#pragma once
#include "Notifier.h"

class Abonnement
{
public:
    Abonnement();
    ~Abonnement();

    void sub(GarnitureRegistre& gi, std::function<void(std::string)>& abonne);
    void sub(YogourtRegistre& gi, std::function<void(std::string)>& abonne);
    void unsub(std::function<void(std::string)>& abonne, std::string nom);
    void subs(std::function<void(std::string)>& abonne);
    void notifier();

private:
    std::vector<std::unique_ptr<Notifier>> abonnements_;
};


