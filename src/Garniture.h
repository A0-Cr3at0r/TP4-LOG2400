/// Garniture.h
// (C) 2026 maplefoxo
// Purpose : 
//

#pragma once

#include <pch.h>


class GarnitureRegistre {
public:
	GarnitureRegistre(string&& nom, const unsigned int qte_initiale, const double cout);
	
	unsigned int getQte();
	void incQte();
	Garniture decQte();
		
	const 	double		_cout;	
	const 	string		_nom;
	
private:
	unsigned int 	_qte;
};


class Garniture {
public:
	friend class GarnitureRegistre;

	double getCout() const;
	string_view& getNom() const;

	Garniture(const Garniture&) = delete;
	Garniture& operator=(const Garniture&) = delete;
private:
	Garniture(GarnitureRegistre& source);
	const GarnitureRegistre& source;
};