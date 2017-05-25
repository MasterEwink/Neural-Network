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

#include "common.h"
#include "reseau.h"
#include "apprentissage.h"
#include "saveload.h"

using namespace std;

int main()
{
    srand(time(NULL));

    vector<unsigned int> nbNeuroneCouche;
    vector< vector<bool> > sortiesSouhaitees;
    vector< vector<bool> > sortiesObtenues;
    vector< bool > listeBool;

    nbNeuroneCouche.push_back(NB_ENTREES);
    nbNeuroneCouche.push_back(5);
    nbNeuroneCouche.push_back(NB_SORTIES);
/*
    // Création d'un nouveau réseau
    Reseau res_test(nbNeuroneCouche);
*/

    // Chargement d'un réseau existant
    Reseau res_test = loadNetwork("reseaux/reseau.txt");

/*
    // Génération aléatoire de données
    for ( unsigned int j = 0 ; j < NB_TESTS ; j++ )
    {
        for ( unsigned int i = 0 ; i < NB_SORTIES ; i++)
        {
            if (rand()%10 < 5)
            {
                listeBool.push_back(true);
            }
            else
            {
                listeBool.push_back(false);
            }
        }
        sortiesSouhaitees.push_back(listeBool);
        listeBool.clear();
    }
*/
    // Chargement de données définies
    sortiesSouhaitees = loadImg("images/imageOrig.txt");

    // Apprentissage
    apprentissageAleatoire(sortiesSouhaitees, res_test, 8000, 1);

    // Affichage et création des données décompressées
    for ( unsigned int j = 0 ; j < NB_TESTS ; j++ )
    {
        res_test.setEntrees(binariseNb(j,res_test.getNbEntrees()));
        res_test.calculeSorties();
        for ( unsigned int i = 0 ; i < sortiesSouhaitees[j].size() ; i++)
        {
            cout << sortiesSouhaitees[j][i] << " ";
            listeBool.push_back(res_test.getNeurone(nbNeuroneCouche.size()-1,i).getActive());
        }
        sortiesObtenues.push_back(listeBool);
        listeBool.clear();
        cout << endl;
        res_test.afficheNeurones();
        cout << calculeErreur(res_test, sortiesSouhaitees[j]) << endl << endl << endl;
    }
    res_test.afficheLiaisons();
/*
    // Enregistrement des données originelles
    switch(saveImg(sortiesSouhaitees, "images/imageOrig2.txt"))
    {
    case F_NO_ERROR:
        break;
    case F_ERR_NOT_OPEN:
        cout << "Impossible d'ouvir le fichier" << endl;
        break;
    default:
        cout << "Erreur inconnue" << endl;
        break;
    }
*/

    // Enregistrement des données décompressées
    switch(saveImg(sortiesObtenues, "images/imageRes.txt"))
    {
    case F_NO_ERROR:
        break;
    case F_ERR_NOT_OPEN:
        cout << "Impossible d'ouvir le fichier" << endl;
        break;
    default:
        cout << "Erreur inconnue" << endl;
        break;
    }

    // Enregistrement du reseau
    saveNetwork(res_test, "reseaux/reseau.txt");

    return 0;
}
