#include "pch.h"

#include <iostream>


#include "ui/UIManager.h"
#include "Inventaire.h"

int main() {
    UIManager::printf("asbestos :  %i \n", Couleurs::BLEU, Inventaire::get().getNumGarnitures());

    return 0;
};