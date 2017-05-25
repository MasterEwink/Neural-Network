/*
    Neural Network
    apprentissage.cpp
        Créé : 03/02/17
        Fonctions d'apprentissage
*/

#include <cstdlib>
#include <iostream>
#include <math.h>

#include "apprentissage.h"

using namespace std;

int calculeErreur(Reseau reseau, vector< bool > sortieSouhaitee)
{
    int erreur(0);
    int i(0);
    for (i = 0 ; i < reseau.getNbSorties() ; i++)
    {
        erreur += pow((reseau.getSortie(i).getActive()) - (sortieSouhaitee[i]), 2);
    }
    return erreur;  // le nombre de différences
}

float calculeG_ijk(Reseau& reseau, vector< bool > sortieSouhaitee, unsigned int i, unsigned int j, unsigned int k)
{
    return (reseau.getNeurone(i, j).getValeur())*(calculeDelta_ij(reseau, sortieSouhaitee, i+1,k));
}

float calculeDelta_ij(Reseau& reseau, vector< bool > sortieSouhaitee, unsigned int i, unsigned int j)
{
    float somme(0.);
    float delta(0.);

    if (reseau.getNeurone(i,j).getDeltaActuel())
    {
        return reseau.getNeurone(i,j).getDelta();
    }
    else
    {
        if (i == reseau.getNbCouches()-1)
        {
            // cette ligne ne peut sortir que des 0
            //delta = ((reseau.getSortie(j).getValeur())-(sortieSouhaitee[j]*2-1))*(1-pow(reseau.getSortie(j).getValeur(),2));
            delta = ((reseau.getSortie(j).getValeur())-(sortieSouhaitee[j]*2-1));
            reseau.setNeuroneDelta(i,j, delta);
            reseau.setNeuroneDeltaActuel(i,j, true);
            return delta;
        }
        else
        {
            for ( unsigned int k = 0 ; k < reseau.getNbNeuronesCouches(i+1) ; k++ )
            {
                somme += (reseau.getLiaison(i, j, k).getPoids())*(calculeDelta_ij(reseau, sortieSouhaitee, i+1,k));
            }
            delta = somme*(1-pow(reseau.getNeurone(i,j).getValeur(),2));
            reseau.setNeuroneDelta(i,j, delta);
            reseau.setNeuroneDeltaActuel(i,j, true);
            return delta;
        }
    }
}

void apprentissage(vector< bool > sortieSouhaitee, Reseau& reseau, float vitesseApprentissage)
{
    for ( unsigned int i = 0 ; i < reseau.getNbCouches() ; i++ )
    {
        for ( unsigned int j = 0 ; j < reseau.getNbNeuronesCouches(i) ; j++ )
        {
            reseau.setNeuroneDeltaActuel(i,j, false);
        }
    }
    for ( unsigned int i = 0 ; i < reseau.getNbCouches()-1 ; i++ )
    {
        for ( unsigned int j = 0 ; j < reseau.getNbNeuronesCouches(i) ; j++ )
        {
            for ( unsigned int k = 0 ; k < reseau.getNbNeuronesCouches(i+1) ; k++ )
            {
                reseau.setLiaisonPoids(i,j,k, reseau.getLiaison(i,j,k).getPoids() - (vitesseApprentissage*calculeG_ijk(reseau, sortieSouhaitee, i,j,k)));
            }
        }
    }
}

vector< bool > binariseNb(unsigned int nb, unsigned int taille)
{
    vector< bool> binaire;
    bool temp(false);
    while (nb > 0)
    {
        binaire.push_back(nb-2*(nb/2));
        nb=nb/2;
    }
    if (taille < binaire.size())
    {
        exit(EXIT_FAILURE);
    }
    for ( unsigned int i = binaire.size() ; i < taille ; i++ )
    {
        binaire.push_back(false);
    }
    for ( unsigned int i = 0 ; i < binaire.size()/2 ; i++ )
    {
        temp = binaire[i];
        binaire[i] = binaire[binaire.size()-(i+1)];
        binaire[binaire.size()-(i+1)] = temp;
    }
    return binaire;
}

void apprentissageAleatoire(vector< vector<bool> > sorties, Reseau& reseau, int facteurMultiplicatif, unsigned int vitesse)
{
    unsigned int i(0);
    unsigned int k(0);
    unsigned int n = facteurMultiplicatif*reseau.getNbSorties()*sorties.size();
    vector< bool > entree;
    for (i = 0 ; i < n ; i++)
    {
        k = rand()%sorties.size();
        entree = binariseNb(k, reseau.getNbEntrees());
        reseau.setEntrees(entree);
        reseau.calculeSorties();
        apprentissage(sorties[k], reseau, vitesse);
    }
}

void apprentissageProgressif(vector< vector<bool> > sorties, Reseau& reseau, int maxError)
{
    bool sortiesPrecAprises;
    vector< bool > entree;

    for (unsigned int i = 0 ; i < sorties.size() ; i++)
    {
        entree = binariseNb(i, reseau.getNbEntrees());
        reseau.setEntrees(entree);
        cout << "Apprentissage de la sortie " << i << endl;
        do
        {
            reseau.calculeSorties();
            apprentissage(sorties[i], reseau, 0.1);
            reseau.calculeSorties();
        }while (calculeErreur(reseau, sorties[i]) > maxError);
        cout << "Reapprentissage des sorties precedentes : ";
        sortiesPrecAprises = false;
        while (!sortiesPrecAprises)
        {
            sortiesPrecAprises = true;
            for (unsigned int j = 0 ; j <= i ; j++)
            {
                entree = binariseNb(j, reseau.getNbEntrees());
                reseau.setEntrees(entree);
                reseau.calculeSorties();
                if (calculeErreur(reseau, sorties[j]) > maxError)
                {
                    apprentissage(sorties[i], reseau, 0.1);
                }
                reseau.calculeSorties();
                if (calculeErreur(reseau, sorties[j]) > maxError)
                {
                    sortiesPrecAprises = false;
                }
            }
        }
        cout << endl;
    }
}
