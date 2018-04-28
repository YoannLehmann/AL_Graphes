#include "grapheliste.h"
#include <iostream>

using namespace std;

GrapheListe::GrapheListe(int _nombreSommet)
{
    this->m_nombreSommet = _nombreSommet;

    this->m_listeDeSommet = new std::list<Sommet*>();

    for(int i = 0; i < this->m_nombreSommet; i++){
        struct Sommet* sommet = new Sommet();
        sommet->empile = false;
        sommet->visite = false;
        sommet->listeDeLien = new std::list<Lien*>();
        sommet->indice = 'A' + static_cast<char>(i);
        sommet->marquage = 0;

        this->m_listeDeSommet->push_back(sommet);
    }
}

GrapheListe::~GrapheListe()
{
    for (std::list<Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        for(std::list<Lien*>::iterator j = (*i)->listeDeLien->begin(); j != (*i)->listeDeLien->end(); j++){
            delete (*j);
            (*j) = nullptr;
        }

        delete (*i);
        (*i) = nullptr;
    }
    delete this->m_listeDeSommet;
}

void GrapheListe::afficher()
{

    for (std::list<Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        // Entête.
        std::cout << "V["
        << ((*i)->visite ? "X" : " ")
        << "]"
        << "S["
        << ((*i)->empile ? "X" : " ")
        << "]_";
        std::cout << "'" << (*i)->indice << "':";


        for(std::list<Lien*>::iterator j = (*i)->listeDeLien->begin(); j != (*i)->listeDeLien->end(); j++){
            std::cout << "--" << (*j)->ponderation << "-->" << (*j)->indice;
        }

        std::cout << std::endl;
    }
}

void GrapheListe::ajouterArc(char _sommetDepart, char _sommetArrive, int _ponderation)
{
    std::list<Sommet*>::iterator it = this->m_listeDeSommet->begin();

    std::advance(it, static_cast<int>(_sommetDepart - 'A')); // Avance l'itérateur jusqu'au bon élément.

    Lien* lien = new Lien();
    lien->indice = _sommetArrive;
    lien->ponderation = _ponderation;

    (*it)->listeDeLien->push_back(lien);
}

void GrapheListe::ajouterArrete(char _sommet1, char _sommet2, int _ponderation)
{
    this->ajouterArc(_sommet1, _sommet2, _ponderation);
    this->ajouterArc(_sommet2, _sommet1, _ponderation);
}

struct Sommet* GrapheListe::getSommetFromChar(char indice)
{
    for (std::list<Sommet*>::iterator j = this->m_listeDeSommet->begin(); j != this->m_listeDeSommet->end(); j++) {

        if((*j)->indice == indice){
            return (*j);
        }
    }

    return nullptr;
}

void GrapheListe::afficherPile()
{
    cout << "Etat de la pile : " << endl;

    if(m_pile.size() > 0){

        std::stack<struct Sommet*> copiePile;

        // Dépilage et affichage de tous les éléments de la pile.
        while(m_pile.size() > 0){
            struct Sommet* sommetPile = m_pile.top();
            m_pile.pop();
            cout << "[" << sommetPile->indice << "]" << endl;
            copiePile.push(sommetPile);
        }

        // Réempilage des éléments dépilés.
        while(copiePile.size() > 0){
            struct Sommet* sommetPile = copiePile.top();
            copiePile.pop();
            m_pile.push(sommetPile);
        }
    } else {
        cout << "Pile vide" << endl;
    }

    cout << endl;
}

void GrapheListe::parcoursProfondeurRecursif(bool _sensAlphabetique)
{

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        VSPR((*i));
    }

    std::cout << std::endl;
}

void GrapheListe::VSPR(struct Sommet *_sommet)
{
    if(_sommet->visite == false){
        _sommet->visite = true;
        std::cout << _sommet->indice;

        if(_sommet->listeDeLien->size() > 0)
            VSPR(getSommetFromChar(_sommet->listeDeLien->front()->indice));
    }
}

void GrapheListe::parcoursProfondeurPile(bool sensAlphabetique)
{
    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        this->VSPNR((*i));
    }
    cout << endl;
}

