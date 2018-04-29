#include "grapheliste.h"
#include <iostream>

using namespace std;

GrapheListe::GrapheListe(int _nombreSommet)
{
    m_nombreSommet = _nombreSommet;
    m_valeurPriorite = 0;
    m_listeDeSommet = new std::list<Sommet*>();


    for(int i = 0; i < m_nombreSommet; i++){
        Sommet* sommet = new Sommet();
        sommet->rencontre = false;
        sommet->visite = false;
        sommet->listeDeLien = new std::list<Lien*>();
        sommet->indice = 'A' + static_cast<char>(i);
        sommet->marquage = 0;
        sommet->priorite = 0;

        m_listeDeSommet->push_back(sommet);
    }
}

GrapheListe::~GrapheListe()
{
    for (std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {

        for(std::list<Lien*>::iterator j = (*i)->listeDeLien->begin(); j != (*i)->listeDeLien->end(); j++){
            delete (*j);
            (*j) = nullptr;
        }

        delete (*i);
        (*i) = nullptr;
    }
    delete m_listeDeSommet;
}

void GrapheListe::afficher()
{

    for (std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {

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
    std::list<Sommet*>::iterator it = m_listeDeSommet->begin();

    std::advance(it, static_cast<int>(_sommetDepart - 'A')); // Avance l'itérateur jusqu'au bon élément.

    Lien* lien = new Lien();
    lien->indice = _sommetArrive;
    lien->ponderation = _ponderation;

    (*it)->listeDeLien->push_back(lien);
}

void GrapheListe::ajouterArrete(char _sommet1, char _sommet2, int _ponderation)
{
    ajouterArc(_sommet1, _sommet2, _ponderation);
    ajouterArc(_sommet2, _sommet1, _ponderation);
}

void GrapheListe::reinitialiserFlags()
{
    for(std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++){
        (*i)->visite = false;
        (*i)->rencontre = false;
        (*i)->priorite = 0;
    }
}

Sommet* GrapheListe::obtenirSommetDepuisIndice(char _indice)
{
    for (std::list<Sommet*>::iterator j = m_listeDeSommet->begin(); j != m_listeDeSommet->end(); j++) {
        if((*j)->indice == _indice){
            return (*j);
        }
    }

    return nullptr;
}

void GrapheListe::afficherPile()
{
    cout << "Etat de la pile : " << endl;

    if(m_pile.size() > 0){

        std::stack<Sommet*> copiePile = m_pile;

        // Dépilage et affichage de tous les éléments de la copie de la pile.
        while(copiePile.size() > 0){
            Sommet* sommetPile = copiePile.top();
            copiePile.pop();
            cout << "[" << sommetPile->indice << "]" << endl;
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

        std::queue<Sommet*> copieFile = m_file;

        // Défile et affiche tous les éléments de la file.
        while(copieFile.size() > 0){
            Sommet* sommetFile = copieFile.front();
            copieFile.pop();
            cout << "[" << sommetFile->indice << "]" << endl;
        }
    } else {
        cout << "File vide" << endl;
    }
}

void GrapheListe::afficherFilePriorite()
{
    cout << "Etat de la file de priorité : " << endl;
    if(m_filePriorite.size() > 0) {
        std::priority_queue<Sommet*, std::vector<Sommet*>, CompareSommet> copieFilePriorite = m_filePriorite;

        while(copieFilePriorite.size() > 0) {
            Sommet* sommetFilePriorite = copieFilePriorite.top();
            copieFilePriorite.pop();
            cout << "[" << sommetFilePriorite->indice << "," << sommetFilePriorite->priorite << "]" << endl;
        }


    } else {
        cout << "File de priorité vide." << endl;
    }
}

void GrapheListe::parcoursProfondeurRecursif()
{
    reinitialiserFlags();

    for (std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {
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
    reinitialiserFlags();

    for (std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {
        VSPNR((*i));
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
        m_valeurPriorite --;
    } else if(_typeParcours == PARCOURS_LARGEUR_FILE) {
        m_valeurPriorite ++;
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
    reinitialiserFlags();

    for (std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {
        VSLNR((*i));
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
            traiterSommet(sommetFile);

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
    reinitialiserFlags();

    for(std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++){
        VSGNR((*i), _typeParcours);
    }
}

void GrapheListe::VSGNR(Sommet *_sommet, TypeParcours _typeParcours)
{
    if(_sommet->visite == false) {
        _sommet->rencontre = true;

        calculerPriorite(_sommet, _typeParcours);
        m_filePriorite.push(_sommet);

        while(m_filePriorite.size() > 0) {
            Sommet* sommetFilePriorite = m_filePriorite.top();
            m_filePriorite.pop();

            sommetFilePriorite->visite = true;

            traiterSommet(sommetFilePriorite);

            for(std::list<Lien*>::iterator j = sommetFilePriorite->listeDeLien->begin(); j != sommetFilePriorite->listeDeLien->end(); j++) {
                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);

                if(sommetLien->visite == false && sommetLien->rencontre == false) {
                    sommetLien->rencontre = true;
                    calculerPriorite(sommetLien, _typeParcours);
                    m_filePriorite.push(sommetLien);
                }
            }
        }
    }
}

void GrapheListe::parcoursARPM()
{
    reinitialiserFlags();

    for(std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++) {
        VSARMP((*i));
    }
}

void GrapheListe::VSARMP(Sommet *_sommet)
{
    if(_sommet->visite == false) {

        _sommet->priorite = 0; // Priorité quelconque.
        m_filePriorite.push(_sommet);

        while(m_filePriorite.size() > 0) {

            Sommet* sommetFilePriorite = m_filePriorite.top();
            m_filePriorite.pop();

            sommetFilePriorite->visite = true;

            traiterSommet(sommetFilePriorite);

            for(std::list<Lien*>::iterator j = sommetFilePriorite->listeDeLien->begin(); j != sommetFilePriorite->listeDeLien->end(); j++) {
                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);

                if(sommetLien->visite == false) {
                    sommetLien->priorite = (*j)->ponderation;

                    if(sommetLien->rencontre == false){
                        sommetLien->rencontre = true;
                        m_filePriorite.push(sommetLien);
                    }
                }
            }
        }
    }
}

void GrapheListe::parcoursACPC()
{
    reinitialiserFlags();

    for(std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++){
        VSACPC((*i));
    }
}

void GrapheListe::VSACPC(Sommet* _sommet)
{
    if(_sommet->visite == false) {
        _sommet->priorite = 0;          // Initialise la priorité du sommet à 0.
        m_filePriorite.push(_sommet);   // Ajoute le sommet avec priorité nulle dans la file de priorité.

        while(m_filePriorite.size() > 0) {

            Sommet* sommetFilePriorite = m_filePriorite.top();
            m_filePriorite.pop();

            sommetFilePriorite->visite = true;
            traiterSommet(sommetFilePriorite);



            for(std::list<Lien*>::iterator j = sommetFilePriorite->listeDeLien->begin(); j != sommetFilePriorite->listeDeLien->end(); j++) {

                Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);

                if(sommetLien->visite == false){

                    // Calcul de la priorité si il n'a pas déjà été emfilé.
                    if(sommetLien->rencontre == false) {
                        sommetLien->priorite = sommetFilePriorite->priorite + (*j)->ponderation; // priorité du sommet source + ponderation de l'arc.

                    // Cas ou l'on doit recalculer la priorité. (P.ex pour I, dernière figure de la page 29)
                    } else {
                        if(sommetLien->priorite > sommetFilePriorite->priorite + (*j)->ponderation){
                            sommetLien->priorite = sommetFilePriorite->priorite + (*j)->ponderation;
                        }
                    }

                    if(sommetLien->rencontre == false){
                        sommetLien->rencontre = true;
                        m_filePriorite.push(sommetLien);
                    }
                }
            }

            afficherFilePriorite();
        }
    }
}

void GrapheListe::parcoursDCFC()
{
    reinitialiserFlags();
    m_numero = 0;

    for(std::list<Sommet*>::iterator i = m_listeDeSommet->begin(); i != m_listeDeSommet->end(); i++){
        if((*i)->visite == false){
            VSDCFC((*i));
        }
    }
}

int GrapheListe::VSDCFC(Sommet* _sommet)
{
    m_numero = m_numero + 1;
    int minimum = m_numero;
    _sommet->visite = true;
    _sommet->marquage = m_numero;
    m_pile.push(_sommet);

    for(std::list<Lien*>::iterator j = _sommet->listeDeLien->begin(); j != _sommet->listeDeLien->end(); j++) {

        Sommet* sommetLien = obtenirSommetDepuisIndice((*j)->indice);
        int M = 0;

        if(sommetLien->visite == false){
            M = VSDCFC(sommetLien);
        } else {
            M = sommetLien->marquage;
        }

        minimum = min(minimum, M);
    }

    if(minimum == _sommet->marquage) {

        cout << "Composante fortement connexe : "  << endl << "[";
        Sommet* sommetPile;
        do {
            sommetPile = m_pile.top();
            m_pile.pop();
            sommetPile->marquage = m_nombreSommet + 1;
            cout << sommetPile->indice << ",";
        } while(sommetPile->indice != _sommet->indice);


        cout << "\b]" << endl; // \b permet de positionner le flux 1 caractère avant.
    }

    return minimum;
}
