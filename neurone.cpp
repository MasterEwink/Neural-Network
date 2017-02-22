/*
    Neural Network
    neurone.cpp
        Créé : 10/09/16
        Fonctions relatives aux neurones
*/

#include <math.h>
#include <ctime>
#include <cstdlib>

#include "neurone.h"
#include "liaison.h"

Neurone::Neurone()
{
    m_active = false;
    m_seuil = 0.5;
    m_actuel = false;
    m_valeur = 0.;
}

Neurone::Neurone(float seuil)
{
    m_active = false;
    m_seuil = seuil;
    m_actuel = false;
    m_valeur = 0.;
}

Neurone::Neurone(Neurone const& autre)
{
    m_active = false;
    m_seuil = autre.m_seuil;
    m_actuel = false;
    m_valeur = autre.m_valeur;
}

bool Neurone::getActive()
{
    return m_active;
}

float Neurone::getSeuil()
{
    return m_seuil;
}

bool Neurone::getActuel()
{
    return m_actuel;
}

float Neurone::getValeur()
{
    return m_valeur;
}

float Neurone::sigmoide(float x)
{
    m_valeur = tanh(x);
    m_actuel = true;
    m_active = m_valeur >= m_seuil;
    return m_valeur;
}

void Neurone::setActuel(bool actuel)
{
    m_actuel = actuel;
}

void Neurone::setActive(bool active)
{
    m_active = active;
    if (active)
    {
        m_valeur = 1.;
    }
    else
    {
        m_valeur = -1.;
    }
}
