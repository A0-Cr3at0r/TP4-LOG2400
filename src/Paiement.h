#pragma once
#include <string>

class Paiement {
public:
    virtual ~Paiement() = default;

    virtual bool        estPayable()               const = 0;
    virtual std::string getNom()                   const = 0;
    virtual double      calculerTotal(double montant) const = 0;
};

class Aucun : public Paiement {
public:
    bool        estPayable()               const override;
    std::string getNom()                   const override;
    double      calculerTotal(double montant) const override;
};

class Prevente : public Paiement {
public:
    bool        estPayable()               const override;
    std::string getNom()                   const override;
    double      calculerTotal(double montant) const override;
};

class Eclair : public Paiement {
public:
    bool        estPayable()               const override;
    std::string getNom()                   const override;
    double      calculerTotal(double montant) const override;
};

class Poly : public Paiement {
public:
    bool        estPayable()               const override;
    std::string getNom()                   const override;
    double      calculerTotal(double montant) const override;
};
