#include "CommandYogourt.h"
#include "EtatPhaseAppli.h"

CommandYogourt::CommandYogourt(Inventaire& inv, Abonnement& abo)
    : inventaire_(inv), abonnement_(abo),
      paiement_(std::make_unique<Aucun>())
{
    etatInitiale_    = std::make_unique<EtatPhaseCommandeInitiale>(this);
    etatPreparation_ = std::make_unique<EtatPhaseCommandePreparation>(this);
    etatTerminee_    = std::make_unique<EtatPhaseCommandeTerminee>(this);
    etatCourant_     = etatInitiale_.get();
}


void CommandYogourt::setState(EtatPhaseAppli* etat) { etatCourant_ = etat; }

EtatPhaseAppli*               CommandYogourt::getEtatCourant()     const { return etatCourant_; }
EtatPhaseCommandeInitiale*    CommandYogourt::getEtatInitiale()    const { return etatInitiale_.get(); }
EtatPhaseCommandePreparation* CommandYogourt::getEtatPreparation() const { return etatPreparation_.get(); }
EtatPhaseCommandeTerminee*    CommandYogourt::getEtatTerminee()    const { return etatTerminee_.get(); }


const std::vector<Yogourt>& CommandYogourt::getYogourts() const { return yogourts_; }

Yogourt* CommandYogourt::getYogourtActif() {
    if (yogourtActif_ < 0 || yogourtActif_ >= (int)yogourts_.size()) return nullptr;
    return &yogourts_[yogourtActif_];
}

int  CommandYogourt::getIndexActif()        const { return yogourtActif_; }
void CommandYogourt::setYogourtActif(int i)       { yogourtActif_ = i; }

void CommandYogourt::ajouterNouveauYogourt(typeYoGourt type) {
    yogourts_.emplace_back(inventaire_.getYogourt(static_cast<size_t>(type)));
    yogourtActif_ = static_cast<int>(yogourts_.size()) - 1;
}

double CommandYogourt::getSousTotal() const {
    double total = 0;
    for (const auto& y : yogourts_)
        total += y.prixTotal();
    return total;
}


Paiement* CommandYogourt::getPaiement() const { return paiement_.get(); }
void      CommandYogourt::setPaiement(std::unique_ptr<Paiement> p) { paiement_ = std::move(p); }


void          CommandYogourt::clearRedo()                       { redoGarniture_.reset(); }
bool          CommandYogourt::hasRedo()                   const { return redoGarniture_.has_value(); }
void          CommandYogourt::setRedoGarniture(typeGarniture t) { redoGarniture_ = t; }
typeGarniture CommandYogourt::getRedoGarniture()          const { return redoGarniture_.value(); }


void CommandYogourt::setTermine(bool val) { termine_ = val; }
bool CommandYogourt::isTermine()    const { return termine_; }


Inventaire& CommandYogourt::getInventaire() { return inventaire_; }
Abonnement& CommandYogourt::getAbonnement() { return abonnement_; }

void CommandYogourt::setNotifyCallback(std::function<void()> cb) { notifyCallback_ = std::move(cb); }

void CommandYogourt::notifyAll() {
    abonnement_.notifier();
    if (notifyCallback_) notifyCallback_();
}
