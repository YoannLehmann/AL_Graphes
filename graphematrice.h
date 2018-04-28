#ifndef GRAPHEMATRICE_H
#define GRAPHEMATRICE_H


class GrapheMatrice
{
public:
    GrapheMatrice(int nombreSommet);
    ~GrapheMatrice();

    int getDegree(char sommet);
    int getDegreeMax();
    int ajouterArc(char sommet1, char sommet2, int ponderation);
    int ajouterArcOriente(char sommet1, char sommet2, int ponderation);
    bool estConnexe();
    void afficher();

private:

    int** graphe;
    int   tailleGraphe;
};

#endif // GRAPHEMATRICE_H
