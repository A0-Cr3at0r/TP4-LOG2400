#pragma once
#include <string>

class CommandYogourt;

class EtatPhaseAppli {
public:
    EtatPhaseAppli(CommandYogourt* commande, const char* nom)
        : commande_(commande), nom_(nom) {}
    virtual ~EtatPhaseAppli() = default;

    const char* getNom() const { return nom_; }

    virtual void AjouterYogourt(const std::string& type) = 0;
    virtual void SelectionnerYogourt(unsigned index) = 0;
    virtual void AjouterGarniture() = 0;
    virtual void Annuler() = 0;
    virtual void Reappliquer() = 0;
    virtual void PreparerCommande() = 0;
    virtual void TerminerCommande();
    virtual void ChangerModePaiement(const std::string& mode) = 0;
    virtual void Payer();
    virtual void VoirTotal();
    virtual void VoirStock();

protected:
    CommandYogourt* commande_;
    const char* nom_;
};

class EtatPhaseCommandeInitiale : public EtatPhaseAppli {
public:
    explicit EtatPhaseCommandeInitiale(CommandYogourt* c)
        : EtatPhaseAppli(c, "Initiale") {}

    void AjouterYogourt(const std::string& type) override;
    void SelectionnerYogourt(unsigned index) override;
    void AjouterGarniture() override;
    void Annuler() override;
    void Reappliquer() override;
    void PreparerCommande() override;
    void ChangerModePaiement(const std::string& mode) override;
    void VoirTotal() override;
    void VoirStock() override;
};

class EtatPhaseCommandePreparation : public EtatPhaseAppli {
public:
    explicit EtatPhaseCommandePreparation(CommandYogourt* c)
        : EtatPhaseAppli(c, "En preparation") {}

    void Annuler() override;
    void TerminerCommande() override;
    void VoirTotal() override;
    void VoirStock() override;
};

class EtatPhaseCommandeTerminee : public EtatPhaseAppli {
public:
    explicit EtatPhaseCommandeTerminee(CommandYogourt* c)
        : EtatPhaseAppli(c, "Terminee") {}

    void AjouterYogourt(const std::string& type) override;
    void Annuler() override;
    void TerminerCommande() override;
    void ChangerModePaiement(const std::string& mode) override;
    void Payer() override;
    void VoirTotal() override;
    void VoirStock() override;
};
