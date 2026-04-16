/// Garniture.h
// (C) 2026 maplefoxo

#pragma once

#include <pch.h>
#include "Aliment.h"

class Garniture;

class GarnitureRegistre : public AlimentRegistre<GarnitureRegistre, Garniture> {
public:
	GarnitureRegistre(string&& nom, unsigned int qte_initiale, double cout)
		: AlimentRegistre(std::move(nom), qte_initiale, cout) {}

	TypeAliment getTypeAliment() override { return TypeAliment::GARNITURE; }
};

class Garniture : public Aliment<GarnitureRegistre> {
public:
	Garniture(Garniture&&)            = default;
	Garniture& operator=(Garniture&&) = default;
	Garniture(const Garniture&)            = delete;
	Garniture& operator=(const Garniture&) = delete;

	template<typename, typename> friend class AlimentRegistre;

private:
	explicit Garniture(GarnitureRegistre& source) : Aliment(source) {}
};
