/*
    Neural Network
    apprentissage.h
        Créé : 03/02/17
        Déclaration des fonctions d'apprentissage
*/

#ifndef DEF_APPRENTISSAGE

#define DEF_APPRENTISSAGE

#include "reseau.h"

int calculeErreur(Reseau reseau, std::vector< bool > sortieSouhaitee);
float calculeG_ijk(Reseau& reseau, std::vector< bool > sortieSouhaitee, unsigned int i, unsigned int j, unsigned int k);
float calculeDelta_ij(Reseau& reseau, std::vector< bool > sortieSouhaitee, unsigned int i, unsigned int j);
void apprentissage(std::vector< bool > sortieSouhaitee, Reseau& reseau, float vitesseApprentissage);
std::vector< bool > binariseNb(unsigned int nb, unsigned int taille);
void apprentissageAleatoire(std::vector< std::vector<bool> > sorties, Reseau& reseau, int facteurMultiplicatif, unsigned int vitesse);
void apprentissageProgressif(std::vector< std::vector<bool> > sorties, Reseau& reseau, int maxError);

#endif // DEF_APPRENTISSAGE
