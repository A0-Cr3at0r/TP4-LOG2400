#include "pch.h"

#include <iostream>


#include "ui/UIManager.h"

int main() {
    UIMessage a{"aafsgagsd"};

    UIManager::printf(a);
    UIManager::printf("\ngagaggoogoo%i", Couleurs::CYAN, 69);
    UIManager::cls();
    return 0;
};