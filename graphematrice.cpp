#include "graphematrice.h"
#include <iostream>

using namespace std;

GrapheMatrice::GrapheMatrice(int nombreSommet)
{
    // Initialisation des attributs.
    this->tailleGraphe = nombreSommet;
    this->graphe = new int*[this->tailleGraphe];

    // Initialisation de la matrice (tailleGraphe x tailleGraphe) avec des zéros.
    for(int i = 0; i < this->tailleGraphe; ++i){
        this->graphe[i] = new int[this->tailleGraphe];
        for(int j = 0; j < this->tailleGraphe; j++){
            this->graphe[i][j] = 0;
        }
    }
}

GrapheMatrice::~GrapheMatrice()
{
    for(int i = 0; i < this->tailleGraphe; i++){
        delete this->graphe[i];
    }
    delete this->graphe;
}

// Nombre d'arc qui arrive à un sommet.
int GrapheMatrice::getDegree(char sommet)
{
    int degree = 0;

    for(int i = 0; i < this->tailleGraphe; i++){
        if(this->graphe[i][(int)(sommet-'A')] != 0){
            degree++;
        }
    }

    return degree;
}

int GrapheMatrice::getDegreeMax()
{
    int  degreeMax = 0;

    for(int i = 0; i < this->tailleGraphe; i++){
        int degreeActuel = this->getDegree((char)(65+i));

        if(degreeActuel > degreeMax){
            degreeMax = degreeActuel;
        }
    }

    return degreeMax;
}

int GrapheMatrice::ajouterArc(char sommet1, char sommet2, int ponderation)
{
    ajouterArcOriente(sommet1, sommet2, ponderation);
    ajouterArcOriente(sommet2, sommet1, ponderation);
}

int GrapheMatrice::ajouterArcOriente(char sommet1, char sommet2, int ponderation)
{
    if((int)(sommet1 - 'A') > tailleGraphe){
        cout << "le sommet 1 est incorrect" << endl;
    } else if((int)(sommet2 - 'A') > tailleGraphe){
        cout << "le sommet 2 est incorrect" << endl;
    } else if(sommet1 == sommet2){
        cout << "le sommet 1 doit être différent du sommet 2" << endl;
    } else {
        graphe[(int)(sommet1 - 'A')][(int)(sommet2-'A')] = ponderation;
    }
}

/**
 * @brief GrapheMatrice::estConnexe
 * @todo  Dev. la méthode.
 * @return
 */
bool GrapheMatrice::estConnexe()
{

}

void GrapheMatrice::afficher()
{
    //
    cout << "  ";
    for(int i = 0; i < tailleGraphe; i++){
        cout << " " << (char)(i+65) << " ";
    }
    cout << endl;

    for(int i = 0; i < tailleGraphe; i++){
        cout << (char)(i+65) << " ";
        for(int j = 0; j < tailleGraphe; j++){
            cout << "[" << graphe[i][j] << "]";
        }
        cout << endl;
    }
}
