/** @mainpage

    Exemple de resolució completa de la pràctica de PRO2.
    
    L'enunciat de la pràctica ens demana crear un arbre filogenètic a partir d'un conjunt donat d'espècies. Aquest conjunt s'acabarà convertint en un conjunt de clústers, per facilitar la construcció de l'arbre filogenètic. Per aquesta raó he dissenyat tres mòduls, el de Especie, representada per un identificador, un gen i una llista dels k-mers del gen i els corresponents Cjt_especies i Cjt_clusters que representen un conjunt d'espècies i de clústers, respectivament. Per aquesta pràctica, el clústers ha sigut més un concepte, és a dir que no he programat una classe clúster per motius d'eficiència. 
    
    El programa principal està explicat en el mòdul program.cc i les classes s'expliquen amb més detall en els respectius mòduls.
    
    
    

*/

/** @file principal.cc
    @brief Programa principal
    
    Consisteix en un bucle on anem escollint les operacions que volem realitzar, explicades en els mòduls corresponents. Suposem que les dades d'entrada són sintacticament correctes, és a dir que els identificadors i els gens només estan formats per lletres majúscules, minúscules i pel caràcter de la barra baixa '_'. Les operacions es representen també amb strings, on s'explicita el que volem fer amb frases curtes.

*/

#include "Cjt_especies.hh"
#include "Cjt_clusters.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#endif

int main() {
    int k;
    cin >> k; // Valor necessari per calcular la distància entre especies
    string op;
    Cjt_especies mesp;              // declaracio del conjunt buit d'especies
    Cjt_clusters clust;             // declaracio del conjunt buit de clusters
    string id, g;                   // strings identificador i gen de l'especie
    while (cin >> op and op != "fin") {
        
        if (op == "crea_especie") {         // Crear especie
            cin >> id >> g;
            cout << "# crea_especie " << id << ' ' << g << endl;
            if (mesp.existeix_especie(id))
                cout << "ERROR: La especie " << id << " ya existe." << endl;
            
            else mesp.crea_especie(id, g, k);
            cout << endl;
        }
        
        else if (op == "obtener_gen") {    // Obtenir gen
            cin >> id;
            cout << "# obtener_gen " << id << endl;
            if(mesp.existeix_especie(id)) 
                cout << mesp.obtenir_gen(id) << endl;
        
            else cout << "ERROR: La especie " << id << " no existe." << endl;
            cout << endl;
        }
        
        else if (op == "distancia") {    // Distancia
            string id1, id2;
            cin >> id1 >> id2;
            cout << "# distancia " << id1 << ' ' << id2 << endl;
            bool existeix1 = mesp.existeix_especie(id1);
            bool existeix2 = mesp.existeix_especie(id2);
            
            if (not existeix1 and not existeix2)
                cout << "ERROR: La especie " << id1 << " y la especie " << id2 << " no existen." << endl;
            
            else if (not existeix1)
                cout << "ERROR: La especie " << id1 << " no existe." << endl;
            
            else if (not existeix2)
                cout << "ERROR: La especie " << id2 << " no existe." << endl;
            
            else cout << mesp.distancia(id1, id2) << endl;
            cout << endl;
        }
        
        else if (op == "elimina_especie") {    // Elimina especie
            cin >> id;
            cout << "# elimina_especie " << id << endl;
            if (mesp.existeix_especie(id)) mesp.elimina_especie(id);
            else cout << "ERROR: La especie " << id << " no existe." << endl;
            cout << endl;
        }
        
        else if (op == "existe_especie") {    // Existeix especie
            cin >> id;
            cout << "# existe_especie " << id << endl;
            if (mesp.existeix_especie(id)) cout << "SI" << endl;
            else cout << "NO" << endl;
            cout << endl;
        }
        
        else if (op == "lee_cjt_especies") {    // Llegir conjunt d'especies
            int nesp;
            cin >> nesp;
            mesp.llegir_cjt_especies(nesp, k);
            cout << "# lee_cjt_especies" << endl;
            cout << endl;
        }
        
        else if (op == "imprime_cjt_especies") {    // Imprimir el conjunt d'especies
            cout << "# imprime_cjt_especies" << endl;
            mesp.imprimir_cjt_especies();
        }
        
        else if (op == "tabla_distancias") {    // Imprimir taula de distancies entre especies
            cout << "# tabla_distancias" << endl;
            mesp.imprimir_distancies_especies();
        }
        
        else if (op == "inicializa_clusters") {    // Inicialitzar el conjunt de clusters
            cout << "# inicializa_clusters" << endl;
            mesp.inicialitzar_clusters(clust);
            clust.imprimir_distancies_clusters();
        }
        
        else if (op == "ejecuta_paso_wpgma") {   // Executar pas algorisme WPGMA
            cout << "# ejecuta_paso_wpgma" << endl;
            if (clust.numero_clusters() < 2) 
                cout << "ERROR: num_clusters <= 1" << endl << endl;
            else {
                clust.executar_pas_wpgma();
                clust.imprimir_distancies_clusters();
            }
            
        }
        
        else if (op == "imprime_cluster") {   // Imprimir cluster
            cin >> id;
            cout << "# imprime_cluster " << id << endl;
            if (clust.existeix_cluster(id)) clust.imprimir_cluster(id);
            else cout << "ERROR: El cluster " << id << " no existe." << endl;
            cout << endl;
        }
        
        else if (op == "imprime_arbol_filogenetico") {   // Imprimir arbre filogenetic
            cout << "# imprime_arbol_filogenetico" << endl;
            mesp.inicialitzar_clusters(clust);
            if (clust.numero_clusters() == 0) cout << "ERROR: El conjunto de clusters es vacio." << endl;
            else { 
                clust.arbre_filogenetic();
                cout << endl;
            }
            cout << endl;
        }
    
    }
}
