#include "grapheliste.h"
#include <iostream>

using namespace std;

GrapheListe::GrapheListe(int _nombreSommet)
{
    this->m_nombreSommet = _nombreSommet;
    this->m_valeurPriorite = 0;
    this->m_listeDeSommet = new std::list<Sommet*>();


    for(int i = 0; i < this->m_nombreSommet; i++){
        struct Sommet* sommet = new Sommet();
        sommet->rencontre = false;
        sommet->visite = false;
        sommet->listeDeLien = new std::list<Lien*>();
        sommet->indice = 'A' + static_cast<char>(i);
        sommet->marquage = 0;
        sommet->priorite = 0;

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
        << ((*i)->rencontre ? "X" : " ")
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

void GrapheListe::marquerSommetsNonVisites()
{
    for(std::list<Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++){
        (*i)->visite = false;
        (*i)->rencontre = false;
    }
}

struct Sommet* GrapheListe::obtenirSommetDepuisIndice(char indice)
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

void GrapheListe::afficherFile()
{
    cout << "Etat de la file : " << endl;

    if(m_file.size() > 0){
        std::queue<Sommet*> copieFile;

        // Défile et affiche tous les éléments de la file.
        while(m_file.size() > 0){
            Sommet* sommetFile = m_file.front();
            m_file.pop();
            cout << "[" << sommetFile->indice << "]" << endl;
            copieFile.push(sommetFile);
        }

        // Enfile tous les éléments défilés.
        while(copieFile.size() > 0){
            Sommet* sommetFile = copieFile.front();
            copieFile.pop();
            m_file.push(sommetFile);
        }
    } else {
        cout << "File vide" << endl;
    }
}

void GrapheListe::parcoursProfondeurRecursif()
{
    this->marquerSommetsNonVisites();

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        VSPR((*i));
    }

    std::cout << std::endl;
}

void GrapheListe::VSPR(Sommet *_sommet)
{
    if(_sommet->visite == false){
        _sommet->visite = true;

        // Traitement du sommet courant.
        traiterSommet(_sommet);

        for(std::list<Lien*>::iterator j = _sommet->listeDeLien->begin(); j != _sommet->listeDeLien->end(); j++)
            VSPR(obtenirSommetDepuisIndice((*j)->indice));
    }
}

void GrapheListe::parcoursProfondeurPile()
{
    this->marquerSommetsNonVisites();

    for (std::list<Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        this->VSPNR((*i));
    }
    cout << endl;
}

/**
 * @brief GrapheListe::traiterSommet
 *        Traitement du sommet. (Pour l'instant, affichage uniquement)
 * @param sommet
 */
void GrapheListe::traiterSommet(Sommet* _sommet)
{
    cout << "Sommet : " << _sommet->indice << " visité." << endl;
}

void GrapheListe::calculerPriorite(Sommet* _sommet, TypeParcours _typeParcours)
{
    if(_typeParcours == PARCOURS_PROFONDEUR_PILE) {
        this->m_valeurPriorite ++;
    } else if(_typeParcours == PARCOURS_LARGEUR_FILE) {
        this->m_valeurPriorite --;
    }

    _sommet->priorite = m_valeurPriorite;
}

void GrapheListe::VSPNR(Sommet* _sommet)
{
    if(_sommet->visite == false){

        _sommet->rencontre = true;
        m_pile.push(_sommet);

        while(m_pile.empty() == false){

            Sommet* sommetPile = m_pile.top();        // Accède au premier élément.
            m_pile.pop();                             // Dépile l'élément de la pile.
            sommetPile->visite = true;                // Indique que l'élément dépilé est visité.

            // Traitement du sommet courant.
            traiterSommet(sommetPile);

            // Affichage de l'état de la pile.
            afficherPile();

            // Parcours de tous les voisins du sommet.
            for(std::list<Lien*>::iterator j = sommetPile->listeDeLien->begin(); j != sommetPile->listeDeLien->end(); j++){

                // Récupération du sommet voisin.
                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);
                // Si le voisin n'est ni empilé ni visité, on l'empile et le marque comme empilé.
                if(sommetLien->rencontre == false && sommetLien->visite == false){
                    sommetLien->rencontre = true;
                    m_pile.push(sommetLien);
                }
            }
        }

    }
}

void GrapheListe::parcoursLargeurFile()
{
    this->marquerSommetsNonVisites();

    for (std::list<struct Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++) {
        this->VSLNR((*i));
    }
}

void GrapheListe::VSLNR(Sommet *_sommet)
{
    if(_sommet->visite == false){
        _sommet->rencontre = true;
        m_file.push(_sommet);

        while(m_file.size() > 0){

            Sommet* sommetFile = m_file.front();    // Accède au dernier élément.
            m_file.pop();                           // Défile le dernier élément.
            sommetFile->visite = true;              // Marque l'élément comme visité.

            // Traitement du sommet courant.
            this->traiterSommet(sommetFile);

            // Affichage de l'état de la file.
            afficherFile();

            for(std::list<Lien*>::iterator j = sommetFile->listeDeLien->begin(); j != sommetFile->listeDeLien->end(); j++){

                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);

                if(sommetLien->rencontre == false && sommetLien->visite == false){
                    sommetLien->rencontre = true;
                    m_file.push(sommetLien);
                }
            }
        }
    }
}

void GrapheListe::parcoursGeneralise(TypeParcours _typeParcours)
{
    this->marquerSommetsNonVisites();

    for(std::list<Sommet*>::iterator i = this->m_listeDeSommet->begin(); i != this->m_listeDeSommet->end(); i++){
        this->VSGNR((*i), _typeParcours);
    }
}

void GrapheListe::VSGNR(Sommet *_sommet, TypeParcours _typeParcours)
{
    if(_sommet->visite == false) {
        _sommet->rencontre = true;

        this->calculerPriorite(_sommet, _typeParcours);
        this->m_filePriorite.push(_sommet);

        while(m_filePriorite.size() > 0) {
            Sommet* sommetFilePriorite = m_filePriorite.top();
            m_filePriorite.pop();

            sommetFilePriorite->visite = true;

            this->traiterSommet(sommetFilePriorite);

            for(std::list<Lien*>::iterator j = sommetFilePriorite->listeDeLien->begin(); j != sommetFilePriorite->listeDeLien->end(); j++) {
                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);

                if(sommetLien->visite == false && sommetLien->rencontre == false) {
                    sommetLien->rencontre = true;
                    this->calculerPriorite(sommetLien, _typeParcours);
                    this->m_filePriorite.push(sommetLien);
                }
            }
        }
    }
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
        struct Sommet* sommetLink = obtenirSommetDepuisIndice((*j)->indice);
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
