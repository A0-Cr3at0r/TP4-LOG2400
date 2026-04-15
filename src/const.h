#pragma once
#include <unordered_map>

static const int MAXYOGOURT = 2;
static const enum class typeGarniture {FRUIT, GRANOLA, MIEL, CHOCOLAT};
static const double PRIX_GREC = 2.5;
static const double PRIX_NATURE = 2;
static const double PRIX_FRUIT = 1;
static const double PRIX_GRANOLA  =  0.8;
static const double PRIX_MIEL  =  0.6;
static const double PRIX_CHOCOLAT  =  0.9;
static const double RABAIS_PREV  =  0.1;
static const double RABAIS_POLY =  2;
static const double FRAIS_ECLAIR = 1.5;
static const int QTE_GREC  = 3;
static const int QTE_NATURE  = 1;
static const int QTE_FRUIT  = 5;
static const int QTE_GRANOLA  = 4;
static const int QTE_MIEL  = 4;
static const int QTE_CHOCOLAT  = 1;
static const char DOLLARS = '$';

const std::unordered_map<typeGarniture, std::tuple<double, int>>PRIX_GARNITURES = {
    {typeGarniture::FRUIT, (PRIX_FRUIT, QTE_FRUIT)},
    {typeGarniture::GRANOLA, (PRIX_GRANOLA, QTE_GRANOLA)},
    {typeGarniture::MIEL, (PRIX_MIEL, QTE_MIEL)},
    {typeGarniture::CHOCOLAT, (PRIX_CHOCOLAT, QTE_CHOCOLAT)}
};
