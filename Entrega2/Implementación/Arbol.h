#ifndef __ARBOL__H__
#define __ARBOL__H__

#include "Nodo.h"
#include <list>

template <class T>
class Arbol {
	
  protected:
    Nodo<T>* raiz;
  
  public:
    
    Arbol();
    Arbol(const T& val);
    
    ~Arbol();
    
    bool esVacio();
    
    Nodo<T>* obtenerRaiz();
    void fijarRaiz(T& val);
    
    bool insertarNodo(T& padre, T& n);
    bool eliminarNodo(T& n);
    Nodo<T>* buscarNodo(T& val);
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void inOrden();
    int grado();
	
	void printGivenLevel(int level);
	void printLevelOrder();
	int getLevel(T key);
	
	void returnNodes(std::list< Nodo<T>* > lista);
	void returnValues(std::list<T> lista);
	
};

#include "Arbol.hxx"

#endif

