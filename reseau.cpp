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
    // Le nombre de couches est indiqué dans la taille de nbNeuroneCouche
    srand(time(NULL));
    unsigned int i(0), j(0), k(0);
    float poids;

    Neurone neurone;
    Liaison liaison;
    // listes temporaire
    vector< Neurone > liNeurone;
    vector< Liaison > liLiaison;
    vector< vector < Liaison > > liLiLiaison;

    //  Création du tableau de neurones
    for (i = 0 ; i < nbNeuroneCouche.size() ; i++ )
    {
        // On stocke le nb de neurones par couches
        m_nbNeuroneCouche.push_back(nbNeuroneCouche[i]);
        for ( j = 0 ; j < nbNeuroneCouche[i] ; j++ )
        {
            neurone.init();
            liNeurone.push_back(neurone);
        }
        m_neurones.push_back(liNeurone);
        liNeurone.clear();
    }

    // Création du tableau 3D de liaisons
    for ( k = 0 ; k < nbNeuroneCouche.size()-1 ; k++)
    {
        for ( i = 0 ; i < nbNeuroneCouche[k] ; i++ )
        {
            for ( j = 0 ; j < nbNeuroneCouche[k+1] ; j++ )
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
    unsigned int i(0), j(0);

    m_nbNeuroneCouche.clear();
    for (i = 0 ; i < m_neurones.size() ; i++)
    {
        m_neurones[i].clear();
    }
    m_neurones.clear();
    for (i = 0 ; i < m_liaisons.size() ; i++)
    {
        for (j = 0 ; j < m_liaisons.size() ; j++)
        {
            m_liaisons[i][j].clear();
        }
        m_liaisons[i].clear();
    }
    m_liaisons.clear();
}

Neurone Reseau::getEntree(unsigned int i)
{
    if (i < m_nbNeuroneCouche[0])
    {
        return m_neurones[0][i].copie();
    }
    return 0;
}

Neurone Reseau::getSortie(unsigned int i)
{
    if (i < m_nbNeuroneCouche[m_nbNeuroneCouche.size()-1])
    {
        return m_neurones[m_nbNeuroneCouche.size()-1][i].copie();
    }
    return 0;
}

Neurone Reseau::getNeurone(unsigned int i, unsigned int j)
{
    if (i < m_nbNeuroneCouche.size())
    {
        if (j < m_nbNeuroneCouche[i])
        {
            return m_neurones[i][j].copie();
        }
    }
    return Neurone();
}

Liaison Reseau::getLiaison(unsigned int i, unsigned int j, unsigned int k)
{
    if (i < m_nbNeuroneCouche[m_nbNeuroneCouche.size()-1]-1)
    {
        return m_liaisons[i][j][k].copie();
    }
    return Liaison(0);
}

int Reseau::getNbEntrees()
{
    return m_nbNeuroneCouche[0];
}

int Reseau::getNbSorties()
{
    return m_nbNeuroneCouche[m_nbNeuroneCouche.size()-1];
}

int Reseau::getNbCouches()
{
    return m_nbNeuroneCouche.size();
}

int Reseau::getNbNeuronesCouches(unsigned int i)
{
    if (i < m_nbNeuroneCouche.size())
    {
        return m_nbNeuroneCouche[i];
    }
    return 0;
}

void Reseau::setEntrees(std::vector<bool> entrees)
{
    unsigned int i(0);
    if (m_nbNeuroneCouche[0] != entrees.size())
    {
        exit(EXIT_FAILURE);
    }
    for ( i = 0 ; i < m_nbNeuroneCouche[0] ; i++ )
    {
        m_neurones[0][i].setActive(entrees[i]);
        m_neurones[0][i].setActuel(true);
    }
}

void Reseau::setEntreesActuelles(bool actuelles)
{
    unsigned int i(0);

    for (i = 0 ; i < m_nbNeuroneCouche[0] ; i++)
    {
        m_neurones[0][i].setActuel(actuelles);
    }
}

void Reseau::setLiaisonPoids(unsigned int i, unsigned int j, unsigned int k, float poids)
{
    if (i < m_nbNeuroneCouche.size()-1)
    {
        if (j < m_nbNeuroneCouche[i] && k < m_nbNeuroneCouche[i+1])
        {
            m_liaisons[i][j][k].changerPoids(poids);
        }
    }
}

void Reseau::setNeuroneDelta(unsigned int i, unsigned int j, float delta)
{
    if (i < m_nbNeuroneCouche.size())
    {
        if (j < m_nbNeuroneCouche[i])
        {
            m_neurones[i][j].setDelta(delta);
        }
    }
}

void Reseau::setNeuroneDeltaActuel(unsigned int i, unsigned int j, bool deltaActuel)
{
    if (i < m_nbNeuroneCouche.size())
    {
        if (j < m_nbNeuroneCouche[i])
        {
            m_neurones[i][j].setDeltaActuel(deltaActuel);
        }
    }
}

vector<bool> Reseau::calculeSorties()
{
    unsigned int i(0), j(0);
    vector<bool> sorties;

    // On désactualise les neurones de la couche 1 à la couche de sortie
    for (i=1 ; i < m_nbNeuroneCouche.size() ; i++)
    {
        for (j = 0 ; j < m_nbNeuroneCouche[i] ; j++)
        {
            m_neurones[i][j].setActuel(false);
        }
    }
    // On demande le calcul des neurones de sortie
    for (i = 0 ; i < m_nbNeuroneCouche[m_nbNeuroneCouche.size()-1] ; i++)
    {
        // Fonction récursive
        caluleNeurone(m_nbNeuroneCouche.size()-1, i);
        // On ajoute l'activation de la sortie à la variable de retour
        sorties.push_back(m_neurones[m_nbNeuroneCouche.size()-1][i].getActive());
    }
    return sorties;
}

void Reseau::caluleNeurone(unsigned int i, unsigned int j)
{
    unsigned int k(0);
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
            for ( k = 0 ; k < m_nbNeuroneCouche[i-1] ; k++ )
            {
                caluleNeurone(i-1,k);
                somme += ((m_neurones[i-1][k].getActive())*2-1)*m_liaisons[i-1][k][j].getPoids();
            }
            // sigmoide actualise le neurone
            m_neurones[i][j].sigmoide(somme);
        }
    }
}

void Reseau::afficheLiaisons()
{
    unsigned int i(0), j(0), k(0);
    cout << "Liaisons :" << endl;
    for (i = 0 ; i < m_liaisons.size() ; i++)
    {
        cout << i << " : " << endl;
        for (j = 0 ; j < m_liaisons[i].size() ; j++)
        {
            for (k = 0 ; k < m_liaisons[i][j].size() ; k++)
            {
                cout << m_liaisons[i][j][k].getPoids() << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}
