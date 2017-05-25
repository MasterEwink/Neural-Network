/*
    Neural Network
    neurone.h
        Créé : 10/09/16
        Déclaration de la classe Neurone
*/

#ifndef DEF_NEURONES

#define DEF_NEURONES

#include <vector>

class Liaison;

class Neurone
{
    public:

        Neurone();
        Neurone(float seuil);

        bool getActive();
        float getSeuil();
        float getValeur();
        bool getActuel();
        float getDelta();           // apprentissage
        bool getDeltaActuel();      // apprentissage

        float sigmoide(float x);        // Calcule f(x), avec f une sigmoide, et actualise les attributs
        void setActuel(bool actuel);
        void setActive(bool active);
        void setDelta(float delta);             // apprentissage
        void setDeltaActuel(bool deltaActuel);  // apprentissage

    private:

        bool m_active;                      // 1 si le neurone a été activé lors de la dernière exécution
        float m_seuil;                      // Seuil d'activation du neurone
        float m_valeur;
        bool m_actuel;                      // 1 si le neurone a été actualisé à la dernière exécution
        float m_delta;        // apprentissage
        bool m_deltaActuel;   // apprentissage
};

#endif // DEF_NEURONES
