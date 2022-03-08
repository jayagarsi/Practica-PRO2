/** @file Cjt_clusters.cc
    @brief Implementació de la classe conjunt de clústers
*/
#ifndef NO_DIAGRAM
#include <iostream>
#include "Cjt_especies.hh"
#endif
#include "BinTree.hh"
using namespace std;

Cjt_clusters::Cjt_clusters() {
    
}

Cjt_clusters::~Cjt_clusters() {}

void Cjt_clusters::buidar_cjt() {

    mclust.clear();
    cldist.clear();
    
}

void Cjt_clusters::actualitzar_clusters(const pair<string, Especie>& esp) {
    
    mclust.insert(make_pair(esp.first, BinTree<pair<string, double> >(make_pair(esp.first, 0.00))));
    
}

void Cjt_clusters::afegir_distancia(const pair<string, map<string, double> >& edist) {
    
    cldist.insert(edist);
    
}

void Cjt_clusters::executar_pas_wpgma() {
 
    map<string, map<string, double> >::iterator itfil = cldist.begin();
    map<string, double>::iterator itcol = itfil->second.begin();
    
    map<string, map<string, double> >::iterator itaux1 = itfil;             // itaux1 tindra la fila on es troben els clusters a menor distància
    map<string, double>::iterator itaux2;                                   // itaux2 tindra la columna dels clústers a menor distància
    
    double min = 0;                                         // valor per saber en cada moment quina es la distància més petita de la taula
    string aux;                                             // valor auxiliar per desempatar quan hi han dos distàncies iguals                          
    
    while (itfil != cldist.end()) {                     // despres del bucle tindrem la posicio de la distancia mes petita
        
        itcol = itfil->second.begin();
        if (itfil == cldist.begin()) {                          // en la primera iteracio necessitem els valors inicialitzats
            min = itcol -> second;
            aux = itcol -> first;
            itaux2 = itcol;
            ++itcol;
        }
        
        while (itcol != itfil->second.end()) {
            
            if ((itcol->second) < min) {                        // cas en el que la distància és més petita que la mínima
                
                itaux1 = itfil;
                itaux2 = itcol;
                min = itcol->second;
                
            }
            
            else if ((itcol->second) == min) {                  // cas en que la distància és igual a la mínima
                if ((itcol->first) < aux) {                     // si el string de itcol->first es mes petit que la del mínim actualitzem, altrament no fem res
                    itaux1 = itfil;
                    itaux2 = itcol;
                    min = itcol->second;
                }
            }
            ++itcol;
        }
        ++itfil;
    }
   
    string id1 = itaux1->first;
    string id2 = itaux2->first;
    
    BinTree<pair<string, double> > taux;
    Cjt_clusters::fusionar_clusters(id1, id2, taux);
        
    mclust.insert(make_pair(id1+id2, taux));
    mclust.erase(id1);                                              // eliminem del conjunt de clústers els
    mclust.erase(id2);                                              // strings fusionats
    
    Cjt_clusters::actualitzar_taula_distancies(id1, id2);
        
}

int Cjt_clusters::numero_clusters() const {
    
    return mclust.size();
    
}

bool Cjt_clusters::existeix_cluster(const string& id) const {
    
    map<string, BinTree<pair<string, double> > >::const_iterator it = mclust.find(id);
    if (it != mclust.end()) return true;                                    // el cluster existeix en el conjunt
    else return false;
    
}

void Cjt_clusters::imprimir_cluster(const string& id) {
    
    map<string, BinTree<pair<string, double> > >::const_iterator it = mclust.find(id);
    BinTree<pair<string, double> > clust = it->second;
    
    Cjt_clusters::imprimir_arbre(clust);
    cout << endl;
    
}

void Cjt_clusters::arbre_filogenetic() {
    
    int num_clust = mclust.size();
    while (num_clust > 1) {                             // per reaprofitar codi, com crear l'arbre filogenetic es aplicar l'algoritme wpgma
        Cjt_clusters::executar_pas_wpgma();             // complet, faig un bucle on es va executant cada pas de l'algoritme fins que el
        --num_clust;                                    // parametre implicit tingui un sol element
    }
    
    map<string, BinTree<pair<string, double> > >::iterator it = mclust.begin();     // com nomes tinc un element estic segur que el que vull imprimir es troba en mclust.begin()
    Cjt_clusters::imprimir_arbre(it->second);
    
}

