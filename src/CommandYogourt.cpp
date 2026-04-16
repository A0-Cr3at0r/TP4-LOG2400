#include "CommandYogourt.h"

CommandYogourt::CommandYogourt(Inventaire& inventaire, std::unique_ptr<Paiement>& paiement, Abonnement& abonnement) :
    inventaire_(inventaire),
    paiement_(paiement),
    abonnement_(abonnement)
{}

CommandYogourt::~CommandYogourt()
{}

void CommandYogourt::typeYogourt(std::string Yogourt) {
    
}

