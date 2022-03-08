/** @file Especie.cc
    @brief Implementació de la classe Espècie
*/

#include "Especie.hh"
#ifndef NO_DIAGRAM
#include <string>
#endif

Especie::Especie(const string& g, int& k) {
    
    gen = g;
    calcular_kmer(k);
    
}

Especie::~Especie() {}

string Especie::consultar_gen() const {
    
    return gen;

}

void Especie::consultar_kmer(map<string, int>& km) const {
    
    km = kmers;

}

void Especie::calcular_kmer(int& k) {

    int i = 0;
    while (i < gen.length()-k+1) {                              
        string sub = gen.substr(i, k);                                      // Obtinc el substring que va des de i fins a k
        
        pair<map<string, int>::iterator, bool> unic;                        // Si el valor ja existia en el mapa, unic es fals
        unic = kmers.insert(make_pair(sub, 1));                             // i es suma 1 al contador del string
            
        if (not unic.second) ++unic.first->second; 
            
        ++i;
    }
    
}
