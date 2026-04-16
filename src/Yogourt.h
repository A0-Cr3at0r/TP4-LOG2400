/// Yogourt.h
// (C) 2026 maplefoxo
// Purpose : 
//

#pragma once

#include <pch.h>

#include "Garniture.h"
#include <vector>
#include <memory>

#include "ui/UIManager.h"


class YogourtRegistre {
public:
    YogourtRegistre(string&& nom, double cout) :
		_cout(cout), _nom(nom)
		{};
	const 	double		_cout;	
	const 	string	_nom;

    unsigned int getQte();
	void incQte();
	int decQte();

private:
   	unsigned int 	_qte;

};


class Yogourt {
public:
    Yogourt(YogourtRegistre& sorte);

    void ajouterGarniture(Garniture&& garniture);
    void undo();
    double prixTotal() const;
    const YogourtRegistre& getSorteYogourt() const;


private: 
    const YogourtRegistre& _yogourt;
    std::vector<Garniture> _garnitures;

};

