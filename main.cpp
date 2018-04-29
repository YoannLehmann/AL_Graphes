#include <QCoreApplication>
#include <iostream>
#include "grapheliste.h"
#include "graphematrice.h"

using namespace std;

//#define EX_INTRO
#define EX_PART1

GrapheListe* creerListeAdjacenteDuCours();
GrapheListe* creerListeAdjacenteARPM();

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

    cout << "Liste de base : " << endl << endl;
    gl->afficher();

    //gl->DCFC();

    cout << endl << "Liste après parcours : " << endl << endl;

    //gl->parcoursProfondeurRecursif();
    //gl->parcoursProfondeurPile();
    //gl->parcoursLargeurFile();
    //gl->parcoursGeneralise(PARCOURS_LARGEUR_FILE);

    GrapheListe* gl2 = creerListeAdjacenteARPM();
    cout << "Liste de base ARPM" << endl << endl;

    gl2->afficher();

    cout << endl << "Liste après parcours : " << endl << endl;

    //gl2->parcoursARPM();
    gl2->parcoursACPC();

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

// Création de la liste adjacente avec arcs pondérés (selon l'exemple ARMP p.24)
GrapheListe* creerListeAdjacenteARPM() {
    GrapheListe *grapheListe = new GrapheListe(11);

    grapheListe->ajouterArc('A', 'B', 1);
    grapheListe->ajouterArc('A', 'F', 4);
    grapheListe->ajouterArc('A', 'G', 2);
    grapheListe->ajouterArc('A', 'C', 2);

    grapheListe->ajouterArc('B', 'A', 1);

    grapheListe->ajouterArc('C', 'J', 1);
    grapheListe->ajouterArc('C', 'A', 2);
    grapheListe->ajouterArc('C', 'G', 1);
    grapheListe->ajouterArc('C', 'H', 3);

    grapheListe->ajouterArc('D', 'E', 1);
    grapheListe->ajouterArc('D', 'F', 1);

    grapheListe->ajouterArc('E', 'G', 1);
    grapheListe->ajouterArc('E', 'F', 3);
    grapheListe->ajouterArc('E', 'D', 1);

    grapheListe->ajouterArc('F', 'A', 4);
    grapheListe->ajouterArc('F', 'D', 1);
    grapheListe->ajouterArc('F', 'E', 1);

    grapheListe->ajouterArc('G', 'C', 1);
    grapheListe->ajouterArc('G', 'A', 2);
    grapheListe->ajouterArc('G', 'E', 1);

    grapheListe->ajouterArc('H', 'K', 1);
    grapheListe->ajouterArc('H', 'C', 3);

    grapheListe->ajouterArc('I','J', 3);
    grapheListe->ajouterArc('I','K', 1);

    grapheListe->ajouterArc('J','K', 1);
    grapheListe->ajouterArc('J','I', 3);
    grapheListe->ajouterArc('J','C', 1);

    grapheListe->ajouterArc('K','I', 1);
    grapheListe->ajouterArc('K','J', 1);
    grapheListe->ajouterArc('K','H', 1);

    return grapheListe;
}
