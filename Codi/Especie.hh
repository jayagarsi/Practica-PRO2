/** @file Especie.hh
    @brief Especificació de la classe espècie
*/

#ifndef ESPECIE_HH
#define ESPECIE_HH

#include <string>
#ifndef NO_DIAGRAM
#include <map>
#endif
using namespace std;

/** @class Especie
    @brief Representa la informació del gen d'una espècie
    
    A més del gen, una espècie també té la seva seqüència de k-mers d'aquest, emmagatzemada en un mapa. Els k-mers d'un string són tots els substrings que es poden formar de longitud k, per tot k pertanyent als naturals, recorrent el conjunt en grups de k. El valor de k es declara al principi del programa, en el main, i serà el mateix fins a la terminació d'aquest. Cada k-mer té dos paràmetres un identificador, que és el substring de longitud k, i un enter que és el nombre de cops que es troba aquell k-mer dins del conjunt de k-mers.

*/
class Especie {
    
private:
    
    /** @brief Gen de l'espècie */
    string gen;
    /** @brief Llista dels k-mers del gen de l'espècie */
    map<string, int> kmers;
    
public:
    
//Constructores
    
    /** @brief Constructora per defecte
        \pre <em>Cert</em>
        \post S'omple el paràmetre implícit amb un string i una llista dels k-mers d'aquest.
    */
    Especie(const string& g, int& k);
    
    
    /** @brief Destructora per defecte
    
    */
    ~Especie();
    
    
// Consultores    
    
    /** @brief Consultora del gen de l'espècie
        \pre <em>Cert</em>
        \post Retorna l'atribut gen del paràmetre implícit
    */
    string consultar_gen() const;
    

    /** @brief Consultora del conjunt de k-mers
        \pre <em>Cert</em>
        \post Retorna un mapa amb els k-mers del paràmetre implícit
    */
    void consultar_kmer(map<string, int>& km) const;
    

private:
    
// Operacions
    
    /** @brief Càlcul del kmer d'una seqüència
        \pre <em>La seqüència g és de llargada com a mínim k</em>
        \post Retorna els k-mer d'una seqüència donada a partir del valor k definit al principi del programa emmagatzemats en un mapa. L'enter relacionat a cada substring representa el nombre de cops que un substring hi és en el string.
        
        L'ús d'aquest nombre és especialment necessari quan calculem la distància entre espècies.
    */
    void calcular_kmer(int& k);
    
};


#endif
