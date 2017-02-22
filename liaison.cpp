/*
    Neural Network
    liaison.cpp
        Créé : 10/09/16
        Fonctions relatives aux liaisons
*/

#include "liaison.h"

using namespace std;

Liaison::Liaison()
{
    m_poids=0;
}

Liaison::Liaison(float poids)
{
    m_poids = poids;
}

Liaison::Liaison(Liaison const& other)
{
    m_poids = other.m_poids;
}

float Liaison::getPoids()
{
    return m_poids;
}

float Liaison::getGradientPrec()
{
    return m_gradientPrec;
}

void Liaison::changerPoids(float nouveau)
{
    m_poids = nouveau;
}
