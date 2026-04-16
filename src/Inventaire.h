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
	void destroy();

	unsigned int	getNumGarnitures() const;
	GarnitureRegistre&	getGarniture(size_t index);
	vector<GarnitureRegistre>::iterator garnitureBegin();
	vector<GarnitureRegistre>::iterator garnitureEnd();

	void enregistrerGarniture(GarnitureRegistre&& garniture);

	unsigned int	getNumYogourts() const;
	YogourtRegistre&	getYogourt(size_t index);
	vector<YogourtRegistre>::iterator yogourtBegin();
	vector<YogourtRegistre>::iterator yogourtEnd();
	void enregistrerYogourt(YogourtRegistre&& yogourt);


private:
	// singleton, enforce inst unique
	static Inventaire* inv;

	Inventaire();
	Inventaire(const Inventaire&) = delete;
	Inventaire& operator=(const Inventaire&) = delete;

	vector<YogourtRegistre> _yogourts;
	vector<GarnitureRegistre> _garnitures;
};


