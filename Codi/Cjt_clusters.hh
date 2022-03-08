/** @file Cjt_clusters.hh
    @brief Especificació de la classe conjunt de clústers
*/
#ifndef CJT_CLUSTERS_HH
#define CJT_CLUSTERS_HH

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif


/** @class Cjt_clusters
    @brief Representa un conjunt de clústers.
    
    Un clúster pot estar format per una espècie sola, o per dos clústers més, d'on podem extreure que un clúster és com un arbre binari on a les fulles hi té espècies. Com en el conjunt d'espècies, la classe de conjunt de clústers té una taula amb les distàncies entre aquests, formada a partir de la taula del conjunt d'espècies.
    
    La classe ens permet fer diverses operacions com inicialitzar el conjunt de clústers amb l'actual conjunt d'espècies, executar un sol pas de l'algoritme WPGMA, imprimir un clúster del conjunt o executar l'algoritme WPGMA complet i imprimir l'arbre filogenètic resultant.

*/
class Cjt_clusters {
    
private:
    /** @brief Conjunt de clústers, representat amb un mapa d'arbres binaris, definits amb un string i un double, associats a un string */
    map<string, BinTree<pair<string, double> > > mclust;
    /** @brief Mapa de distancies entre clusters */
    map<string, map<string, double> > cldist;

     
public:
    
// Constructores
    
    /** @brief Constructora per defecte
        \pre <em>Cert</em>
        \post Crea un conjunt de clústers buit
    */
    Cjt_clusters();
    
    
    /** @brief Destructora per defecte
    
    */
    ~Cjt_clusters();
    
    
// Operacions
    
    /** @brief Buidar el conjunt de clústers
        \pre <em>Cert</em>
        \post Deixa el paràmetre implícit buit
        
        Aquesta funció és important per inicialitzar els clústers i poder assegurar que en el conjunt no hi havia informació basura d'altres operacions
    */
    void buidar_cjt();
    
    
    /** @brief Actualitzar conjunt de clusters
        \pre <em>Cert</em>
        \post Afegeix un clúster al paràmetre implícit, a partir d'una espècie
    */
    void actualitzar_clusters(const pair<string, Especie>& esp);
    
    
    /** @brief Afegir distancia a la taula
        \pre <em>Cert</em>
        \post Afegeix una fila de distàncies a la taula del paràmetre implícit a partir de la taula de distàncies entre espècies
    */
    void afegir_distancia(const pair<string, map<string, double> >& edist);
    
    
    /** @brief Executar un pas de l'algoritme WPGMA
        \pre <em>El paràmetre implícit té dos clústers com a mínim</em>
        \post Fusiona els dos clústers a menor distància en un de nou i imprimeix la taula de distàncies entre clústers resultant
    */
    void executar_pas_wpgma();
    

// Consultores
    
    /** @brief Consultora del nombre de clusters del conjunt
        \pre <em>Cert</em>
        \post Retorna el nombre d'elements que hi ha en el paràmetre implícit
    */
    int numero_clusters() const;
    
    
    /** @brief Cerca d'un clúster
        \pre <em>Cert</em>
        \post Retorna cert si en el paràmetre implícit hi és el clúster amb identificador id i fals altrament.
    */
     bool existeix_cluster(const string& id) const;
     
    
// Entrada/Sortida

    /** @brief Imprimir clúster
        \pre <em>El clúster es troba dins del paràmetre implícit</em>
        \post Imprimeix el clúster amb identificador id i tots els seus fills, en cas que en tingui.
    */
    void imprimir_cluster(const string& id);
    
    
    /** @brief Imprimir arbre filogenetic
        \pre <em>El paràmetre implícit té com a mínim dos clústers</em>
        \post S'aplica l'algoritme WPGMA complet i s'imprimeix l'arbre filogenètic resultant
    */
    void arbre_filogenetic();
    
    
    /** @brief Imprimir la taula de distàncies
        \pre <em>Cert</em>
        \post S'escriu pel canal estàndard de sortida la taula amb les distàncies entre cada parell de clústers tal i com es troben en el moment de la crida en el paràmetre implícit. Si la taula és buida no s'imprimeix res
    */
    void imprimir_distancies_clusters();
    

private:
    
    /** @brief Fusionar clústers
        \pre <em>Ambdós clústers es troben dins del paràmetre implícit</em>
        \post Retorna un clúster format pels altres dos
    */
    void fusionar_clusters(const string& id1, const string& id2, BinTree<pair<string, double> >& tf);
    
    
    /** @brief Actualitzar taula de distàncies
        \pre <em>Cert</em>
        \post Actualitza la taula de distàncies entre clústers amb els nous clústers
    */
    void actualitzar_taula_distancies(const string& id1, string& id2);
    
    
    /** @brief Imprimir arbre binari
        \pre <em>Cert</em>
        \post Escriu pel canal estàndard de sortida un arbre binari en preordre.
        
        Aquesta és una funció auxiliar per poder facilitar l'escriptura recursiva de l'arbre
    */
    void imprimir_arbre(const BinTree<pair<string, double> >& clust) const;
    
};



#endif
