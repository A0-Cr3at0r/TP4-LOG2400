/// EtatPhaseAppli.h
// (C) 2026 maplefoxo
// Purpose : 
//

#pragma once

#include <string>
#include <cstdint>

//patron etat
// etat abstract:
class EtatPhaseAppli {
public:
	virtual void AjouterYogourt(std::string type);
	virtual void SelectionnerYogourt(unsigned index);
	virtual void AjouterGarniture(); // ouvrir menu
	virtual void Annuler();
	virtual void Reappliquer();
	virtual void TerminerCommande();
	virtual void PreparerCommande();
	virtual void ChangerModePaiment(std::string mode);
	virtual void Payer(StrategiePaiement& strat); //todo, patron strategie
	virtual void VoirTotal();
	virtual void VoirStock();
private:
	const char* name
};

// etats concrets
class EtatPhaseCommandeIntitiale 	: EtatPhaseAppli {
	virtual void AjouterYogourt(std::string type) override;
	virtual void SelectionnerYogourt(unsigned index) override;
	virtual void AjouterGarniture() override;
	virtual void Annuler() override;
	virtual void Reappliquer() override;
	virtual void TerminerCommande() override;
	virtual void PreparerCommande() override;
	virtual void ChangerModePaiment(std::string mode) override;
	virtual void Payer(StrategiePaiement& strat) override;
	virtual void VoirTotal() override;
	virtual void VoirStock() override;
};
class EtatPhaseCommandePreparation 	: EtatPhaseAppli {
	virtual void AjouterYogourt(std::string type) override;
	virtual void SelectionnerYogourt(unsigned index) override;
	virtual void AjouterGarniture() override;
	virtual void Annuler() override;
	virtual void Reappliquer() override;
	virtual void TerminerCommande() override;
	virtual void PreparerCommande() override;
	virtual void ChangerModePaiment(std::string mode) override;
	virtual void Payer(StrategiePaiement& strat) override;
	virtual void VoirTotal() override;
	virtual void VoirStock() override;
};
class EtatPhaseCommandeTerminee 	: EtatPhaseAppli {
	virtual void AjouterYogourt(std::string type) override;
	virtual void SelectionnerYogourt(unsigned index) override;
	virtual void AjouterGarniture() override;
	virtual void Annuler() override;
	virtual void Reappliquer() override;
	virtual void TerminerCommande() override;
	virtual void PreparerCommande() override;
	virtual void ChangerModePaiment(std::string mode) override;
	virtual void Payer(StrategiePaiement& strat) override;
	virtual void VoirTotal() override;
	virtual void VoirStock() override;
};


