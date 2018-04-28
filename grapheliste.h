#ifndef GRAPHELISTE_H
#define GRAPHELISTE_H

#include <list>
#include <stack>
#include <queue>

struct Sommet {
  char indice;
  bool visite;
  bool empile;
  int  marquage;
  std::list<struct Lien*>* listeDeLien;
};
typedef struct Sommet Sommet;

struct Lien {
    char  indice;
    int   ponderation;
};
typedef struct Lien Lien;

class GrapheListe
{
public:
    GrapheListe(int _nombreSommet);
    ~GrapheListe();

    void afficher();
    void ajouterArc(char _sommetDepart, char _sommetArrive, int _ponderation = 1);
    void ajouterArrete(char _sommet1, char _sommet2, int _ponderation = 1);

    Sommet* getSommetFromChar(char indice);
    void afficherPile();

    void parcoursProfondeurRecursif(bool _sensAlphabetique = true);
    void VSPR(Sommet* _sommet); // Visite à partir du Sommet en Profondeur Récursif.

    void parcoursProfondeurPile(bool sensAlphabetique = true);
    void VSPNR(Sommet* _sommet); // Visiter le Sommet en Profondeur Non Récursif.

    void parcoursLargeurFile(bool sensAlphabetique = false);
    void VSLNR(Sommet* _sommet); // Visiter le Sommet en Largeur Non Récursif.


    void DCFC(); // Détermination des composantes fortement connexes d'un graphe orienté.
    int  visiterSommetDCFC(Sommet* sommet);
private:
    std::list<Sommet*>* m_listeDeSommet;
    std::stack<Sommet*> m_pile;
    std::queue<Sommet*> m_file;
    int m_nombreSommet;
    int m_nombreCourant;
};

#endif // GRAPHELISTE_H