void Cjt_clusters::imprimir_distancies_clusters() {
    
    map<string, double>::const_iterator itcol;
    map<string, map<string, double> >::const_iterator itfil = cldist.begin();
    
    while (itfil != cldist.end()) {
        itcol = itfil -> second.begin();
        cout << itfil -> first << ':';
        while (itcol != itfil->second.end()) {
            cout << ' ' << itcol->first << " (" << itcol->second << ")";
            ++itcol;
        }
        cout << endl;
        ++itfil;
    }
    cout << endl;
    
}

void Cjt_clusters::fusionar_clusters(const string& id1, const string& id2, BinTree<pair<string, double> >& tf) {
    
    // com la taula ha de estar ordenada lexicograficament haurem de tenir el id menor primer, per aixo faig la comparacio
    
    map<string, BinTree<pair<string, double> > >::const_iterator it1 = mclust.find(id1);
    map<string, BinTree<pair<string, double> > >::const_iterator it2 = mclust.find(id2);
    
    // com se que id1 i id2 existeixen dins del conjunt, ja que m'asseguro que no s'eliminin fins despres de fusionar els clusters, 
    // puc utilitzar l'operador [] amb la total seguretat de saber que no es crearan valors en la taula de distancia
    
    if (id1 < id2) {
        double d = cldist[id1][id2]/2;                                  
        tf = BinTree<pair<string, double> >(make_pair(id1 + id2, d), it1->second, it2->second);
    }
    
    else if(id2 < id1) {
        double d = cldist[id2][id1]/2;
        tf = BinTree<pair<string, double> >(make_pair(id2 + id1, d), it2->second, it1->second);
    }

}

void Cjt_clusters::actualitzar_taula_distancies(const string& id1, string& id2) {             // sabem que id1 < id2 per com esta ordenada la taula
    
    map<string, map<string, double> >::iterator itfinal = cldist.find(id2);
    map<string, map<string, double> >::iterator itfil = cldist.begin();
    
    map<string, double>::iterator itcol1;
    map<string, double>::iterator itcol2;
    
    while (itfil != itfinal) {
        
        if (itfil->first == id1) {                              // cas per quan la fila on estem es la que te id1
            
            map<string, double> maux = itfil->second;
            cldist.erase(itfil);
            
            cldist.insert(make_pair(id1+id2, maux));
            itfil = cldist.find(id1+id2);
            
            map<string, map<string, double> >::iterator itaux;
            itfil->second.erase(id2);
            itcol1 = itfil->second.begin();
            
            while (itcol1 != itfil->second.end()) {
                
                if (itcol1->first < id2) {
                    itaux = cldist.find(itcol1->first);
                    itcol2 = itaux->second.find(id2);
                    itcol1->second = (itcol1->second + itcol2->second)/2;
                }
                
                else {
                    itaux = cldist.find(id2);
                    itcol2 = itaux->second.find(itcol1->first);
                    itcol1->second = (itcol1->second + itcol2->second)/2;
                }
                ++itcol1;
            }
            
        }
    
        else if (itfil->first > id1)                            // cas per les files que estiguin entre les dues files amb
            itfil->second.erase(id2);                           // id1 i id2 on nomes he d'eliminar la columna amb id2
            
        else {                                                  // cas per les files que estiguin abans de la fila amb id1
            
            itcol1 = itfil->second.find(id1);
            itcol2 = itfil->second.find(id2);
            
            string saux = itcol1->first;
            double daux = (itcol1->second + itcol2->second)/2;
            
            itfil->second.insert(make_pair(saux+id2, daux));
            itfil->second.erase(itcol2);
            
        }
        itfil->second.erase(id1);
        itfil->second.erase(id2);
        ++itfil;
    }
    cldist.erase(itfinal);
    
}

void Cjt_clusters::imprimir_arbre(const BinTree<pair<string, double> >& clust) const {
    
    if (not clust.empty()) {
        
        if (clust.left().empty() and clust.right().empty())                 // cas en que tinguem una especie
            cout << '[' << clust.value().first << ']';
        
        else {
            cout << "[(" << clust.value().first << ", " << clust.value().second << ") ";
            imprimir_arbre(clust.left());
            imprimir_arbre(clust.right());
            cout << ']';
        }
    }
}




