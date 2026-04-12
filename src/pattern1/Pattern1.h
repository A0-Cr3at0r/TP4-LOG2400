#pragma once

// -- TODO : Changer le nom de la classe du fichier et puis ajouter toutes les méthodes nécessaires pour cette composante 
// Composante = Patron de conception, classe, etc etc
class Pattern1
{
public:
    Pattern1() = default;
    Pattern1(const int);
    const int getValue() const;
    
private:
    int value;
};