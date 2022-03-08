/** @file Cjt_especies.cc
    @brief Implementació de la classe conjunt d'espècies
*/

#include "Cjt_especies.hh"
#include <iostream>

Cjt_especies::Cjt_especies() {
    
}

Cjt_especies::~Cjt_especies() {}

bool Cjt_especies::existeix_especie(const string& id) const {
    
    map<string, Especie>::const_iterator it = mesp.find(id);
    if (it == mesp.end()) return false;                          // L'espècie no existeix
    else return true;
    
}

string Cjt_especies::obtenir_gen(const string& id) const {
    
    map<string, Especie>::const_iterator it = mesp.find(id);
    return it->second.consultar_gen();

}

double Cjt_especies::distancia(const string& id1, const string& id2) const {
    
// Com s'explica en la especificacio la informacio taula esta emmagatzemada de manera eficient, sense repetir 
// valors redundants. Per aquesta rao sabem que l'identificador mes petit lexicograficament tindra tota la informacio
// necessaria i per aixo es necessari fer la comparacio
    
    if (id1 < id2) {                                                                
        map<string, map<string, double> >::const_iterator itfil = dist.find(id1);
        map<string, double>::const_iterator itcol = itfil->second.find(id2);
        return itcol->second;
    }
                                                        
    else if (id1 > id2) {                       
        map<string, map<string, double> >::const_iterator itfil = dist.find(id2);
        map<string, double>::const_iterator itcol = itfil->second.find(id1);
        return itcol->second;
    }
    
    return 0;
}

void Cjt_especies::inicialitzar_clusters(Cjt_clusters& cjt) {
    
    cjt.buidar_cjt();                               // ens assegurem que el conjunt de clusters sigui buit
    
    for (map<string, map<string, double> >::const_iterator it = dist.begin(); it != dist.end(); ++it)       // passem cada fila de la taula
        cjt.afegir_distancia(*it);
    
    for (map<string, Especie>::const_iterator it = mesp.begin(); it != mesp.end(); ++it)                    // passem cada especie
        cjt.actualitzar_clusters(*it);
    
}

void Cjt_especies::crea_especie(const string& id, const string& g, int& k) {
    
    Especie esp(g, k);
    mesp.insert(make_pair(id, esp));
    Cjt_especies::actualitza_taula(id);
    
}

void Cjt_especies::elimina_especie(const string& id) {
    
    mesp.erase(id);
    Cjt_especies::actualitza_taula(id);
    
}

void Cjt_especies::llegir_cjt_especies(int nesp, int& k) {
    
    string id, gen;
    mesp.clear();
    for (int i = 0; i < nesp; ++i) {
        cin >> id >> gen;
        Especie esp(gen, k);
        mesp.insert(make_pair(id, esp));
    }
    dist.clear();
    Cjt_especies::actualitza_taula("0");
    
}

void Cjt_especies::imprimir_cjt_especies() {
    
    for (map<string, Especie>::const_iterator it = mesp.begin(); it != mesp.end(); ++it)
        cout << it -> first << ' ' << it -> second.consultar_gen() << endl;
    cout << endl;

}

void Cjt_especies::imprimir_distancies_especies() {
    
    map<string, double>::const_iterator itcol;
    map<string, map<string, double> >::iterator itfil = dist.begin();
    
    while (itfil != dist.end()) {
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

void Cjt_especies::actualitza_taula(const string& id) {                  
    
    if (id == "0") {                                                                      // Marca "0" per diferenciar que es llegeix un nou cjt d'especies i la taula s'ha de tornar a construir (o construir per primer cop)
        
        map<string, Especie>::const_iterator itcol;                                      // Iterador de les columnes del mapa de distancies
        map<string, Especie>::const_iterator itfil = mesp.begin();                       // Iterador de les files del mapa de distancies 
        
        while (itfil != mesp.end()) {
            
           dist.insert(make_pair(itfil->first, map<string, double>()));                  // Els iteradors itfil i itcol realment apunten a
           string aux = itfil -> first;                                                 // elements del mapa d'especies pero li dic 
           ++itfil;                                                                     // itfil i itcol per entendre que un es per les
           itcol = itfil;                                                               // files de la taula i un per les columnes        
           while (itcol != mesp.end()) {
               double d = Cjt_especies::calcular_distancia(aux, itcol->first);
               dist[aux].insert(make_pair(itcol->first, d));
               ++itcol;
            
           }
        }
    }

    else if (dist.size() < mesp.size()) {                   // S'ha afegit una especie al conjunt
                                                            // (el tamany del conjunt sera mes gran que el de la taula actual)
        dist.insert(make_pair(id, map<string, double>()));
        map<string, map<string, double> >::iterator it1 = dist.begin();
        map<string, map<string, double> >::iterator it2 = dist.find(id);
        
        while (it1 != it2) {                                                        // Inserir a cada fila el nou element id
            double d = Cjt_especies::calcular_distancia(it1->first, id);
            it1->second.insert(make_pair(id, d));
            ++it1;
        }
        // Al terminar el bucle it1 == it2 == dist.find(id);
        ++it2;
        while (it2 != dist.end()) {                                                 // Inserir a la fila del nou element la distancia amb
            double d = Cjt_especies::calcular_distancia(id, it2->first);            // els altres
            it1->second.insert(make_pair(it2->first, d));
            ++it2;
        }
        
    }
    
    else if (dist.size() > mesp.size()) {                   // S'ha eliminat una especie del conjunt
                                                            // (el tamany del conjunt sera mes petit que el de la taula actual)
        dist.erase(id);
        map<string, map<string, double> >::iterator it = dist.begin();
        while (it != dist.end()) {
            it->second.erase(id);
            ++it;
        }
    }
    

}

double Cjt_especies::calcular_distancia(const string& id1, const string& id2) {
    
    map<string, Especie>::iterator it;
    
    it = mesp.find(id1);
    map<string, int> kmer1; 
    it->second.consultar_kmer(kmer1);
    
    it = mesp.find(id2);
    map<string, int> kmer2;
    it->second.consultar_kmer(kmer2);
    
    double cardinal_unio = 0;
    double cardinal_interseccio = 0;

    map<string, int>::iterator it1 = kmer1.begin();
    map<string, int>::iterator it2 = kmer2.begin();
    
    while (it1 != kmer1.end() and it2 != kmer2.end()) {         // Calcul del cardinal de la unio i de la interseccio
                                                                // dels dos conjunts de kmers fent un recorregut
        if (it1 -> first < it2 -> first) {                      // simultani als dos mapes 
            cardinal_unio += it1 -> second;
            ++it1;
        }
        
        else if (it2 -> first < it1 -> first) {
            cardinal_unio += it2 -> second;
            ++it2;
        }
        
        else {
            cardinal_unio += max(it1 ->second, it2 -> second);
            cardinal_interseccio += min(it1 -> second, it2 ->second);
            ++it1;
            ++it2;
        }
    }
    
    while (it1 != kmer1.end()) {                    // En el cas que hi hagin mes elemetns en un conjunt que en l'altre
        cardinal_unio += it1 -> second;             // hem de sumar al cardinal de la unio aquells elements que 
        ++it1;                                      // te de mes un dels dos conjunts
    }

    while (it2 != kmer2.end()) {
        cardinal_unio += it2 -> second;
        ++it2;
    }
    
    double distancia = (1 - (cardinal_interseccio/cardinal_unio))*100;          // Formula de la distancia entre especies
    
    return distancia;
    
}
