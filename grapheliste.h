#ifndef GRAPHELISTE_H
#define GRAPHELISTE_H

#include <list>
#include <stack>
#include <queue>

struct Sommet {
  char indice;
  bool visite;
  bool stack;
  int  marquage;
  std::list<struct Link*>* listDeLien;
};

struct Link {
    char indice;
    int ponderation;
};

class GrapheListe
{
public:
    GrapheListe(int m_nombreSommet);
    ~GrapheListe();

    void display();
    void ajouterArc(char sommetDepart, char sommetArrive, int ponderation = 1);
    void ajouterArrete(char sommet1, char sommet2, int ponderation = 1);
    struct Sommet* getSommetFromChar(char indice);


    void parcoursProfondeurRecursif(bool sensAlphabetique = true);
    void VSPR(struct Sommet* sommet); // Visite à partir du Sommet en Profondeur Récursif.

    void parcoursProfondeurPile(bool sensAlphabetique = true);
    void VSPNR(struct Sommet* sommet); // Visiter le Sommet en Profondeur Non Récursif.

    void parcoursLargeurFile(bool sensAlphabetique = false);
    void VSLNR(struct Sommet* sommet); // Visiter le Sommet en Largeur Non Récursif.

    // Détermination des composantes fortement connexes d'un graphe orienté.
    void DCFC();
    int  visiterSommetDCFC(struct Sommet* sommet);
private:
    std::list<struct Sommet*>* m_listeDeSommet;
    int m_nombreSommet;
    int m_nombreCourant;
    std::stack<struct Sommet*> m_pile;
    std::queue<struct Sommet*> m_file;
};

#endif // GRAPHELISTE_H
