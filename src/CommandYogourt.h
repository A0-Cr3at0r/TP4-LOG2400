#pragma once
#include "Inventaire.h"
#include "Paiement.h"
#include "Abonnement.h"
#include "Yogourt.h"
#include "const.h"
#include <vector>
#include <memory>
#include <optional>

class EtatPhaseAppli;
class EtatPhaseCommandeInitiale;
class EtatPhaseCommandePreparation;
class EtatPhaseCommandeTerminee;

class CommandYogourt {
public:
    explicit CommandYogourt(Inventaire& inv, Abonnement& abo);
    ~CommandYogourt() = default;

    void setState(EtatPhaseAppli* etat);
    EtatPhaseAppli*               getEtatCourant()     const;
    EtatPhaseCommandeInitiale*    getEtatInitiale()    const;
    EtatPhaseCommandePreparation* getEtatPreparation() const;
    EtatPhaseCommandeTerminee*    getEtatTerminee()    const;

    const std::vector<Yogourt>& getYogourts() const;
    Yogourt*                    getYogourtActif();
    int                         getIndexActif() const;
    void                        setYogourtActif(int index);
    void                        ajouterNouveauYogourt(typeYoGourt type);

    double getSousTotal() const;

    Paiement*                getPaiement() const;
    void                     setPaiement(std::unique_ptr<Paiement> p);

    void          clearRedo();
    bool          hasRedo() const;
    void          setRedoGarniture(typeGarniture type);
    typeGarniture getRedoGarniture() const;

    void setTermine(bool val);
    bool isTermine() const;

    Inventaire& getInventaire();
    Abonnement& getAbonnement();

private:
    Inventaire& inventaire_;
    Abonnement& abonnement_;

    std::vector<Yogourt>         yogourts_;
    int                          yogourtActif_ = -1;
    std::unique_ptr<Paiement>    paiement_;
    std::optional<typeGarniture> redoGarniture_;
    bool                         termine_ = false;

    std::unique_ptr<EtatPhaseCommandeInitiale>    etatInitiale_;
    std::unique_ptr<EtatPhaseCommandePreparation> etatPreparation_;
    std::unique_ptr<EtatPhaseCommandeTerminee>    etatTerminee_;
    EtatPhaseAppli*                               etatCourant_ = nullptr;
};
