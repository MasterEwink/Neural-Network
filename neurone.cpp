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
    m_delta = 0;
    m_deltaActuel = false;
}

Neurone::Neurone(float seuil)
{
    m_active = false;
    m_seuil = seuil;
    m_actuel = false;
    m_valeur = 0.;
    m_delta = 0;
    m_deltaActuel = false;
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

float Neurone::getDelta()
{
    return m_delta;
}

bool Neurone::getDeltaActuel()
{
    return m_deltaActuel;
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

void Neurone::setDelta(float delta)
{
    m_delta = delta;
}

void Neurone::setDeltaActuel(bool deltaActuel)
{
    m_deltaActuel = deltaActuel;
}
