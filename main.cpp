#include <QCoreApplication>
#include <iostream>
#include "grapheliste.h"
#include "graphematrice.h"

using namespace std;

//#define EX_INTRO
#define EX_PART1

GrapheListe* creerListeAdjacenteDuCours();

int main()
{

#ifdef EX_INTRO
    // Série 10 : Graphes (introduction)

    GrapheMatrice* gm = new GrapheMatrice(11);
    gm->ajouterArc('A', 'B', 2);
    gm->ajouterArc('D', 'E', 3);
    gm->ajouterArcOriente('C', 'D', 6);
    gm->afficher();

    cout << "degree 'A' : " << gm->getDegree('A') << endl;
    cout << "degree 'D' : " << gm->getDegree('D') << endl;
    cout << "degree max : " << gm->getDegreeMax() << endl;

    delete gm;
#endif
#ifdef EX_PART1
    GrapheListe* gl = creerListeAdjacenteDuCours();

    cout << "Liste de base : " << endl << endl,
    gl->afficher();

    //gl->DCFC();

    cout << endl << "Liste après parcours : " << endl << endl;

    //gl->parcoursProfondeurRecursif();
    //gl->parcoursProfondeurPile();
    gl->parcoursLargeurFile();

#endif
    return 0;
}


GrapheListe* creerListeAdjacenteDuCours(){
    GrapheListe *grapheListe = new GrapheListe(11);

    grapheListe->ajouterArc('A', 'B');
    grapheListe->ajouterArc('A', 'F');
    grapheListe->ajouterArc('A', 'G');
    grapheListe->ajouterArc('A', 'C');

    grapheListe->ajouterArc('B', 'A');

    grapheListe->ajouterArc('C', 'A');

    grapheListe->ajouterArc('D', 'E');
    grapheListe->ajouterArc('D', 'F');

    grapheListe->ajouterArc('E', 'G');
    grapheListe->ajouterArc('E', 'F');
    grapheListe->ajouterArc('E', 'D');

    grapheListe->ajouterArc('F', 'A');
    grapheListe->ajouterArc('F', 'D');

    grapheListe->ajouterArc('G', 'A');
    grapheListe->ajouterArc('G', 'E');

    grapheListe->ajouterArc('I','J');
    grapheListe->ajouterArc('I','K');

    grapheListe->ajouterArc('J','K');
    grapheListe->ajouterArc('J','I');

    grapheListe->ajouterArc('K','I');
    grapheListe->ajouterArc('K','J');

    return grapheListe;
}
