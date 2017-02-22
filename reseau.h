/*
    Neural Network
    reseau.h
        Créé : 09/09/16
        Délaration de la classe réseau
*/

#ifndef DEF_RESEAU

#define DEF_RESEAU

#define PRECISION 100000

#include <vector>
#include <string>

#include "neurone.h"
#include "liaison.h"

class Reseau
{
    public :

        //Reseau(); //1
        Reseau(std::vector<unsigned int> nbNeuroneCouche);
        ~Reseau();

        Neurone getEntree(unsigned int i);
        Neurone getSortie(unsigned int i);
        Liaison getLiaison(unsigned int i, unsigned int j, unsigned int k);
        unsigned int getNbEntrees();
        unsigned int getNbSorties();
        unsigned int getNbCouches();
        unsigned int getNbNeuronesCouches(unsigned int i);
        void setEntrees(std::vector<bool> entrees);     // Retourne 1 si les entrees ont été initialisées
        void setEntreesActuelles(bool actuelles);

        std::vector<bool> calculeSorties();
        void caluleNeurone(unsigned int i, unsigned int j);

        void afficheNeurones();
        void afficheLiaisons();

    private :

        std::vector< unsigned int > m_nbNeuroneCouche;    // liste
        std::vector< std::vector< Neurone > > m_neurones;           // tableau
        std::vector< std::vector< std::vector< Liaison > > > m_liaisons;      // tableau 3D
};

#endif // DEF_RESEAU
