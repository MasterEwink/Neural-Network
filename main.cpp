/*
    Neural Network
        Un réseau de neurones sur le même modèle que "Réseau Neurones liaisons"
    main.cpp
        Créé : 09/09/16
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "reseau.h"

using namespace std;

int main()
{
    vector<unsigned int> nbNeuroneCouche;
    vector<bool> entrees;
    vector<bool> sorties;

    // Je fais tout à la main pour les tests (flemme de déclarer des incréments)
    nbNeuroneCouche.push_back(15);
    nbNeuroneCouche.push_back(8);
    nbNeuroneCouche.push_back(15);

    Reseau res_test(nbNeuroneCouche);

    entrees.push_back(true);
    entrees.push_back(false);
    entrees.push_back(false);
    entrees.push_back(true);
    entrees.push_back(false);
    entrees.push_back(true);
    entrees.push_back(false);
    entrees.push_back(false);
    entrees.push_back(true);
    entrees.push_back(true);
    entrees.push_back(false);
    entrees.push_back(true);
    entrees.push_back(true);
    entrees.push_back(false);
    entrees.push_back(true);

    res_test.setEntrees(entrees);

    sorties = res_test.calculeSorties();

    res_test.afficheNeurones();

    return 0;
}
