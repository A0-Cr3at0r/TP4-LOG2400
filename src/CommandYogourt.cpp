#include "CommandYogourt.h"

CommandYogourt::CommandYogourt(Inventaire& inventaire, std::unique_ptr<Paiement>& paiement, Abonnement& abonnement) :
    inventaire_(inventaire),
    paiement_(paiement),
    abonnement_(abonnement)
{}

CommandYogourt::~CommandYogourt()
{}

void CommandYogourt::typeYogourt(std::string yogourt) {
    if (yogourts_.size() == 2)
        return;

    if (yogourt != "nature" && yogourt != "grec") 
        return;

    auto& registre = inventaire_.getYogourt(yogourt == "nature" ? 0 : 1);

    if (registre.getQte()) {
        yogourtActif++;
        yogourts_.push_back(std::make_unique<Yogourt>(Yogourt(registre)));
    }
}

void CommandYogourt::selYogourt(int index) {
    yogourtActif = index;
}

void CommandYogourt::appliquerGarniture(Garniture& garniture) {
    yogourts_[yogourtActif]->ajouterGarniture(garniture);
    while(!actionHistorique_.empty()) {
        actionHistorique_.pop();
    }
}

void CommandYogourt::undo() {
    actionHistorique_.push(yogourts_[yogourtActif]->undo());
}

void CommandYogourt::mode(std::unique_ptr<Paiement>& paiement) {
    paiement_ = std::move(paiement);
}

void CommandYogourt::pay() {
    paiement_->pay(yogourts_[yogourtActif]->prixTotal());
}

void CommandYogourt::pay(std::unique_ptr<Paiement>& paiement) {
    mode(paiement);
    pay();
}

int CommandYogourt::total() {
    return yogourts_[yogourtActif]->prixTotal();
}

int CommandYogourt::totalProjete() {
    return paiement_->totalProjete();
}


std::string CommandYogourt::paiement() {
    return paiement_->toString();
}

void  CommandYogourt::sub(std::string garniture,  std::function<void(std::string)>& abonne) {
    int index = -1;
    if (garniture == "fruits") {
        index = 0;
    } else if (garniture == "granola")
    {
        index = 1;
    } else if (garniture == "chocolat") {
        index = 2;
    } else if (garniture == "miel") {
        index = 3;
    }
    if (index >= 0)
        abonnement_.sub(inventaire_.getGarniture(index), abonne);
    
}

void CommandYogourt::unSub(std::function<void(std::string)>& abonne, std::string nom) {
    abonnement_.unsub(abonne, nom);
}

void CommandYogourt::subs(std::function<void(std::string)>& abonne) {
    abonnement_.subs(abonne);
}



