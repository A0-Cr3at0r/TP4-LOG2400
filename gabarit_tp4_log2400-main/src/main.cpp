#include <iostream>
#include "pattern1/Pattern1.h"
#include "pattern2/Pattern2.h"
#include "ui/ConsoleColors.h"

int main()
{
    Pattern1 p1(20);
    Pattern2 p2(50);

    std::cout << ConsoleColor::yellow << "Hello World!" << ConsoleColor::reset << std::endl;
    std::cout << ConsoleColor::cyan << "Je suis Pattern1 :  " << p1.getValue() << ConsoleColor::reset << std::endl;
    std::cout << ConsoleColor::cyan << "Je suis Pattern2 :  " << p2.getValue() << ConsoleColor::reset << std::endl;
    std::cout << ConsoleColor::magenta << "Bon TP a tous :) " << ConsoleColor::reset << std::endl;

    return 0;
};