void GrapheListe::VSPNR(Sommet* _sommet)
{
    if(_sommet->visite == false){

        _sommet->empile = true;
        m_pile.push(_sommet);

        while(m_pile.empty() == false){

            struct Sommet* sommetPile = m_pile.top(); // Accède au dernier élément.
            m_pile.pop();                             // Dépile l'élément de la pile.
            sommetPile->visite = true;                // Indique que l'élément dépilé est visité.

            // Affichage de l'indice.
            cout << "Sommet : " << sommetPile->indice << " visité." << endl;

            // Affichage de l'état de la pile.
            afficherPile();

            // Parcours de tous les voisins du sommet.
            for(std::list<struct Lien*>::iterator j = sommetPile->listeDeLien->begin(); j != sommetPile->listeDeLien->end(); j++){

                // Récupération du sommet voisin.
                struct Sommet* sommetLien = getSommetFromChar((*j)->indice);
                // Si le voisin n'est ni empilé ni visité, on l'empile et le marque comme empilé.
                if(sommetLien->empile == false && sommetLien->visite == false){
                    sommetLien->empile = true;
                    m_pile.push(sommetLien);
                }
            }
        }

    }
}

void GrapheListe::parcoursLargeurFile(bool sensAlphabetique)
{
    std::queue<struct Sommet*> queue;

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        // --> VSLNR
        if((*i)->visite == false){
            (*i)->empile = true;
            queue.push(*i);

            while(queue.size() > 0){
                struct Sommet* sommet = queue.front();
                queue.pop();
                sommet->visite = true;

                // Affichage de l'état de la file.
                std::cout << "Sommet : " << sommet->indice << " visité." << std::endl;
                std::cout << "Etat de la file : " << std::endl;
                if(queue.size() > 0){
                    std::queue<struct Sommet*> copieQueue;
                    while(queue.size() > 0){
                        struct Sommet* sommet = queue.front();
                        queue.pop();
                        std::cout << "[" << sommet->indice << "]" << std::endl;
                        copieQueue.push(sommet);
                    }
                    while(copieQueue.size() > 0){
                        struct Sommet* sommet = copieQueue.front();
                        copieQueue.pop();
                        queue.push(sommet);
                    }
                } else {
                    std::cout << "File vide" << std::endl;
                }



                for(std::list<struct Lien*>::iterator j = sommet->listeDeLien->begin(); j != sommet->listeDeLien->end(); j++){
                    struct Sommet* sommetLink = getSommetFromChar((*j)->indice);

                    if(sommetLink->empile == false && sommetLink->visite == false){
                        sommetLink->empile = true;
                        queue.push(sommetLink);
                    }
                }
            }
        }
    }
}

void GrapheListe::VSLNR(Sommet *_sommet)
{

}

void GrapheListe::DCFC()
{
    this->m_nombreCourant = 0;

    for(std::list<struct Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++){
        if((*i)->visite == false) {
            this->visiterSommetDCFC((*i));
        }
    }
}

int GrapheListe::visiterSommetDCFC(Sommet *sommet)
{
    this->m_nombreCourant++;
    int minimum = m_nombreCourant;
    sommet->visite = true;
    sommet->marquage = m_nombreCourant;
    this->m_pile.push(sommet);

    for(std::list<struct Lien*>::iterator j = sommet->listeDeLien->begin(); j != sommet->listeDeLien->end(); j++) {
        struct Sommet* sommetLink = getSommetFromChar((*j)->indice);
        int marquage = 0;

        if(sommetLink->visite == false){
            marquage = this->visiterSommetDCFC(sommetLink);
        } else {
            marquage = sommet->marquage;
        }

        minimum = std::min(minimum, marquage);
    }

    if(minimum == sommet->marquage) {
        struct Sommet* sommetADepiler = m_pile.top();
        do {
            sommetADepiler = m_pile.top();
            std::cout << sommetADepiler->indice;
        } while(this->m_pile.size() > 0 || sommetADepiler->indice != sommet->indice);

        std::cout << std::endl;
    }

    return minimum;
}
