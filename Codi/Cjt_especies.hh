/** @file Cjt_especies.hh
    @brief Especificació de la classe conjunt d'espècies
*/
#ifndef CJT_ESPECIES_HH
#define CJT_ESPECIES_HH

#include "Especie.hh"
#include <map>
#ifndef NO_DIAGRAM
#include <string>
#include "Cjt_clusters.hh"
#endif
using namespace std;



/** @class Cjt_especies
    @brief Representa un conjunt d'espècies
    
    El conjunt d'espècies ve representat per una mapa de strings que tenen associats una espècie cadascuna. En l'apartat de Especie s'explica millor com està implementada aquesta.
    
    Aquesta classe ens proporciona diverses operacions com llegir un conjunt d'espècies o imprimir el del paràmetre implícit, obtenir el gen d'una espècie a partir d'un identificador, obtenir la distància entre dues espècies, afegir noves espècies al conjunt o eliminar-les, etc. 
    
    A més a més, la classe també té una taula amb les distàncies entre espècies. Aquesta taula es construeix de tal manera que s'emmagatzema la manera d'una forma eficient. És a dir que ni la distància d'una espècie a si mateixa ni les distàncies repetides es guarden. D'aquí podem extreure que l'única fila de la taula que té tots els elements del conjunt és la primera. A més de l'eficiència, organitzar la taul d'aquesta manera va bé per facilitar-ne la impressió ja que és com ens demanen que sigui escrita en l'enunciat.
    
*/

class Cjt_especies {

private:
    
    /** @brief Conjunt d'espècies, representat per un mapa d'espècies associades a un string */
    map<string, Especie> mesp;
    
    /** @brief Taula de distàncies entre espècies, representada amb un mapa de mapes associats a un string */
    map<string, map<string, double> > dist;

    
public:
    
// Constructores
    
    /** @brief Constructora per defecte
        \pre <em>Cert</em>
        \post El paràmetre implícit és buit
    */
    Cjt_especies();
    
    
    /** @brief Destructora per defecte

    */
    ~Cjt_especies();
    
    
// Consultores
    
    /** @brief Consultora de l'existència d'una espècie
        \pre <em>Cert</em>
        \post Retorna un boolea, cert si l'espècie existeix en el paràmetre implícit i fals altrament.
    */
    bool existeix_especie(const string& id) const;
    
    
    /** @brief Consultora del gen d'una espècie
        \pre <em>Existeix en el paràmetre implícit l'espècie amb identif = id</em> 
        \post Retorna el gen corresponent a l'espècie amb identificador id
    */
    string obtenir_gen(const string& id) const;
    
    
    /** @brief Consultora de la distància entre dues espècies
        \pre <em>Existeixen dues espècies amb identificador id1 i id2 en el conjunt i la taula de distancies ja ha sigut creada</em>
        \post Retorna la distància entre dues espècies accedint a la taula de distàncies
        
        Com la precondició imposa que la taula ja existeix, accedir-hi és molt més eficient que fer un altre cop el càlcul.
    */
    double distancia(const string& id1, const string& id2) const;
   
    
// Modificadores
    
     /** @brief Inicialitzar el conjunt de clusters
        \pre <em>Cert</em>
        \post Actualitza el conjunt de clústers amb l'actual d'espècies i copia la taula de distàncies del paràmetre implícit al conjunt de clústers
    */
    void inicialitzar_clusters(Cjt_clusters& cjt);

    
    /** @brief Afegir una espècie al conjunt
        \pre <em>L'espècie no hi és en el paràmetre implícit</em>
        \post Crea una espècie amb identificador id i gen g i l'afegeix al paràmetre implícit
    */
    void crea_especie(const string& id, const string& g, int& k);
    
    
    /** @brief Eliminar una espècie del conjunt
        \pre <em>L'espècie existeix dins del paràmetre implícit</em>
        \post Esborra l'espècie amb identificador id dins del paràmetre implícit
    */
    void elimina_especie(const string& id);
    

// Entrada/Sortida
    
    /** @brief Llegir un conjunt de n espècies
        \pre <em>Les n especies tenen identificadors diferents entre si</em>  
        \post Lleigeix pel canal estàndard d'entrada un conjunt d'espècies i les afegeix al paràmetre implícit, substituint a les que hi eren abans
    */
    void llegir_cjt_especies(int nesp, int& k);
    
    
    /** @brief Imprimir el conjunt d'espècies
        \pre <em>Cert</em>
        \post Escriu pel canal estàndard de sortida les espècies del paràmetre implícit ordenades per identificador en ordre lexicogràfic
    */
    void imprimir_cjt_especies();
    
    
    /** @brief Imprimir la taula de distàncies entre espècies
        \pre <em>Cert</em>
        \post Escriu pel canal estàndard de sortida la taula de distàncies entre espècies. Si aquesta és buida no s'escriu res
    */
    void imprimir_distancies_especies();
    

private:
        
    /** @brief Actualitzar la taula de distàncies
        \pre <em>Cert</em>
        \post Varia la taula de distàncies segons el canvi que s'hagi fet al paràmetre implícit
        
        El string que es passa per paràmetre és per saber en quin cas estem, si s'ha afegit una espècie, si s'ha eliminat o si s'ha llegit un nou conjunt
    */
    void actualitza_taula(const string& id);
    

    /** @brief Càlcul de la distància entre dues espècies
        \pre <em>Cert</em>
        \post Retorna la distancia entre les dues espècies amb gens g1 i g2, respectivament
        
        La diferència entre aquesta funcio i la anterior anomenada distancia, és que aquesta fa el càlcul de la distància i l'altre simplement accedeix a la matriu de les distàncies i retorna els valors d'aquesta. Aquesta funció es crida quan el conjunt no és buit, per actualitzar la taula de distàncies.
    */
    double calcular_distancia(const string& id1, const string& id2);    

};

#endif
