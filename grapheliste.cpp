#include "grapheliste.h"
#include <iostream>
#include <stack>
#include <queue>

GrapheListe::GrapheListe(int nombreSommet)
{
    this->m_nombreSommet = nombreSommet;

    this->m_listeDeSommet = new std::list<struct Sommet*>();

    for(int i = 0; i < this->m_nombreSommet; i++){
        struct Sommet* sommet = new struct Sommet();
        sommet->stack = false;
        sommet->visite = false;
        sommet->listDeLien = new std::list<struct Link*>();
        sommet->indice = 'A' + static_cast<char>(i);
        sommet->marquage = 0;

        this->m_listeDeSommet->push_back(sommet);
    }
}

GrapheListe::~GrapheListe()
{
    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        for(std::list<struct Link*>::iterator j = (*i)->listDeLien->begin(); j != (*i)->listDeLien->end(); j++){
            delete (*j);
            (*j) = nullptr;
        }

        delete (*i);
        (*i) = nullptr;
    }
    delete this->m_listeDeSommet;
}

void GrapheListe::display()
{

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        std::cout << "V["
        << ((*i)->visite ? "X" : " ")
        << "]"
        << "S["
        << ((*i)->stack ? "X" : " ")
        << "]_";
        std::cout << "'" << (*i)->indice << "':";


        for(std::list<struct Link*>::iterator j = (*i)->listDeLien->begin(); j != (*i)->listDeLien->end(); j++){
            std::cout << "--" << (*j)->ponderation << "-->" << (*j)->indice;
        }


        std::cout << std::endl;
    }
}

void GrapheListe::ajouterArc(char sommetDepart, char sommetArrive, int ponderation)
{
    std::list<struct Sommet*>::iterator it = this->m_listeDeSommet->begin();

    std::advance(it, static_cast<int>(sommetDepart - 'A')); // Avance l'itérateur jusqu'au bon élément.

    struct Link* link = new struct Link();
    link->indice = sommetArrive;
    link->ponderation = ponderation;

    (*it)->listDeLien->push_back(link);
}

void GrapheListe::ajouterArrete(char sommet1, char sommet2, int ponderation)
{
    this->ajouterArc(sommet1, sommet2, ponderation);
    this->ajouterArc(sommet2, sommet1, ponderation);
}

struct Sommet* GrapheListe::getSommetFromChar(char indice)
{
    for (std::list<struct Sommet*>::iterator j = this->m_listeDeSommet->begin(); j != this->m_listeDeSommet->end(); j++) {

        if((*j)->indice == indice){
            return (*j);
        }
    }

    return nullptr;
}

void GrapheListe::parcoursProfondeurRecursif(bool sensAlphabetique)
{

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        VSPR((*i));
    }

    std::cout << std::endl;
}

void GrapheListe::VSPR(struct Sommet *sommet)
{
    if(sommet->visite == false){
        sommet->visite = true;
        std::cout << sommet->indice;

        if(sommet->listDeLien->size() > 0)
            VSPR(getSommetFromChar(sommet->listDeLien->front()->indice));
    }
}

void GrapheListe::parcoursProfondeurPile(bool sensAlphabetique)
{
    std::stack<struct Sommet*> stack;

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        // --> VSPNR
        if((*i)->visite == false){

            (*i)->stack = true;
            stack.push((*i));

            while(stack.empty() == false){
                struct Sommet* sommet = stack.top(); // Accède au dernier élément.
                stack.pop(); // Dépile l'élément de la pile.
                sommet->visite = true;

                // Affichage de l'indice.
                std::cout << "Sommet : " << sommet->indice << " visité." << std::endl;



                // Affichage de l'état de la pile.
                std::cout << "Etat de la pile : " << std::endl;
                if(stack.size() > 0){
                    std::stack<struct Sommet*> copieStack;
                    while(stack.size() > 0){
                        struct Sommet* sommet = stack.top();
                        stack.pop();
                        std::cout << "[" << sommet->indice << "]" << std::endl;
                        copieStack.push(sommet);
                    }
                    while(copieStack.size() > 0){
                        struct Sommet* sommet = copieStack.top();
                        copieStack.pop();
                        stack.push(sommet);
                    }
                } else {
                    std::cout << "Pile vide" << std::endl;
                }

                std::cout << std::endl;

                for(std::list<struct Link*>::iterator j = sommet->listDeLien->begin(); j != sommet->listDeLien->end(); j++){

                    struct Sommet* sommetDuLien = getSommetFromChar((*j)->indice);
                    if(sommetDuLien->stack == false && sommetDuLien->visite == false){
                        sommetDuLien->stack = true;
                        stack.push(sommetDuLien);
                    }
                }
            }

        }

    }

    std::cout << std::endl;

}

void GrapheListe::VSPNR(Sommet *sommet)
{

}

void GrapheListe::parcoursLargeurFile(bool sensAlphabetique)
{
    std::queue<struct Sommet*> queue;

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {

        // --> VSLNR
        if((*i)->visite == false){
            (*i)->stack = true;
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



                for(std::list<struct Link*>::iterator j = sommet->listDeLien->begin(); j != sommet->listDeLien->end(); j++){
                    struct Sommet* sommetLink = getSommetFromChar((*j)->indice);

                    if(sommetLink->stack == false && sommetLink->visite == false){
                        sommetLink->stack = true;
                        queue.push(sommetLink);
                    }
                }
            }
        }
    }
}

void GrapheListe::VSLNR(Sommet *sommet)
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

    for(std::list<struct Link*>::iterator j = sommet->listDeLien->begin(); j != sommet->listDeLien->end(); j++) {
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
