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

#include "reseau.h"
#include "apprentissage.h"

#define NB_ENTREES 30
#define INPUT_VECTORS_COUNT 6

using namespace std;

vector<bool> buildInput()
{
    vector<bool> entrees;
    for (int i = 0 ; i < NB_ENTREES ; i++)
    {
        if (rand()%10 < 5)
        {
            entrees.push_back(true);
        }
        else
        {
            entrees.push_back(false);
        }
    }
    return entrees;
}

void showResults(vector<bool> expected, vector<bool> got)
{
    cout << "Expected :" << endl;
    for (const bool &value : expected)
    {
        cout << value << " ";
    }
    cout << endl;

    cout << "Got :" << endl;
    for (const bool &value : got)
    {
        cout << value << " ";
    }
    cout << endl;

    cout << "Accuracy : ";
    unsigned int correct_values_count = 0;
    for (unsigned int i = 0; i < expected.size(); ++i)
    {
        if (got[i] == expected[i])
        {
            ++correct_values_count;
        }
    }
    cout << correct_values_count << "/" << expected.size() << endl;
}

int main()
{
    srand(time(NULL));
    unsigned int i(0);

    vector<unsigned int> nbNeuroneCouche;

    nbNeuroneCouche.clear();
    nbNeuroneCouche.push_back(NB_ENTREES);
    nbNeuroneCouche.push_back(5);
    nbNeuroneCouche.push_back(NB_ENTREES);

    Reseau res_test(nbNeuroneCouche);

    vector< vector<bool> > entrees;

    for (i = 0; i < INPUT_VECTORS_COUNT; ++i)
    {
        entrees.push_back(buildInput());
    }

    cout << "Learning..." << endl;
    for (i = 0 ; i < 700 ; i++)
    {
        vector<bool> input = entrees[i % INPUT_VECTORS_COUNT];
        res_test.setEntrees(input);
        res_test.calculeSorties();
        apprentissage(res_test);
    }

    for (i = 0; i < INPUT_VECTORS_COUNT; ++i)
    {
        vector<bool> input = entrees[i];
        res_test.setEntrees(input);
        vector<bool> output = res_test.calculeSorties();
        apprentissage(res_test);
        cout << "Vecteur d'entrainement #" << i << endl;
        showResults(input, output);
        //cin.get();
    }

    cout << "Et maintenant avec un vecteur inconnu" << endl;
    vector<bool> input = buildInput();
    res_test.setEntrees(input);
    vector<bool> output = res_test.calculeSorties();
    showResults(input, output);


    return 0;
}
