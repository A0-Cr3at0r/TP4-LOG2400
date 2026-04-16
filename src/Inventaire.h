/// Inventaire.h
// (C) 2026 maplefoxo
// Purpose : 
//

#pragma once

#include <pch.h>

#include "Garniture.h"
#include "Yogourt.h"
#include <vector>
#include <memory>

class Inventaire { // patron singleton, observateur
public:

	static Inventaire& get();


	unsigned int	getNumGarnitures() const;
	weak_ptr<Garniture>&	getGarniture(unsigned int index);
	void enregistrerGarniture(GarnitureRegistre&&);

	unsigned int	getNumYogourts() const;
	weak_ptr<Garniture>&	getYogourt(unsigned int index);
	void enregistrerGarniture(Yogourt&&);
private:
	// singleton, enforce inst unique
	Inventaire();
	Inventaire(const Inventaire&) = delete;
	Inventaire& operator=(const Inventaire&) = delete;


	const vector<unique_ptr<Yogourt>>& yogourts;
	const vector<unique_ptr<GarnitureRegistre>>& garnitures;
};
