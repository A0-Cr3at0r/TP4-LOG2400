#include <string>

class Paiement
{

public:
    ~Paiement() = default;

    virtual void pay(double montant) = 0;
    virtual std::string  toString() = 0;
    double totalProjete();
protected:
    double total_;
};


class Prevente : public Paiement {
public:
    void pay(double montant) override;
    std::string toString() override;
};

class Eclair : public Paiement
{
public:
    void pay(double montant) override;
    std::string toString() override;
};


class Poly : public Paiement
{
public:
    void pay(double montant) override;
    std::string toString() override;
};
