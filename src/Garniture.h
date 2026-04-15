#pragma once

#include "const.h"

class Garniture {
public:
    Garniture(typeGarniture typeGarniture, double prix);
    ~Garniture();
    double getPrice();

protected:
    typeGarniture typeGarniture_;
    double prix_;
};

