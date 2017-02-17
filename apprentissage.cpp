/*
    Neural Network
    apprentissage.cpp
        Créé : 03/02/17
        Fonctions d'apprentissage
*/

#include <math.h>

#include "apprentissage.h"

int calculeErreur(Reseau reseau)
{
    int erreur(0);
    int i(0);
    for (i = 0 ; i < reseau.getNbEntrees() ; i++)
    {
        // l'erreur est le carré de la différence de la sortie obtenue par la sortie attendue
        erreur += pow(((reseau.getSortie(i).getActive())*2-1) - ((reseau.getEntree(i).getActive()*2)-1), 2);
    }
    return erreur;
}

float calculeG_ijk(Reseau& reseau, unsigned int i, unsigned int j, unsigned int k)
{
    return (reseau.getNeurone(i, j).getValeur())*(calculeDelta_ij(reseau, i+1,k));
}

float calculeDelta_ij(Reseau& reseau, unsigned int i, unsigned int j)
{
    unsigned int k(0);
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
            delta = ((reseau.getSortie(j).getActive()*2-1)-(reseau.getEntree(j).getActive()*2-1))*(1+pow(reseau.getEntree(j).getValeur(),2));
            reseau.setNeuroneDelta(i,j, delta);
            reseau.setNeuroneDeltaActuel(i,j, true);
            return delta;
        }
        else
        {
            for (k= 0 ; k < reseau.getNbNeuronesCouches(i+1) ; k++)
            {
                somme += (reseau.getLiaison(i, j, k).getPoids())*(calculeDelta_ij(reseau, i+1,k));
            }
            delta = somme*(1+pow(reseau.getNeurone(i,j).getValeur(),2));
            reseau.setNeuroneDelta(i,j, delta);
            reseau.setNeuroneDeltaActuel(i,j, true);
            return delta;
        }
    }
}

void apprentissage(Reseau& reseau)
{
    unsigned int i(0), j(0), k(0);
    for (i = 0 ; i < reseau.getNbCouches() ; i++)
    {
        for (j = 0 ; j < reseau.getNbNeuronesCouches(i) ; j++)
        {
            reseau.setNeuroneDeltaActuel(i,j, false);
        }
    }
    for (i = 0 ; i < reseau.getNbCouches()-1 ; i++)
    {
        for (j = 0 ; j < reseau.getNbNeuronesCouches(i) ; j++)
        {
            for (k = 0 ; k < reseau.getNbNeuronesCouches(i+1) ; k++)
            {
                reseau.setLiaisonPoids(i,j,k, reseau.getLiaison(i,j,k).getPoids() - (0.1*calculeG_ijk(reseau, i,j,k)));
            }
        }
    }
}
