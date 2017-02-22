/*
    Neural Network
    reseau.h
        Créé : 09/09/16
        Fonctions relatives au réseau
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "reseau.h"
#include "neurone.h"
#include "liaison.h"

using namespace std;

Reseau::Reseau(vector<unsigned int> nbNeuroneCouche)
{
    unsigned int layerCount = nbNeuroneCouche.size();

    // Setting the seed for the rand() function with current time
    srand(time(nullptr));
    float poids;

    Neurone neurone;
    Liaison liaison;
    // listes temporaire
    vector< Neurone > liNeurone;
    vector< Liaison > liLiaison;
    vector< vector < Liaison > > liLiLiaison;

    //  Création du tableau de neurones
    for (unsigned int i = 0 ; i < layerCount ; i++ )
    {
        // On stocke le nb de neurones par couches
        m_nbNeuroneCouche.push_back(nbNeuroneCouche[i]);
        for (unsigned int j = 0 ; j < nbNeuroneCouche[i] ; j++ )
        {
            liNeurone.push_back(neurone);
        }
        m_neurones.push_back(liNeurone);
        liNeurone.clear();
    }

    // Création du tableau 3D de liaisons
    for (unsigned int k = 0 ; k < layerCount-1 ; k++)
    {
        for (unsigned int i = 0 ; i < nbNeuroneCouche[k] ; i++ )
        {
            for (unsigned int j = 0 ; j < nbNeuroneCouche[k+1] ; j++ )
            {
                poids = (((rand()%PRECISION)+1))/((float)PRECISION);
                liaison.changerPoids(poids);
                liLiaison.push_back(liaison);
            }
            liLiLiaison.push_back(liLiaison);
            liLiaison.clear();
        }
        m_liaisons.push_back(liLiLiaison);
        liLiLiaison.clear();
    }
}

Reseau::~Reseau()
{
    //dtor
}

Neurone Reseau::getEntree(unsigned int i)
{
    if (i < getNbEntrees())
    {
        return Neurone(m_neurones[0][i]);
    }
    return 0;
}

Neurone Reseau::getSortie(unsigned int i)
{
    unsigned int layerCount = getNbCouches();

    if (i < m_nbNeuroneCouche[layerCount-1])
    {
        return Neurone(m_neurones[layerCount-1][i]);
    }
    return 0;
}

Liaison Reseau::getLiaison(unsigned int i, unsigned int j, unsigned int k)
{
    if (i < getNbSorties()-1)
    {
        return m_liaisons[i][j][k];
    }
    return Liaison(0);
}

unsigned int Reseau::getNbEntrees()
{
    return m_nbNeuroneCouche[0];
}

unsigned int Reseau::getNbSorties()
{
    return m_nbNeuroneCouche[getNbCouches()-1];
}

unsigned int Reseau::getNbCouches()
{
    return m_nbNeuroneCouche.size();
}

unsigned int Reseau::getNbNeuronesCouches(unsigned int i)
{
    if (i < getNbCouches())
    {
        return m_nbNeuroneCouche[i];
    }
    return 0;
}

void Reseau::setEntrees(vector<bool> entrees)
{
    if (getNbEntrees() != entrees.size())
    {
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0 ; i < getNbEntrees() ; i++ )
    {
        m_neurones[0][i].setActive(entrees[i]);
        m_neurones[0][i].setActuel(true);
    }
}

void Reseau::setEntreesActuelles(bool actuelles)
{
    for (unsigned int i = 0 ; i < getNbEntrees() ; i++)
    {
        m_neurones[0][i].setActuel(actuelles);
    }
}

vector<bool> Reseau::calculeSorties()
{
    vector<bool> sorties;
    unsigned int layerCount = getNbCouches();

    // On désactualise les neurones de la couche 1 à la couche de sortie
    for (unsigned int i=1 ; i < layerCount ; i++)
    {
        for (unsigned int j = 0 ; j < getNbNeuronesCouches(i) ; j++)
        {
            m_neurones[i][j].setActuel(false);
        }
    }
    // On demande le calcul des neurones de sortie
    for (unsigned int i = 0 ; i < m_nbNeuroneCouche[layerCount-1] ; i++)
    {
        // Fonction récursive
        caluleNeurone(layerCount-1, i);
        // On ajoute l'activation de la sortie à la variable de retour
        sorties.push_back(m_neurones[layerCount-1][i].getActive());
    }
    return sorties;
}

void Reseau::caluleNeurone(unsigned int i, unsigned int j)
{
    float somme(0);

    // Si on est pas actualisé, on calcule
    if ( m_neurones[i][j].getActuel() == 0)
    {
        // Si une entrée est non actualisée, on a un problème
        if ( i == 0 )
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            somme = 0;
            for (unsigned int k = 0 ; k < m_nbNeuroneCouche[i-1] ; k++ )
            {
                caluleNeurone(i-1,k);
                somme += (m_neurones[i-1][k].getActive()*2 - 1) * m_liaisons[i-1][k][j].getPoids();
            }
            // sigmoide actualise le neurone
            m_neurones[i][j].sigmoide(somme);
        }
    }
}

void Reseau::afficheNeurones()
{
    cout << "Neurones :" << endl;
    for (unsigned int i = 0 ; i < getNbCouches() ; i++)
    {
        for (unsigned int j = 0 ; j < getNbNeuronesCouches(i) ; j++)
        {
            cout << m_neurones[i][j].getActive() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Reseau::afficheLiaisons()
{
    cout << "Liaisons :" << endl;
    for (unsigned int i = 0 ; i < m_liaisons.size() ; i++)
    {
        cout << i << " : " << endl;
        for (unsigned int j = 0 ; j < m_liaisons[i].size() ; j++)
        {
            for (unsigned int k = 0 ; k < m_liaisons[i][j].size() ; k++)
            {
                cout << getLiaison(i,j,k).getPoids() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}
