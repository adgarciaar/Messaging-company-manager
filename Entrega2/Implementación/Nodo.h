#ifndef __NODO__H__
#define __NODO__H__

#include <iostream>
#include <list>

template< class T >
class Nodo {
	
  public:
    
    typedef std::list< Nodo<T>* > TList;
  
  public:
    
    Nodo();
    Nodo(const T& val);
    
    ~Nodo();
    
    T& obtenerDato();
    void fijarDato(T& val);
    
    TList& obtenerDesc();
    void fijarDesc(TList& listaDesc);
    
    bool adicionarDesc(T& nval);
    bool eliminarDesc(T& val);
    Nodo<T>* buscarDesc(T& val);
    void limpiarLista();
    unsigned int numDesc();
    
    bool insertarNodo(T& padre, T& n);
    bool eliminarNodo(T& n);
    Nodo<T>* buscarNodo(T& val);
    int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void inOrden();
    int grado();
	
	void printGivenLevel(Nodo<T>* root, int level);
	void printLevelOrder(Nodo<T>* root);
	int getLevelUtil(Nodo<T>* node, T key, int level);
	int getLevel(Nodo<T>* node, T key);
	
	void returnNodes(Nodo<T>* root, std::list< Nodo<T>* >& lista);
	void returnNodesGivenLevel(Nodo<T>* root, int level, std::list< Nodo<T>* >& lista);
	
	void returnValues(Nodo<T>* root, std::list<T>& lista);	
	void returnValuesGivenLevel(Nodo<T>* root, int level, std::list<T>& lista);
	
	void returnLeafs(Nodo<T>* nodo, std::list<T>& lista);
  
  protected:
    T dato;
    TList desc;
};

#include "Nodo.hxx"

#endif

