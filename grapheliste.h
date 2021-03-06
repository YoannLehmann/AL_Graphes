#ifndef GRAPHELISTE_H
#define GRAPHELISTE_H

#include <list>
#include <stack>
#include <queue>

struct Sommet {
  char indice;
  bool visite;
  bool rencontre;
  int  marquage;
  int  priorite;
  std::list<struct Lien*>* listeDeLien;
};
typedef struct Sommet Sommet;

struct Lien {
    char  indice;
    int   ponderation;
};
typedef struct Lien Lien;

struct CompareSommet {
    bool operator()(const Sommet* lhs, const Sommet* rhs) const
    {
        return lhs->priorite > rhs->priorite;
    }
};
typedef struct CompareSommet CompareSommet;

enum TypeParcours {
    PARCOURS_PROFONDEUR_PILE,
    PARCOURS_LARGEUR_FILE
};

class GrapheListe
{
public:
    GrapheListe(int _nombreSommet);
    ~GrapheListe();

    void afficher();
    void ajouterArc(char _sommetDepart, char _sommetArrive, int _ponderation = 1);
    void ajouterArrete(char _sommet1, char _sommet2, int _ponderation = 1);

    void reinitialiserFlags();
    void afficherPile();
    void afficherFile();
    void afficherFilePriorite();
    Sommet* obtenirSommetDepuisIndice(char _indice);
    void traiterSommet(Sommet* _sommet);
    void calculerPriorite(Sommet* _sommet, TypeParcours _typeParcours);

    void parcoursProfondeurRecursif();
    void VSPR(Sommet* _sommet); // Visite à partir du Sommet en Profondeur Récursif.

    void parcoursProfondeurPile();
    void VSPNR(Sommet* _sommet); // Visiter le Sommet en Profondeur Non Récursif.

    void parcoursLargeurFile();
    void VSLNR(Sommet* _sommet); // Visiter le Sommet en Largeur Non Récursif.

    void parcoursGeneralise(TypeParcours _typeParcours);
    void VSGNR(Sommet* _sommet, TypeParcours _typeParcours); // Visiter le Sommet en Généralisé Non Récursif.

    void parcoursARPM(); // Algorithme de Prim.
    void VSARMP(Sommet* _sommet);   // Visiter le Sommet avec ARMP.

    void parcoursACPC(); // Algorithme de Dijkstra
    void VSACPC(Sommet* _sommet);   // Visiter le Sommet avec ACPC.

    void parcoursDCFC(); // Parcours pour déterminer les composantes fortement connexes.
    int  VSDCFC(Sommet* _sommet);    // Visiter le Sommet avec DCFC.


private:
    std::list<Sommet*>* m_listeDeSommet;
    std::stack<Sommet*> m_pile;
    std::queue<Sommet*> m_file;

    std::priority_queue<Sommet*, std::vector<Sommet*>, CompareSommet> m_filePriorite;
    int m_nombreSommet;
    int m_valeurPriorite;   // Utilisé pour l'algorithme de parcours généralisé.
    int m_numero;           // Utilisé pour l'algorithme DCFC.
};

#endif // GRAPHELISTE_H
