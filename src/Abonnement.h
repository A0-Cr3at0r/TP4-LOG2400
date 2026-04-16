#pragma once
#include "Notifier.h"

class Abonnement
{
public:
    Abonnement();
    ~Abonnement();

    void sub(GarnitureRegistre& gi, const std::function<void(std::string)>& abonne);
    void unsub(const std::function<void(std::string)>& abonne, std::string nom);
    void subs(const std::function<void(std::string)>& abonne) const;
    void notifier();

private:
    std::vector<std::unique_ptr<Notifier>> abonnements_;
};


